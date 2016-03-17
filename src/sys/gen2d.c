/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* parameters & defaults */
struct pars {
		double 
#define PAR(n, v) n,
#define LASTPAR(n, v) n;
#include "sys/gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

static struct pars pars_defaults = {
#define PAR(name, value) .name = value,
#define LASTPAR(name, value) .name = value
#include "sys/gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

struct data
{
	struct sd_sys sd_sys;
	struct sd_sys_gen2d sd_sys_gen2d;
	struct pars pars;
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
        sd_err("copy gen2d failed.");
    *copy = *data;
    return copy;
}

sd_declare_tag_functions(sd_sys)
sd_declare_tag_functions(sd_sys_gen2d)

/* get & set parameters */
#define PAR(name, value)\
	static double get_ ## name(struct sd_sys_gen2d *s)\
		{ return ((struct data *) s->data)->pars.name; } \
	static void set_ ## name(struct sd_sys_gen2d *s, double new)\
		{ ((struct data *) s->data)->pars.name = new; }
#define LASTPAR(n, v) PAR(n, v)
#include "sys/gen2d_pars.h"
#undef PAR
#undef LASTPAR

static enum sd_stat 
apply(struct sd_sys *s, 
    struct sd_sys_in *in, struct sd_sys_out *out)
{
		struct pars *p = &((struct data*) s->data)->pars;
		double *x = in->state, *c = in->input, *f = out->drift
             , *g = out->diffusion, *o = out->output;
		double V = x[0], W = x[1];
		double V2 = V * V;
		f[0] = p->d * p->tau * (p->alpha * W - p->f*V2*V + p->e*V2 + p->g * V + p->gamma * (p->I + c[0]));
		f[1] = p->d * (p->a + p->b * V + p->c * V2 - p->beta * W) / p->tau;
		g[0] = p->D;
		g[1] = p->D;
		o[0] = x[0];
		return SD_OK;
}

static uint32_t  ndim(struct sd_sys *s) { (void) s;  return 2; }
static uint32_t   ndc(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(struct sd_sys *s) { (void) s;  return 4; }
static uint32_t nipar(struct sd_sys *s) { (void) s;  return 0; }

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
as_sys(struct sd_sys_gen2d *sd_sys_gen2d)
{
    struct data *data = sd_sys_gen2d->data;
    return &data->sd_sys;
}

static struct sd_sys_gen2d sd_sys_gen2d_defaults = {
    sd_declare_tag_vtable(sd_sys_gen2d),
	.as_sys = &as_sys,
#define PAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n,
#define LASTPAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n
#include "sys/gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

struct sd_sys_gen2d *
sd_sys_gen2d_new()
{
    struct data *data;
    if ((data = sd_malloc(sizeof(struct data))) == NULL)
    {
        sd_err("alloc gen2d failed.");
        return NULL;
    }
    data->sd_sys = sd_sys_defaults;
    data->sd_sys_gen2d = sd_sys_gen2d_defaults;
    data->pars = pars_defaults;
    data->sd_sys.data = data->sd_sys_gen2d.data = data;
    return &data->sd_sys_gen2d;
}
