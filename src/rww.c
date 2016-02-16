/* copyright 2016 Apache 2 sddekit authors */

/*
    [WW_2006] Kong-Fatt Wong and Xiao-Jing Wang, *A Recurrent Network
              Mechanism of Time Integration in Perceptual Decisions*.
              Journal of Neuroscience 26(4), 1314-1328, 2006.
 */

#include "sddekit.h"

struct rww_pars
{
	double
#define PAR(n, v) n,
#define LPAR(n, v) n;
#include "rww_pars.h"
#undef PAR
#undef LPAR
};

struct rww_pars default_pars = {
#define LPAR(n, v) .n = v
#define PAR(n, v) LPAR(n, v),
#include "rww_pars.h"
#undef PAR
#undef LPAR
};

struct rww
{
	struct rww_pars pars;
	struct sd_sys sys_if;
	struct sd_sys_rww rww_if;
};

static void free_sys(struct sd_sys *sys) { sd_free(sys->ptr); }

static void free_rww(struct sd_sys_rww *rww) { sd_free(rww->ptr); }

/* get / set parameters */
#define PAR(n, v) \
	static double get_##n(struct sd_sys_rww *sys) \
	{\
		return ((struct rww *) sys->ptr)->pars.n;\
	}\
	static void set_##n(struct sd_sys_rww *sys, double val) \
	{\
		((struct rww *) sys->ptr)->pars.n = val;\
	}
#define LPAR(n, v) PAR(n, v)
#include "rww_pars.h"
#undef PAR
#undef LPAR

static uint32_t  ndim(sd_sys *s) { (void) s;  return 1; }
static uint32_t   ndc(sd_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(sd_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(sd_sys *s) { (void) s;  return 9; }
static uint32_t nipar(sd_sys *s) { (void) s;  return 0; }

static sd_stat apply(sd_sys *s, sd_sys_in *in, sd_sys_out *out)
{
	struct rww_pars *d = &(((struct rww*) s->ptr)->pars);
	double _x, H, *x = in->x, *c = in->i, *f = out->f, *g = out->g, *o = out->o;
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

static sd_sys sys_default = { 
	.ptr = NULL,
	.ndim = &ndim,
	.ndc = &ndc,
	.nobs = &nobs,
	.nrpar = &nrpar,
	.nipar = &nipar,
	.apply = &apply,
	.free = &free_sys
};

sd_sys * get_sys(struct sd_sys_rww *r) { return &(((struct rww*) r->ptr)->sys_if); }

struct sd_sys_rww rww_default = {
	.ptr = NULL,
	.free = &free_rww,
	.sys = &get_sys,
#define LPAR(n, v) .get_##n = &get_##n, .set_##n=&set_##n
#define PAR(n, v) LPAR(n, v),
#include "rww_pars.h"
#undef LPAR
#undef PAR
};

struct sd_sys_rww *sd_sys_rww_new()
{
	struct rww *r;
	if ((r = sd_malloc(sizeof(struct rww)))==NULL)
	{
		sd_err("alloc sys rww failed.");
		return NULL;
	}
	r->pars = default_pars;
	r->rww_if = rww_default;
	r->sys_if = sys_default;
	r->sys_if.ptr = r->rww_if.ptr = r;
	return &(r->rww_if);
}
