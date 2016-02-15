/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct netd
{
	sd_sys sys_if;
	sd_net net_if;
	uint32_t n, m, nnz, * restrict M, * restrict Ms, 
			 * restrict Ma, * restrict Me, ns, ne, 
			 * restrict Or, * restrict Ic;
	double * restrict w, * restrict d, * restrict cn;
	sd_sys **models;
	/* flag for init1 use */
	bool _init1;
	/* cache vi2i from history */
	uint32_t *vi2i;
} netd;

static uint32_t  get_n       (sd_net *net)             { return ((netd*)net->ptr)->n; }
static uint32_t  get_m       (sd_net *net)             { return ((netd*)net->ptr)->m; }
static uint32_t  get_nnz     (sd_net *net)             { return ((netd*)net->ptr)->nnz; }
static uint32_t *get_or      (sd_net *net)             { return ((netd*)net->ptr)->Or; }
static uint32_t  get_or_i    (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->Or[i]; }
static uint32_t *get_ic      (sd_net *net)             { return ((netd*)net->ptr)->Ic; }
static uint32_t  get_ic_i    (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->Ic[i]; }
static double *  get_w       (sd_net *net)             { return ((netd*)net->ptr)->w; }
static double    get_w_i     (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->w[i]; }
static double *  get_d       (sd_net *net)             { return ((netd*)net->ptr)->d; }
static double    get_d_i     (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->d[i]; }
static uint32_t  get_ns      (sd_net *net)             { return ((netd*)net->ptr)->ns; }
static uint32_t  get_ne      (sd_net *net)             { return ((netd*)net->ptr)->ne; }
static bool      cn_is_null  (sd_net *net)             { return ((netd*)net->ptr)->cn == NULL; }
static uint32_t  get_Ms_i    (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->Ms[i]; }
static uint32_t  get_Ma_i    (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->Ma[i]; }
static uint32_t  get_Me_i    (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->Me[i]; }
static uint32_t  get_M_i     (sd_net *net, uint32_t i) { return ((netd*)net->ptr)->M[i]; }
static sd_sys *  get_models_i(sd_net *net, uint32_t i) { return ((netd*)net->ptr)->models[i]; }
static bool      get__init1  (sd_net *net)             { return ((netd*)net->ptr)->_init1; }

static sd_stat apply(sd_sys *sys, sd_sys_in *in, sd_sys_out *out)
{
	sd_stat stat;
	uint32_t l, j;
	netd *d = sys->ptr;
	sd_sys **sysi = d->models;
	sd_sys_in in_l = *in;
	sd_sys_out out_l = *out;
	/* cache vi2i if not present */
	if (d->vi2i==NULL)
		d->vi2i = in->hist->get_vi2i_vec(in->hist);
	/* compute (sparse) inputs */
	for (l=0; l<d->ne; l++) 
		for (d->cn[l]=0.0, j=d->Or[l]; j<d->Or[l+1]; j++)
			d->cn[l] += in->i[d->vi2i[d->Ic[j]]] * d->w[j];
	/* TODO redo, this is not restrict */
	in_l.i = out_l.o = d->cn;
	for (l = 0; l < d->n; l++)
	{
		uint32_t ml = d->M[l];
		if ((stat = (*sysi)->apply(*sysi, &in_l, &out_l)) != SD_OK)
			return stat;
		/* TODO double check */
		in_l.id += 1;
		in_l.i += d->Ma[ml];
		in_l.x += d->Ms[ml];
		out_l.f += d->Ms[ml];
		out_l.g += d->Ms[ml];
		out_l.o += d->Me[ml];
	}
	/* compute outputs */
	for (l=0; l<d->nnz; l++)
		out->o[l] = d->cn[d->Ic[l]];
	return SD_OK;
}

sd_net *sd_net_new_hom(uint32_t n, sd_sys *sys,
		uint32_t ns, uint32_t na, uint32_t ne,
		uint32_t nnz, 
		uint32_t * restrict Or, 
		uint32_t * restrict Ic, 
		double * restrict w,
		double * restrict d)
{
	uint32_t i, *M, *Ms, *Me, *Ma;
	sd_sys **models;
	char *errmsg;
	sd_net *net;
	M = Ms = Me = Ma = NULL;
	models = NULL;
	if ((M = sd_malloc (sizeof(uint32_t) * n))==NULL
	 || (Ms = sd_malloc (sizeof(uint32_t)))==NULL
	 || (Ma = sd_malloc (sizeof(uint32_t)))==NULL
	 || (Me = sd_malloc (sizeof(uint32_t)))==NULL
	 || (models = sd_malloc (sizeof(sd_sys*)))==NULL)
	{
		errmsg = "failed to allocate net init1 storage.";
		goto fail;
	}
	Ms[0] = ns;
	Ma[0] = na;
	Me[0] = ne;
	for(i=0; i<n; i++)
		M[i] = 0;
	models[0] = sys;
	if ((net = sd_net_new_het(n, 1, M, Ms, Ma, Me, models, 
			        nnz, Or, Ic, w, d)) == NULL)
	{
		errmsg = "net initn failed.";
		goto fail;
	}
	((netd*)net->ptr)->_init1 = true;
	return net;
fail:
	if (M!=NULL) sd_free(M);
	if (Ms!=NULL) sd_free(Ms);
	if (Me!=NULL) sd_free(Me);
	if (Ma!=NULL) sd_free(Ma);
	if (models!=NULL) sd_free(models);
	sd_err(errmsg);
	return NULL;
}

