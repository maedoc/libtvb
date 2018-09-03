/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
    uint32_t n_in;
	struct tvb_sys tvb_sys;
};

static void
data_free(struct data *data)
{
    tvb_free(data);
}

static uint32_t
data_n_byte(struct data *data)
{
    return sizeof(struct data);
}

static struct data *
data_copy(struct data *data)
{
    struct data *copy = tvb_malloc(sizeof(struct data));
    if (copy == NULL)
        tvb_err("copy sys savg failed.");
    *copy = *data;
    return copy;
}

tvb_declare_tag_functions(tvb_sys)

static enum tvb_stat
apply(struct tvb_sys *sys,
    struct tvb_sys_in *in, struct tvb_sys_out *out)
{
	struct data *data = sys->data;
	out->drift[0] = 0.0;
	out->diffusion[0] = 0.0;
	in->state[0] = 0.0;
    double sum = 0.0;
	for (uint32_t i=0; i<data->n_in; i++)
		sum += in->input[i];
    out->output[0] = in->state[0] = sum * 1.0 / data->n_in;
	return TVB_OK;
}

static uint32_t  ndim(struct tvb_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(struct tvb_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(struct tvb_sys *s) { (void) s;  return 0; }
static uint32_t nipar(struct tvb_sys *s) { (void) s;  return 0; }

static uint32_t n_in(struct tvb_sys *tvb_sys)
{
    return ((struct data *) tvb_sys->data)->n_in;
}

static struct tvb_sys tvb_sys_defaults = {
	tvb_declare_tag_vtable(tvb_sys),
    .get_n_dim = &ndim,
    .get_n_in = &n_in,
    .get_n_out = &nobs,
    .get_n_rpar = &nrpar,
    .get_n_ipar = &nipar,
    .apply = &apply
};

struct tvb_sys *
tvb_sys_new_mean(uint32_t n_in)
{
    struct data *data;
    if ((data = tvb_malloc(sizeof(struct data))) == NULL)
    {
        tvb_err("alloc sys mean failed.");
        return NULL;
    }
    data->n_in = n_in;
    data->tvb_sys = tvb_sys_defaults;
    data->tvb_sys.data = data;
    return &data->tvb_sys;
}
