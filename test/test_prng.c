//TODO

/*
 * Run the generator and check the output against values from the original
 * Fortran implementation by F. James.
 */
/*
void checkCorrectness(size_t wg_size, size_t wg_num, int lux, int gen_per_it,
	cl_mem *buff_state, cl_mem *buff_prns,
	cl_program program, cl_command_queue queue)
{
	cl_int err;
	cl_ulong iter_num;
	size_t num_errors = 0;
	size_t wi_tot; 
	size_t ref_file_size_meas;
	size_t ref_file_elems_read;
	size_t elems_to_check;
	double sum_errors = 0;
	cl_float *ref_data, *ref_data_offset;
	cl_float4 *prns;
	const size_t ref_file_elems = 51200 * 5;
	const char ref_file_name[] = "ranluxclref.binary";

	//Must be able to generate exactly 1 million numbers per work-item,
	//meaning 250 000 calls to ranluxcl.
	if(250000 % gen_per_it){
		printf("gen_per_it must divide 250 000, "
			"correctness check aborted.\n\n");
		return;
	}

	//Correctness check only works for lux 0-4
	if(lux > 4 || lux < 0){
		printf("lux must be 0-4, correctness check aborted.\n\n");
		return;
	}

	iter_num = 250000 / gen_per_it;

	cl_kernel kernel_prn_light = 
		clCreateKernel(program, "kernelPrnLight", &err);
	IUNCLERR( err );

	IUNCLERR( clSetKernelArg(kernel_prn_light, 0,
		sizeof(buff_state), buff_state) );
	IUNCLERR( clSetKernelArg(kernel_prn_light, 1,
		sizeof(buff_prns), buff_prns) );
	
	wi_tot = wg_size * wg_num;

	prns = malloc(wi_tot * sizeof(*prns));

	printf("Starting correctness run.\n");

	for(cl_ulong iter = 0; iter < iter_num; iter++)
		IUNCLERR( clEnqueueNDRangeKernel(queue, kernel_prn_light, 1, NULL,
			&wi_tot, &wg_size, 0, NULL, NULL) );

	IUNCLERR( clFinish(queue) );

	printf("Finished run.\n");

	IUNCLERR( clEnqueueReadBuffer(queue, *buff_prns, CL_TRUE, 0,
		wi_tot * sizeof(*prns), prns, 0, NULL, NULL) );

	IUNCLERR( clFinish(queue) );

	//File contains 51200 floats (4 bytes) for each of the 5 luxury values (0-4)
	FILE *ref_file;

	printf("Reading reference file \"%s\"\n", ref_file_name);
	
	if((ref_file = fopen(ref_file_name, "rb")) == NULL){
		printf("Could not open reference file \"%s\", "
			"correctness check aborted.\n\n", ref_file_name);
		return;
	}

	if(fseek(ref_file, 0, SEEK_END)){
		printf("Could not seek the reference file \"%s\", "
			"correctness check aborted.\n\n", ref_file_name);
		return;
	}

	ref_file_size_meas = (size_t)ftell(ref_file);
	if(fseek(ref_file, 0, SEEK_SET)){
		printf("Could not seek the reference file \"%s\", "
			"correctness check aborted.\n\n", ref_file_name);
		return;
	}

	if(ref_file_elems * sizeof(cl_float) != ref_file_size_meas){
		printf("Reference file has wrong size. Should be %zu B, is %zu B."
			" Correctness check aborted.\n\n",
			ref_file_elems * sizeof(cl_float), ref_file_size_meas);
		return;
	}

	ref_data = malloc(ref_file_elems * sizeof(*ref_data));

	ref_file_elems_read = 
		fread(ref_data, sizeof(*ref_data), ref_file_elems, ref_file); 
	if(ref_file_elems_read != ref_file_elems){
		printf("Reference file not read correctly, "
			"%zu elements were read, expected %zu. "
			"Correctness check aborted.\n\n",
			ref_file_elems_read, ref_file_elems);
		return;
	}

	fclose(ref_file);

	//Set correct offset for luxury value.
	ref_data_offset = &ref_data[ref_file_elems / 5 * lux];

	elems_to_check = (ref_file_elems / 5 > wi_tot) ? 
		wi_tot : ref_file_elems / 5;

	//Perform correctness check
	for(size_t i = 0; i < elems_to_check; i++){
		if(ref_data_offset[i] != prns[i].s[3])
			num_errors++;
		sum_errors += fabs(ref_data_offset[i] - prns[i].s[3]);
	}

	printf("%*s %zu\n%*s %zu\n%*s %.8f\n",
		-PAD, "Number of values checked:", elems_to_check,
		-PAD, "Number of errors:", num_errors,
		-PAD, "Sum of errors:", sum_errors);
	
	if((num_errors == 0) && (sum_errors == 0))
		printf("Correctness check PASSED!\n\n");
	else
		printf("COrrectness check FAILED!\n\n");

	free(ref_data);
	free(prns);
}
*/

/*
 * Writes the contents of prns to text files, one file per work-item.
 */
/*
void writeTextFiles(size_t wi_tot, size_t gen_per_it, cl_float4 *prns)
{
	FILE *f;
	char *fbase = "rlx-rand-wi-";
	char *fext = "txt";
	char fname[32];

	for(size_t wi = 0; wi < wi_tot; wi++){
		snprintf(fname, 32, "%s%.4zu.%s", fbase, wi, fext);
		if((f = fopen(fname, "a")) == NULL){
			printf("Error opening file %s for write/append.\n", fname);
			continue;
		}
		
		for(size_t i = 0; i < gen_per_it; i++)
			for(int j = 0; j < 4; j++)
				fprintf(f, "%.7f\n", prns[wi + i * wi_tot].s[j]);

		fclose(f);
	}
}
*/
/*
 * Writes the contents of prns to a binary file, taking care to only use
 * the useful bits (so that the output file should be filled with pseudorandom
 * bit).
 */
