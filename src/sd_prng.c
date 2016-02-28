/* copyright 2016 Apache 2 sddekit authors */

#define _POSIX_C_SOURCE 200809L
#include "sddekit.h"

#include "parallel/iuncl.h"

/*
typedef struct{
	float
		s01, s02, s03, s04,
		s05, s06, s07, s08,
		s09, s10, s11, s12,
		s13, s14, s15, s16,
		s17, s18, s19, s20,
		s21, s22, s23, s24;
	float carry;
	float dummy; //Causes struct to be a multiple of 128 bits
	int in24;
	int stepnr;
} prng_data;
*/

typedef struct prng_data{
	uint32_t seed;
	//For now
} prng_data;

/* 
 * Automatically set the number of work-groups and the number of work-items per
 * work-group if not specified by the user.
 */
static void autoSetWgNumAndSize(uint32_t n, size_t gen_per_it, cl_kernel kernel, cl_command_queue queue, 
		size_t *wg_size, size_t *wg_num)
{
	cl_uint max_cu;
	cl_device_id device;

	size_t wg_per_cu = 16;

	IUNCLERR( clGetCommandQueueInfo(
				queue, CL_QUEUE_DEVICE, sizeof(device), &device, NULL) );
	if(*wg_num == 0){
		IUNCLERR( clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, 
					sizeof(max_cu), &max_cu, NULL) );
		*wg_num = wg_per_cu * max_cu;
	}
	
	if(*wg_size == 0){
		#ifdef CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE
		IUNCLERR( clGetKernelWorkGroupInfo(kernel, device,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof(*wg_size), wg_size, NULL) );
		#else
		printf("WARNING: Could not quiery preferred work-group size.\n");
		*wg_size = 64;
		#endif
		//TODO, temporary fix
		*wg_size = ((*wg_num) * gen_per_it * 4)/ n + 1;
	}
}

/*
 * Perform various setup tasks like compiling the kernels, setting the number
 * of work-items and initializing the generator.
 */
static void stimulate(sd_prng *r, bool isnorm, uint32_t n, float *x, size_t *wg_size,
	size_t *wg_num, int lux, size_t gen_per_it, bool no_warm, bool legacy,
	cl_mem *buff_state, cl_mem *buff_prns,
	cl_program *program, cl_context context, cl_command_queue queue)
{	
	struct prng_data *d = r->ptr;
	cl_uint ins = d->seed;
	cl_int err;
	cl_kernel kernel_init, kernel_prn;

	char bopt[1024] = " -I .";
		
	if(no_warm){
		sprintf(&bopt[strlen(bopt)], " -D RANLUXCL_NO_WARMUP");
	}
	if(legacy) {
		sprintf(&bopt[strlen(bopt)], " -D RANLUXCL_USE_LEGACY_INITIALIZATION");
	}
	sprintf(&bopt[strlen(bopt)], " -D RANLUXCL_LUX=%d", lux);
	sprintf(&bopt[strlen(bopt)], " -D GEN_PER_IT=%zu", gen_per_it);

	iunclCompileKernel("ranluxcl-test_kernels.cl", bopt, context, program, 1);
	printf("\n"); //Add newline since Nvidia's compiler likes to spit out stuff.

	kernel_init = clCreateKernel(*program, "kernelInit", &err);
	IUNCLERR( err );
	if(isnorm) {
		kernel_prn = clCreateKernel(*program, "kernelPnrn", &err);
	} else {
		kernel_prn = clCreateKernel(*program, "kernelPurn", &err);
	}
	IUNCLERR( err );

	//Auto set work-group size and number if not specified
	autoSetWgNumAndSize(n, gen_per_it, kernel_prn, queue, wg_size, wg_num);

	size_t wi_tot = *wg_size * *wg_num;
	printf("Setting up generator."
			"\n%s %zu\n%s %d\n%s %zu\n%s %zu\n%s %zu\n\n",
			 "gen_per_it:", gen_per_it,
			 "Luxury:", lux,
			 "Work-items:", wi_tot,
			 "Work-group size:", *wg_size,
			 "Work-groups:", *wg_num);

	*buff_prns = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
			gen_per_it * wi_tot * sizeof(cl_float4), NULL, &err);
	IUNCLERR( err );
	*buff_state = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(prng_data) * wi_tot, NULL, &err);
	IUNCLERR( err );

	IUNCLERR( clSetKernelArg(kernel_init, 0, sizeof(ins), &ins) );
	IUNCLERR( clSetKernelArg(kernel_init, 1, sizeof(*buff_state), buff_state) );

	IUNCLERR( clSetKernelArg(kernel_prn, 0, sizeof(*buff_state), buff_state) );
	IUNCLERR( clSetKernelArg(kernel_prn, 1, sizeof(*buff_prns), buff_prns) );
	//Initialize the generator.
	IUNCLERR( clEnqueueNDRangeKernel(queue, kernel_init, 1, NULL, &wi_tot,
				wg_size, 0, NULL, NULL) );
	IUNCLERR( clFinish(queue) );


	IUNCLERR( clEnqueueReadBuffer(queue, *buff_prns, CL_TRUE, 0,
		n * sizeof(*x), x, 0, NULL, NULL) );

	IUNCLERR( clFinish(queue) );

}

