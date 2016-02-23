/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct {
		double 
#define PAR(n, v) n,
#define LASTPAR(n, v) n;
#include "sys_gen2d_pars.h"
#undef PAR
#undef LASTPAR
} pars;

static pars default_pars = {
#define PAR(name, value) .name = value,
#define LASTPAR(name, value) .name = value
#include "sys_gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

typedef struct {
	sd_sys sys_if;
	sd_sys_gen2d gen2d_if;
	pars pars;
} gen2d;

#define PAR(name, value)\
	static double get_ ## name(sd_sys_gen2d *s)\
		{ return ((gen2d*) s->ptr)->pars.name; } \
	static void set_ ## name(sd_sys_gen2d *s, double new)\
		{ ((gen2d*) s->ptr)->pars.name = new; }
#define LASTPAR(n, v) PAR(n, v)
#include "sys_gen2d_pars.h"
#undef PAR
#undef LASTPAR

static void _free(gen2d *s) { sd_free(s); }
static void gen2d_free(sd_sys_gen2d *s) { _free(s->ptr); }
static void sys_free(sd_sys *s) { _free(s->ptr); }

static sd_stat apply(sd_sys *s, sd_sys_in *in, sd_sys_out *out)
{
		pars *p = &(((gen2d*) s->ptr)->pars);
		double *x = in->x, *c = in->i, *f = out->f, *g = out->g, *o = out->o;
		double V = x[0], W = x[1];
		double V2 = V * V;
		f[0] = p->d * p->tau * (p->alpha * W - p->f*V2*V + p->e*V2 + p->g * V + p->gamma * (p->I + c[0]));
		f[1] = p->d * (p->a + p->b * V + p->c * V2 - p->beta * W) / p->tau;
		g[0] = p->D;
		g[1] = p->D;
		o[0] = x[0];
		return SD_OK;
}

static uint32_t  ndim(sd_sys *s) { (void) s;  return 2; }
static uint32_t   ndc(sd_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(sd_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(sd_sys *s) { (void) s;  return 4; }
static uint32_t nipar(sd_sys *s) { (void) s;  return 0; }

static sd_sys sys_if_default = { 
	.ptr = NULL,
	.ndim = &ndim,
	.ndc = &ndc,
	.nobs = &nobs,
	.nrpar = &nrpar,
	.nipar = &nipar,
	.apply = &apply,
	.free = &sys_free
};

static sd_sys * get_sys(sd_sys_gen2d *s) { return &(((gen2d*) s->ptr)->sys_if); }

static sd_sys_gen2d gen2d_if_default = { 
	.ptr = NULL,
	.free = &gen2d_free,
	.sys = &get_sys,
#define PAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n,
#define LASTPAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n
#include "sys_gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

sd_sys_gen2d *sd_sys_gen2d_new() {
	gen2d *d, zero = {0};
	if ((d = sd_malloc (sizeof(gen2d))) == NULL)
	{
		sd_err("alloc gen2d sys failed.");
		return NULL;
	}
	*d = zero;
	d->sys_if = sys_if_default;
	d->gen2d_if = gen2d_if_default;
	d->pars = default_pars;
	d->sys_if.ptr = d->gen2d_if.ptr = d;
	return &(d->gen2d_if);
}
