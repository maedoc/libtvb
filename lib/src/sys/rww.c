/* copyright 2016 Apache 2 sddekit authors */

/*
    [WW_2006] Kong-Fatt Wong and Xiao-Jing Wang, *A Recurrent Network
              Mechanism of Time Integration in Perceptual Decisions*.
              Journal of Neuroscience 26(4), 1314-1328, 2006.
 */

#include "sddekit.h"
#include <math.h>

struct pars
{
	double
#define PAR(n, v) n,
#define LPAR(n, v) n;
#include "sys/rww_pars.h"
#undef PAR
#undef LPAR
};

static struct pars pars_defaults = {
#define LPAR(n, v) .n = v
#define PAR(n, v) LPAR(n, v),
#include "sys/rww_pars.h"
#undef PAR
#undef LPAR
};

struct data
{
	struct pars pars;
	struct sd_sys sd_sys;
	struct sd_sys_rww sd_sys_rww;
};

static void
data_free(struct data *data)
{
    sd_free(data);
}

static uint32_t
data_n_byte(struct data *data)
{
    return sizeof(struct data);
}

static struct data *
data_copy(struct data *data)
{
    struct data *copy = sd_malloc(sizeof(struct data));
    if (copy == NULL)
        sd_err("copy rww failed.");
    *copy = *data;
    return copy;
}

sd_declare_tag_functions(sd_sys)
sd_declare_tag_functions(sd_sys_rww)

/* get / set parameters */
#define PAR(n, v) \
	static double get_##n(struct sd_sys_rww *sys) \
	{\
		return ((struct data *) sys->data)->pars.n;\
	}\
	static void set_##n(struct sd_sys_rww *sys, double val) \
	{\
		((struct data *) sys->data)->pars.n = val;\
	}
#define LPAR(n, v) PAR(n, v)
#include "sys/rww_pars.h"
#undef PAR
#undef LPAR

static uint32_t  ndim(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t   ndc(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(struct sd_sys *s) { (void) s;  return 9; }
static uint32_t nipar(struct sd_sys *s) { (void) s;  return 0; }

static enum sd_stat apply(struct sd_sys *s, struct sd_sys_in *in, struct sd_sys_out *out)
{
	struct pars *d = &(((struct data*) s->data)->pars);
	double _x, H, *x = in->state, *c = in->input, *f = out->drift
         , *g = out->diffusion, *o = out->output;
	/* clamp between 0 & 1 */
	if (x[0] > 1.0) x[0] = 1.0;
	if (x[0] < 0.0) x[0] = 0.0;
	_x = d->w * d->J_N * (x[0] + c[0]) + d->I_o;
	H = (d->a * _x - d->b) / (1.0 - exp(-d->d * (d->a * _x - d->b)));
	f[0] = - (x[0] / d->tau_s) + (1.0 - x[0]) * H * d->gamma;
	g[0] = d->D;
	o[0] = x[0];
	return SD_OK;
}

static struct sd_sys sd_sys_defaults = { 
	sd_declare_tag_vtable(sd_sys),
	.get_n_dim = &ndim,
	.get_n_in = &ndc,
	.get_n_out = &nobs,
	.get_n_rpar = &nrpar,
	.get_n_ipar = &nipar,
	.apply = &apply
};

struct sd_sys * as_sys(struct sd_sys_rww *r) { return &(((struct data*) r->data)->sd_sys); }

static struct sd_sys_rww sd_sys_rww_defaults = {
	sd_declare_tag_vtable(sd_sys_rww),
	.as_sys = &as_sys,
#define LPAR(n, v) .get_##n = &get_##n, .set_##n=&set_##n
#define PAR(n, v) LPAR(n, v),
#include "sys/rww_pars.h"
#undef LPAR
#undef PAR
};

struct sd_sys_rww *sd_sys_rww_new()
{
	struct data *data;
	if ((data = sd_malloc(sizeof(struct data)))==NULL)
	{
		sd_err("alloc sys rww failed.");
		return NULL;
	}
    data->pars = pars_defaults;
    data->sd_sys = sd_sys_defaults;
    data->sd_sys_rww = sd_sys_rww_defaults;
	data->sd_sys.data = data->sd_sys_rww.data = data;
	return &data->sd_sys_rww;
}