/* isnorm = false for uniform, and true for norm
	lux = luxery value, the higher the slower and more chaotic
	no_warm = 1 for not warming up
	legacy = to use legacy initializer, otherwise Uses a 64-bit xorshift PRNG by George Marsaglia

	*/
static void filler(sd_prng *r, bool isnorm, int lux, bool no_warm,
		 bool legacy, uint32_t n, float *x)
{
	cl_uint pid=0, did=0;	//Setting to 0 for now, TODO
	size_t wg_size, wg_num;	//TODO 
	size_t gen_per_it = 1000;		//TODO, setting manually

	cl_mem buff_state, buff_prns;
	cl_program program;
	cl_context context;
	cl_command_queue queue;

	iunclGetSingleDeviceContext(pid, did, &context, &queue, 1);

	stimulate(r, isnorm, n, x, &wg_size, &wg_num, lux, gen_per_it,
		no_warm, legacy, &buff_state, &buff_prns,
		&program, context, queue);

}

static void prng_seed(sd_prng *r, uint32_t sed)
{
	struct prng_data *d = r->ptr;
	d->seed = sed;

}


static void prng_fill_uniform(sd_prng *r, size_t n, float *x)
{
	//Setting to default for now, TODO
	int lux = 4;
	bool no_warm = 0;
	bool legacy = 0;

	filler(r, 0, lux, no_warm, legacy, n, x);
}

static void prng_fill_norm(sd_prng *r, size_t n, float *x)
{
	//Setting to default for now, TODO
	int lux = 4;
	bool no_warm = 0;
	bool legacy = 0;
	
	filler(r, 1, lux, no_warm, legacy, n, x);
}

static void prng_free(sd_prng *r)
{
	sd_free(r->ptr);
	sd_free(r);
}

static uint32_t prng_nbytes(sd_prng *r)
{
	(void) r;
	return sizeof(prng_data) + sizeof(sd_prng);
}

static sd_prng prng_default = {
	.ptr = NULL,
	.seed = &prng_seed,
//	.norm = &prng_norm,
//	.uniform = &prng_uniform,
	.fill_uniform = &prng_fill_uniform,
	.fill_norm = &prng_fill_norm,
	.nbytes = &prng_nbytes,
	.free = &prng_free
};

sd_prng *sd_prng_new_default()
{
	sd_prng *r;
    if ((r = sd_malloc (sizeof(sd_prng))) == NULL
	 || (*r = prng_default, 0)
	 || (r->ptr = sd_malloc (sizeof(prng_data))) == NULL)
	{
		sd_free(r);
		sd_err("alloc prng failed.");
		return NULL;
	}
	return r;
}
