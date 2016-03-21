/* copyright 2016 Apache 2 sddekit authors */

#include <math.h>
#include "sddekit.h"

struct pars
{
	double
#define PAR(n, v) n,
#define LPAR(n, v) n;
#include "sys/hmje_pars.h"
#undef PAR
#undef LPAR
};

static struct pars default_pars = {
#define LPAR(n, v) .n = v
#define PAR(n, v) LPAR(n, v),
#include "sys/hmje_pars.h"
#undef PAR
#undef LPAR
};

struct data
{
	struct pars pars;
	struct sd_sys sd_sys;
	struct sd_sys_hmje sd_sys_hmje;
};

/* obj free n byte copy */
static void
data_free(struct data *data)
{
    sd_free(data);
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
    struct data *copy = sd_malloc(sizeof(struct data));
    if (copy == NULL)
        sd_err("copy hmje failed.");
    *copy = *data;
    return copy;
}

sd_declare_tag_functions(sd_sys)
sd_declare_tag_functions(sd_sys_hmje)

/* get / set parameters */
#define PAR(n, v) \
	static double get_##n(struct sd_sys_hmje *sys) \
	{ return ((struct data*) sys->data)->pars.n; }\
	static void set_##n(struct sd_sys_hmje *sys, double val) \
	{ ((struct data*) sys->data)->pars.n = val; }
#define LPAR(n, v) PAR(n, v)
#include "sys/hmje_pars.h"
#undef PAR
#undef LPAR

static uint32_t  ndim(struct sd_sys *s) { (void) s;  return 6; }
static uint32_t   ndc(struct sd_sys *s) { (void) s;  return 3; }
static uint32_t  nobs(struct sd_sys *s) { (void) s;  return 2; }
static uint32_t nrpar(struct sd_sys *s) { (void) s;  return 16; }
static uint32_t nipar(struct sd_sys *s) { (void) s;  return 0; }

static enum sd_stat
apply(struct sd_sys *sd_sys, 
    struct sd_sys_in *in, 
    struct sd_sys_out *out)
{
    struct data *data = sd_sys->data;
	struct pars *p = &data->pars;
	double *x = in->state, *c = in->input
         , *f = out->drift, *g = out->diffusion
         , *o = out->output;
	double f_0_aux, f_2_aux, f_4_aux;

	/* pop 1 */
	if (x[0] < 0.0) 
		f_0_aux = -p->a*x[0]*x[0] + p->b*x[0];
	else
		f_0_aux = p->slope - x[3] + 0.6 * pow(x[2] - 4.0, 2);

	f[0] = p->tt*(x[1] - x[2] + p->Iext + p->Kvf * c[0] + f_0_aux * x[0]);
	f[1] = p->tt*(p->c - p->d*pow(x[0], 2) - x[1]);

	/* energy */
	if (x[2] < 0.0)
		f_2_aux = -0.1 * pow(x[2], 7);
	else
		f_2_aux = 0.0;

	f[2] = p->tt*(p->r * (4 * (x[0] - p->x0) - x[2] + f_2_aux + p->Ks * c[0]));

	/* pop 2 */
	if (x[3] < -0.25)
		f_4_aux = 0.0;
	else
		f_4_aux = p->aa * (x[3] + 0.25);

	f[3] = p->tt*(-x[4] + x[3] - pow(x[3], 3) + p->Iext2 + 2 * x[5] - 0.3 * (x[2] - 3.5) + p->Kf * c[1]);
	f[4] = p->tt*((-x[4] + f_4_aux) / p->tau);

	/* lfp */
	f[5] = p->tt*(-0.01 * (x[5] - 0.1*x[0]));

	/* noise on first & second subsystems only */
	g[0] = p->D1;
	g[1] = p->D1;
	g[2] = 0.0;
	g[3] = p->D2;
	g[4] = p->D2;
	g[5] = 0.0;

    /* x1 and x2 serve as coupling variables */
	o[0] = x[0];
    o[1] = x[3];
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

static struct sd_sys *
as_sys(struct sd_sys_hmje *hmje)
{
    struct data *data = hmje->data;
    return &data->sd_sys;
}

struct sd_sys_hmje sd_sys_hmje_defaults = {
	sd_declare_tag_vtable(sd_sys_hmje),
    .as_sys = &as_sys,
#define LPAR(n, v) .get_##n = &get_##n, .set_##n=&set_##n
#define PAR(n, v) LPAR(n, v),
#include "sys/hmje_pars.h"
#undef LPAR
#undef PAR
};

struct sd_sys_hmje *
sd_sys_hmje_new()
{
	struct data *data;
    if ((data = sd_malloc(sizeof(struct data))) == NULL)
    {
        sd_err("alloc hmje failed.");
        return NULL;
    }
    data->pars = default_pars;
    data->sd_sys = sd_sys_defaults;
    data->sd_sys_hmje = sd_sys_hmje_defaults;
    data->sd_sys.data = data->sd_sys_hmje.data = data;
	return &data->sd_sys_hmje;
}
