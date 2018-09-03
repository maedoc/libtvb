/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

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
	struct tvb_sys tvb_sys;
	struct tvb_sys_gen2d tvb_sys_gen2d;
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
tvb_declare_tag_functions(tvb_sys_gen2d)

/* get & set parameters */
#define PAR(name, value)\
	static double get_ ## name(struct tvb_sys_gen2d *s)\
		{ return ((struct data *) s->data)->pars.name; } \
	static void set_ ## name(struct tvb_sys_gen2d *s, double new)\
		{ ((struct data *) s->data)->pars.name = new; }
#define LASTPAR(n, v) PAR(n, v)
#include "sys/gen2d_pars.h"
#undef PAR
#undef LASTPAR

static enum tvb_stat 
apply(struct tvb_sys *s, 
    struct tvb_sys_in *in, struct tvb_sys_out *out)
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
		return TVB_OK;
}

static uint32_t  ndim(struct tvb_sys *s) { (void) s;  return 2; }
static uint32_t   ndc(struct tvb_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(struct tvb_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(struct tvb_sys *s) { (void) s;  return 4; }
static uint32_t nipar(struct tvb_sys *s) { (void) s;  return 0; }

static struct tvb_sys tvb_sys_defaults = {
    tvb_declare_tag_vtable(tvb_sys),
    .get_n_dim = &ndim,
    .get_n_in = &ndc,
    .get_n_out = &nobs,
    .get_n_rpar = &nrpar,
    .get_n_ipar = &nipar,
    .apply = &apply
};

static struct tvb_sys *
as_sys(struct tvb_sys_gen2d *tvb_sys_gen2d)
{
    struct data *data = tvb_sys_gen2d->data;
    return &data->tvb_sys;
}

static struct tvb_sys_gen2d tvb_sys_gen2d_defaults = {
    tvb_declare_tag_vtable(tvb_sys_gen2d),
	.as_sys = &as_sys,
#define PAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n,
#define LASTPAR(n, v) .get_##n = &get_##n, .set_##n = &set_##n
#include "sys/gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

struct tvb_sys_gen2d *
tvb_sys_gen2d_new()
{
    struct data *data;
    if ((data = tvb_malloc(sizeof(struct data))) == NULL)
    {
        tvb_err("alloc gen2d failed.");
        return NULL;
    }
    data->tvb_sys = tvb_sys_defaults;
    data->tvb_sys_gen2d = tvb_sys_gen2d_defaults;
    data->pars = pars_defaults;
    data->tvb_sys.data = data->tvb_sys_gen2d.data = data;
    return &data->tvb_sys_gen2d;
}