static void free_ptr(netd *d)
{
	if (d->_init1) {
		sd_free(d->M);
		sd_free(d->Ms);
		sd_free(d->Me);
		sd_free(d->Ma);
		sd_free(d->models);
		sd_free(d->cn);
	}
	sd_free(d);
}

static void free_net(sd_net *net) { free_ptr(net->ptr); }
static void free_sys(sd_sys *sys) { free_ptr(sys->ptr); }

static	uint32_t sys_ndim(sd_sys*sys) { return ((netd*)sys->ptr)->ns; }
static	uint32_t sys_ndc(sd_sys*sys)  { return ((netd*)sys->ptr)->nnz; }
static	uint32_t sys_nobs(sd_sys*sys) { return ((netd*)sys->ptr)->ne; }
static	uint32_t sys_nrpar(sd_sys*sys){ (void) sys; return 0; }
static	uint32_t sys_nipar(sd_sys*sys){ (void) sys; return 0; }

static sd_sys net_sys_defaults = {
	.ndim = &sys_ndim,
	.ndc = &sys_ndc,
	.nobs = &sys_nobs,
	.nrpar = &sys_nrpar,
	.nipar = &sys_nipar,
	.apply = &apply,
	.free = &free_sys,
	.ptr = NULL
};

static sd_sys *net_to_sys(sd_net *net) { return &(((netd*)net->ptr)->sys_if); }

static sd_net net_defaults = {
	.ptr = NULL,
	.sys = &net_to_sys,
	.get_n = &get_n,
	.get_m = &get_m,
	.get_nnz = &get_nnz,
	.get_or = &get_or,
	.get_or_i = &get_or_i,
	.get_ic = &get_ic,
	.get_ic_i = &get_ic_i,
	.get_w = &get_w,
	.get_w_i = &get_w_i,
	.get_d = &get_d,
	.get_d_i = &get_d_i,
	.get_ns = &get_ns,
	.get_ne = &get_ne,
	.cn_is_null = &cn_is_null,
	.get_Ms_i = &get_Ms_i,
	.get_Ma_i = &get_Ma_i,
	.get_Me_i = &get_Me_i,
	.get_M_i = &get_M_i,
	.get_models_i = &get_models_i,
	.get__init1 = &get__init1,
	.free = &free_net
};

sd_net *
sd_net_new_het(uint32_t n, uint32_t m, 
	uint32_t * restrict M, uint32_t * restrict Ms, 
	uint32_t * restrict Ma, uint32_t * restrict Me,
	sd_sys **models,
	uint32_t nnz, 
	uint32_t * restrict Or,
	uint32_t * restrict Ic,
	double * restrict w,
	double * restrict d)
{
	uint32_t i;
	netd *net = sd_malloc(sizeof(netd));
	if (net == NULL)
	{
		sd_err("net alloc failed.");
		return NULL;
	}
	net->net_if = net_defaults;
	net->sys_if = net_sys_defaults;
	net->net_if.ptr = net->sys_if.ptr = net;
	net->n = n;
	net->m = m;
	net->nnz = nnz;
	net->M = M;
	net->Ms = Ms;
	net->Ma = Ma;
	net->Me = Me;
	net->models = models;
	net->Or = Or;
	net->Ic = Ic; /* TODO ? same as Ie ? */
	net->w = w;
	net->d = d;
	/* intialize based on passed attributes: Ie, cne, cna */
	net->ns = 0;
	net->ne = 0;
	for (i=0; i<n; i++) {
		net->ns += net->Ms[net->M[i]];
		net->ne += net->Me[net->M[i]];
	}
	if ((net->cn = sd_malloc (sizeof(double) * net->ne))==NULL)
	{
		sd_err("failed to allocate memory for network.");
		return NULL;
	}
	net->_init1 = 0;
	net->vi2i = NULL;
	return &(net->net_if);
}