/*
void writeBinaryFile(size_t numvecs, size_t rand_bytes, bool lsb,
	cl_float4 *prns, FILE *rand_file)
{
	unsigned char *rand_data;
	unsigned char rand1, rand2, rand3;
	size_t count = 0;
	
	if((rand_data = malloc(rand_bytes)) == NULL){
		printf("Could not allocate memory, filewrite aborted.\n");
		return;
	}

	for(size_t vec = 0; vec < numvecs; vec++){
		rand1 = 0;
		for(size_t i = 0; i < 4; i++){
			if(lsb)
				rand1 += (1 << (7-i)) * 
					(((cl_uint)(prns[vec].s[i] * (1 << 24))) & 1);
			else{
				rand1 = (((cl_uint)(prns[vec].s[i] * (1 << 24))) >> 0)  & 255;
				rand2 = (((cl_uint)(prns[vec].s[i] * (1 << 24))) >> 8)  & 255;
				rand3 = (((cl_uint)(prns[vec].s[i] * (1 << 24))) >> 16) & 255;
				rand_data[count] = rand3;
				count++;
				rand_data[count] = rand2;
				count++;
				rand_data[count] = rand1;
				count++;
			}
		}
		vec++;
		for(size_t i = 0; i < 4; i++){
			if(lsb)
				rand1 += (1 << (3-i)) *
					(((cl_int)(prns[vec].s[i] * (1 << 24))) & 1);
			else{
				rand1 = (((cl_uint)(prns[vec].s[i] * (1 << 24))) >> 0)  & 255;
				rand2 = (((cl_uint)(prns[vec].s[i] * (1 << 24))) >> 8)  & 255;
				rand3 = (((cl_uint)(prns[vec].s[i] * (1 << 24))) >> 16) & 255;
				rand_data[count] = rand3;
				count++;
				rand_data[count] = rand2;
				count++;
				rand_data[count] = rand1;
				count++;
			}
		}
		if(lsb){
			rand_data[count] = rand1;
			count++;
		}
	}

	if(fwrite(rand_data, 1, count, rand_file) != count){
		printf("fwrite error, fwrite() != count.\n");
	}
	
	if(count != rand_bytes){
		printf("filewrite error: count != rand_bytes: %zu != %zu\n",
			count, rand_bytes);
	}

	free(rand_data);
}
*/
/*
 * Writes the output of the generator to file, for example for empirically
 * testing the quality.
 */
/*
void writeRandomFile(size_t wg_size, size_t wg_num,
	size_t bytes_req, int gen_per_it, bool lsb, bool txt,
	cl_mem *buff_state, cl_mem *buff_prns,
	cl_program program, cl_command_queue queue)
{
	cl_int err;
	cl_ulong iter_num;
	size_t wi_tot;
	size_t vals_per_it;
	size_t bytes_per_val = 3;
	size_t rand_bytes_per_it;
	cl_float4 *prns;
	FILE *rand_file;
	const char *rand_file_name;
	rand_file_name = lsb ? "ranluxcl-test-rand-lsb.binary" : 
	                       "ranluxcl-test-rand-std.binary";

	wi_tot = wg_size * wg_num;
	vals_per_it = wi_tot * gen_per_it * 4;
	rand_bytes_per_it = lsb ? vals_per_it / 8 : vals_per_it * bytes_per_val;

	iter_num = (cl_ulong)ceil((double)bytes_req / rand_bytes_per_it);

	//Demand this to make lsb mode easier
	if(gen_per_it % 2){
		printf("gen_per_it must be divisible by 2, filewrite aborted.\n");
		return;
	}

	cl_kernel kernel_prn = clCreateKernel(program, "kernelPrn", &err);
	IUNCLERR( err );

	IUNCLERR( clSetKernelArg(kernel_prn, 0, sizeof(buff_state), buff_state) );
	IUNCLERR( clSetKernelArg(kernel_prn, 1, sizeof(buff_prns), buff_prns) );
	
	if((prns = malloc(vals_per_it * sizeof(cl_float))) == NULL){
		printf("Could not allocate memory, filewrite aborted.\n");
		return;
	}

	printf("Starting filewrite run.\n");

	if((rand_file = fopen(rand_file_name, "ab")) == NULL){
		printf("Could not open file \"%s\" "
			"for appending, filewrite aborted.\n",
			rand_file_name);
		return;
	}

	for(cl_ulong iter = 0; iter < iter_num; iter++){
		IUNCLERR( clEnqueueNDRangeKernel(queue, kernel_prn, 1, NULL, 
			&wi_tot, &wg_size, 0, NULL, NULL) );
		IUNCLERR( clEnqueueReadBuffer(queue, *buff_prns, CL_FALSE, 0,
			vals_per_it * sizeof(cl_float), prns, 0, NULL, NULL) );
		IUNCLERR( clFinish(queue) );

		if(txt)
			writeTextFiles(wi_tot, gen_per_it, prns);
		else
			writeBinaryFile(wi_tot * gen_per_it, rand_bytes_per_it,
				lsb, prns, rand_file);
	}

	fclose(rand_file);

	printf("Finished run.\n");

	free(prns);
}
*/