/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct {
		double 
#define PAR(n, v) n,
#define LASTPAR(n, v) n;
#include "gen2d_pars.h"
#undef PAR
#undef LASTPAR
} pars;

static pars default_pars = {
#define PAR(name, value) .name = value,
#define LASTPAR(name, value) .name = value
#include "gen2d_pars.h"
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
		{ return ((gen2d*) s->ptr).pars.name; } \
	static void set_ ## name(sd_sys_gen2d *s, double new)\
		{ ((gen2d*) s->ptr).pars.name = new; }
#define LASTPAR(n, v) PAR(n, v)
#include "gen2d_pars.h"
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
		f[0] = p->alpha * W - p->f * V *V *+ p->g * V + p->gamma * (p->I + c[0]);
		if (p->f != 0.0)
				f[0] -= V * V * V;
		if (p->e != 0.0)
				f[0] += V * V;

		f[0] = (x[0] - x[0]*x[0]*x[0]/3.0 + x[1]) * d->tau;
		f[1] = (d->a - x[0] + d->k*c[0]) / d->tau;
		g[0] = p->D;
		g[1] = p->D;
		o[0] = x[0];
		return SD_OK;
}

uint32_t  ndim(sd_sys *s) { (void) s;  return 2; }
uint32_t   ndc(sd_sys *s) { (void) s;  return 1; }
uint32_t  nobs(sd_sys *s) { (void) s;  return 1; }
uint32_t nrpar(sd_sys *s) { (void) s;  return 4; }
uint32_t nipar(sd_sys *s) { (void) s;  return 0; }

sd_sys sys_if_default = { 
	.ptr = NULL,
	.ndim = &ndim,
	.ndc = &ndc,
	.nobs = &nobs,
	.nrpar = &nrpar,
	.nipar = &nipar,
	.apply = &apply,
	.free = &gen2d_free
};

sd_sys * get_sys(sd_sys_gen2d *s) { return &(((gen2d*) s->ptr)->sys_id); }

sd_sys_gen2d gen2d_if_default = { 
	.ptr = NULL,
	.sys = &get_sys,
#define PAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n,
#define LASTPAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n
#include "gen2d_pars.h"
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
