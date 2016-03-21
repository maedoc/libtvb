/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
    uint32_t n_in;
	struct sd_sys sd_sys;
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
        sd_err("copy sys savg failed.");
    *copy = *data;
    return copy;
}

sd_declare_tag_functions(sd_sys)

static enum sd_stat
apply(struct sd_sys *sys,
    struct sd_sys_in *in, struct sd_sys_out *out)
{
	struct data *data = sys->data;
	out->drift[0] = 0.0;
	out->diffusion[0] = 0.0;
	in->state[0] = 0.0;
    double sum = 0.0;
	for (uint32_t i=0; i<data->n_in; i++)
		sum += in->input[i];
    out->output[0] = in->state[0] = sum * 1.0 / data->n_in;
	return SD_OK;
}

static uint32_t  ndim(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t  nobs(struct sd_sys *s) { (void) s;  return 1; }
static uint32_t nrpar(struct sd_sys *s) { (void) s;  return 0; }
static uint32_t nipar(struct sd_sys *s) { (void) s;  return 0; }

static uint32_t n_in(struct sd_sys *sd_sys)
{
    return ((struct data *) sd_sys->data)->n_in;
}

static struct sd_sys sd_sys_defaults = {
	sd_declare_tag_vtable(sd_sys),
    .get_n_dim = &ndim,
    .get_n_in = &n_in,
    .get_n_out = &nobs,
    .get_n_rpar = &nrpar,
    .get_n_ipar = &nipar,
    .apply = &apply
};

struct sd_sys *
sd_sys_new_mean(uint32_t n_in)
{
    struct data *data;
    if ((data = sd_malloc(sizeof(struct data))) == NULL)
    {
        sd_err("alloc sys mean failed.");
        return NULL;
    }
    data->n_in = n_in;
    data->sd_sys = sd_sys_defaults;
    data->sd_sys.data = data;
    return &data->sd_sys;
}
