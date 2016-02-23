/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct hmje_pars
{
	double
#define PAR(n, v) n,
#define LPAR(n, v) n;
#include "sys_hmje_pars.h"
#undef PAR
#undef LPAR
};

static struct hmje_pars default_pars = {
#define LPAR(n, v) .n = v
#define PAR(n, v) LPAR(n, v),
#include "sys_hmje_pars.h"
#undef PAR
#undef LPAR
};

struct hmje
{
	struct hmje_pars pars;
	struct sd_sys sys_if;
	struct sd_sys_hmje hmje_if;
};

static void free_sys(struct sd_sys *sys) { sd_free(sys->ptr); }

static void free_hmje(struct sd_sys_hmje *hmje) { sd_free(hmje->ptr); }

/* get / set parameters */
#define PAR(n, v) \
	static double get_##n(struct sd_sys_hmje *sys) \
	{\
		return ((struct hmje *) sys->ptr)->pars.n;\
	}\
	static void set_##n(struct sd_sys_hmje *sys, double val) \
	{\
		((struct hmje *) sys->ptr)->pars.n = val;\
	}
#define LPAR(n, v) PAR(n, v)
#include "sys_hmje_pars.h"
#undef PAR
#undef LPAR

static uint32_t  ndim(sd_sys *s) { (void) s;  return 6; }
static uint32_t   ndc(sd_sys *s) { (void) s;  return 3; }
static uint32_t  nobs(sd_sys *s) { (void) s;  return 2; }
static uint32_t nrpar(sd_sys *s) { (void) s;  return 16; }
static uint32_t nipar(sd_sys *s) { (void) s;  return 0; }

static sd_stat apply(sd_sys *s, sd_sys_in *in, sd_sys_out *out)
{
	struct hmje_pars *d = &(((struct hmje*) s->ptr)->pars);
	double *x = in->x, *c = in->i, *f = out->f, *g = out->g, *o = out->o;
	double f_0_aux, f_2_aux, f_4_aux;

	/* pop 1 */
	if (x[0] < 0.0) 
		f_0_aux = -d->a*x[0]*x[0] + d->b*x[0];
	else
		f_0_aux = d->slope - x[3] + 0.6 * pow(x[2] - 4.0, 2);

	f[0] = d->tt*(x[1] - x[2] + d->Iext + d->Kvf * c[0] + f_0_aux * x[0]);
	f[1] = d->tt*(d->c - d->d*pow(x[0], 2) - x[1]);

	/* energy */
	if (x[2] < 0.0)
		f_2_aux = -0.1 * pow(x[2], 7);
	else
		f_2_aux = 0.0;

	f[2] = d->tt*(d->r * (4 * (x[0] - d->x0) - x[2] + f_2_aux + d->Ks * c[0]));

	/* pop 2 */
	if (x[3] < -0.25)
		f_4_aux = 0.0;
	else
		f_4_aux = d->aa * (x[3] + 0.25);

	f[3] = d->tt*(-x[4] + x[3] - pow(x[3], 3) + d->Iext2 + 2 * x[5] - 0.3 * (x[2] - 3.5) + d->Kf * c[1]);
	f[4] = d->tt*((-x[4] + f_4_aux) / d->tau);

	/* lpf */
	f[5] = d->tt*(-0.01 * (x[5] - 0.1*x[0]));

	    /* noise on first & second subsystems only */
	g[0] = d->D1;
	g[1] = d->D1;
	g[2] = 0.0;
	g[3] = d->D2;
	g[4] = d->D2;
	g[5] = 0.0;

        /* x1 and x2 serve as coupling variables */
	o[0] = x[0];
        o[1] = x[3];
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

static sd_sys * get_sys(struct sd_sys_hmje *r) { return &(((struct hmje*) r->ptr)->sys_if); }

struct sd_sys_hmje hmje_default = {
	.ptr = NULL,
	.free = &free_hmje,
	.sys = &get_sys,
#define LPAR(n, v) .get_##n = &get_##n, .set_##n=&set_##n
#define PAR(n, v) LPAR(n, v),
#include "sys_hmje_pars.h"
#undef LPAR
#undef PAR
};

struct sd_sys_hmje *sd_sys_hmje_new()
{
	struct hmje *r;
	if ((r = sd_malloc(sizeof(struct hmje)))==NULL)
	{
		sd_err("alloc sys hmje failed.");
		return NULL;
	}
	r->pars = default_pars;
	r->hmje_if = hmje_default;
	r->sys_if = sys_default;
	r->sys_if.ptr = r->hmje_if.ptr = r;
	return &(r->hmje_if);
}
