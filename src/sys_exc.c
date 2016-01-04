/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct pars {
	double a, tau, D, k;
};

struct pars pars_default = {.a=1.1, .tau=3.0, .D=1e-3, .k=0.01};

struct data {
	sd_sys sys_if;
	sd_sys_exc exc_if;
	struct pars pars;
};

static void exc_free(sd_sys *s) { sd_free(s->ptr); }

/* get set */
#define GETSET(field) \
static double get_ ## field(sd_sys_exc *s) { \
	struct data *d = (struct data *) (*s->sys)(s)->ptr; \
	return d->pars.field; \
}\
static void set_ ## field(sd_sys_exc *s, double val) { \
	struct data *d = (struct data *) (*s->sys)(s)->ptr; \
	d->pars.field = val; \
}

GETSET(a)
GETSET(tau)
GETSET(D)
GETSET(k)

#undef GETSET

static sd_stat apply(sd_sys *s, sd_sys_in *in, sd_sys_out *out)
{
	struct pars *d = &(((struct data*) s->ptr)->pars);
	double *x = in->x, *c = in->i, *f = out->f, *g = out->g, *o = out->o;
	f[0] = (x[0] - x[0]*x[0]*x[0]/3.0 + x[1]) * d->tau;
	f[1] = (d->a - x[0] + d->k*c[0]) / d->tau;
	g[0] = d->D;
	g[1] = d->D;
	o[0] = x[0];
	return SD_OK;
}

uint32_t  ndim(sd_sys *s) { (void) s;  return 2; }
uint32_t   ndc(sd_sys *s) { (void) s;  return 1; }
uint32_t  nobs(sd_sys *s) { (void) s;  return 1; }
uint32_t nrpar(sd_sys *s) { (void) s;  return 4; }
uint32_t nipar(sd_sys *s) { (void) s;  return 0; }

sd_sys sys_default = { 
	.ptr = NULL,
	.ndim = &ndim,
	.ndc = &ndc,
	.nobs = &nobs,
	.nrpar = &nrpar,
	.nipar = &nipar,
	.apply = &apply,
	.free = &exc_free
};

sd_sys * get_sys(sd_sys_exc *e) { return &(((struct data *) e->ptr)->sys_if); }

sd_sys_exc exc_default = { 
	.ptr = NULL,
	.sys = &get_sys,
	.get_a = &get_a,
	.set_a = &set_a,
	.get_tau = &get_tau,
	.set_tau = &set_tau,
	.get_D = &get_D,
	.set_D = &set_D,
	.get_k = &get_k,
	.set_k = &set_k
};

sd_sys_exc *sd_sys_exc_new() {
	struct data *d, zero = {0};
	if ((d = sd_malloc (sizeof(struct data))) == NULL)
	{
		sd_err("alloc exc sys failed.");
		return NULL;
	}
	*d = zero;
	d->pars = pars_default;
	d->sys_if = sys_default;
	d->exc_if = exc_default;
	d->sys_if.ptr = d->exc_if.ptr = d;
	return &(d->exc_if);
}
