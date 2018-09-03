/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

#include "extern/randomkit.h"

struct data
{
	uint32_t seed;
	tvb_rng_mt_state rks;
	struct tvb_rng tvb_rng;
};

/* obj n byte free copy {{{ */

static uint32_t data_n_byte(struct data *data)
{
	(void) data;
	return sizeof(struct data);
}

static struct data *data_copy(struct data *data)
{
	struct data *copy = tvb_malloc(sizeof(struct data));
	if (copy == NULL)
	{
		tvb_err("alloc rng copy failed.");
		return NULL;
	}
	memcpy(copy, data, sizeof(struct data));
	return copy;
}

static void data_free(struct data *data)
{
	tvb_free(data);
}

tvb_declare_tag_functions(tvb_rng)

/* }}} */

/* tvb_rng seed norm uniform fill norm {{{ */

static void rng_seed(struct tvb_rng *tvb_rng, uint32_t seed)
{
	struct data *d = tvb_rng->data;
	d->seed = seed;
	tvb_rng_mt_seed(seed, &d->rks);
}

static double rng_norm(struct tvb_rng *tvb_rng)
{
	struct data *d = tvb_rng->data;
	return tvb_rng_mt_gauss(&(d->rks));
}

static double rng_uniform(struct tvb_rng *tvb_rng)
{
	struct data *d = tvb_rng->data;
	return tvb_rng_mt_random(&(d->rks)) * 1.0 / RK_MAX;
}

static void rng_fill_norm(struct tvb_rng *tvb_rng, uint32_t n, double *x)
{
	uint32_t i;
	struct data *d = tvb_rng->data;
	for (i=0; i<n; i++)
		x[i] = tvb_rng_mt_gauss(&d->rks);
}

/* }}} */

static struct tvb_rng tvb_rng_defaults = {
	tvb_declare_tag_vtable(tvb_rng),
	.seed = &rng_seed,
	.norm = &rng_norm,
	.uniform = &rng_uniform,
	.fill_norm = &rng_fill_norm,
};

struct tvb_rng *
tvb_rng_new_mt(uint32_t seed)
{
	struct data *data;
	if ((data = tvb_malloc(sizeof(struct data))) == NULL)
	{
		tvb_err("alloc rng failed.");
		return NULL;
	}
	data->seed = seed;
	data->tvb_rng = tvb_rng_defaults;
	data->tvb_rng.data = data;
	tvb_rng_mt_seed(seed, &data->rks);
	return &data->tvb_rng;
}

/* vim: foldmethod=marker
 */
