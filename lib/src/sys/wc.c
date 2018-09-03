/* copyright 2016 Apache 2 libtvb authors */

#include <math.h>
#include "libtvb.h"

struct pars
{
#define PAR(name, value) double name;
#define LPAR(name, value) PAR(name, value)
#include "sys/wc_pars.h"
#undef PAR
#undef LPAR
};

struct pars pars_defaults = {
#define PAR(name, value) .name = value,
#define LPAR(name, value) .name = value
#include "sys/wc_pars.h"
#undef PAR
#undef LPAR
};

struct data
{
	struct tvb_sys tvb_sys;
    struct tvb_sys_wc tvb_sys_wc;
	struct pars pars;
};

/* obj free n byte copy */
static void
data_free(struct data *data)
{
    tvb_free(data);
}

static uint32_t
data_n_byte(struct data *data)
{
    (void) data;
    return sizeof(struct data);    
}

static struct data * 
data_copy(struct data *data)
{
    struct data *copy = tvb_malloc(sizeof(struct data));
    if (copy == NULL)
        tvb_err("copy gen2d failed.");
    *copy = *data;
    return copy;
}

tvb_declare_tag_functions(tvb_sys)
tvb_declare_tag_functions(tvb_sys_wc)

static uint32_t  ndim(struct tvb_sys *s) { (void) s; return 2; }
static uint32_t   ndc(struct tvb_sys *s) { (void) s; return 2; }
static uint32_t  nobs(struct tvb_sys *s) { (void) s; return 2; }
static uint32_t nrpar(struct tvb_sys *s) { (void) s; return 28; }
static uint32_t nipar(struct tvb_sys *s) { (void) s; return 0; }

/* get / set parameters */
#define PAR(n, v) \
	static double get_##n(struct tvb_sys_wc *sys) \
	{\
		return ((struct data *) sys->data)->pars.n;\
	}\
	static void set_##n(struct tvb_sys_wc *sys, double val) \
	{\
		((struct data *) sys->data)->pars.n = val;\
	}
#define LPAR(n, v) PAR(n, v)
#include "sys/wc_pars.h"
#undef PAR
#undef LPAR

static enum tvb_stat
apply(struct tvb_sys *tvb_sys, struct tvb_sys_in *in, struct tvb_sys_out *out) {
	struct data *data = tvb_sys->data;
	double *x = in->state, *c = in->input, *f = out->drift,
           *g = out->diffusion, *o = out->output;
    struct pars *p = &data->pars;
	f[0] = p->alpha_e * (p->c_ee * x[0] - p->c_ei * x[1] + p->P
		- p->theta_e + c[0] + c[1]);
	f[1] = p->alpha_i * (p->c_ie * x[0] - p->c_ii * x[1] + p->Q
		- p->theta_i + c[0] + c[1]);
	f[0] = p->c_e / (1.0 + exp(-p->a_e * (f[0] - p->b_e)));
	f[1] = p->c_i / (1.0 + exp(-p->a_i * (f[1] - p->b_i)));
	f[0] = (-x[0] + (p->k_e - p->r_e * x[0]) * f[0]) / p->tau_e;
	f[1] = (-x[1] + (p->k_i - p->r_i * x[1]) * f[1]) / p->tau_i;
    g[0] = p->D;
    g[1] = p->D;
	o[0] = x[0];
	o[1] = x[1];
	return TVB_OK;
}

static struct tvb_sys tvb_sys_defaults = {
    tvb_declare_tag_vtable(tvb_sys),
	.get_n_dim = &ndim,
	.get_n_in = &ndc,
	.get_n_out = &nobs,
	.get_n_rpar = &nrpar,
	.get_n_ipar = &nipar,
	.apply = &apply
};

static struct tvb_sys_wc tvb_sys_wc_defaults = {
    tvb_declare_tag_vtable(tvb_sys_wc),
#define LPAR(n, v) .get_##n = &get_##n, .set_##n=&set_##n
#define PAR(n, v) LPAR(n, v),
#include "sys/wc_pars.h"
#undef LPAR
#undef PAR
};

struct tvb_sys_wc *
tvb_sys_wc_new()
{
	struct data *data = tvb_malloc(sizeof(struct data));
	if (data == NULL)
	{
		tvb_err("alloc wc data failed.");
		return NULL;
	}
    data->pars = pars_defaults;
    data->tvb_sys = tvb_sys_defaults;
    data->tvb_sys_wc = tvb_sys_wc_defaults;
    return &data->tvb_sys_wc;
}