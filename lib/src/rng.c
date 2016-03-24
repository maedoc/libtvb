/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "extern/randomkit.h"

struct data
{
	uint32_t seed;
	sd_rng_mt_state rks;
	struct sd_rng sd_rng;
};

/* obj n byte free copy {{{ */

static uint32_t data_n_byte(struct data *data)
{
	(void) data;
	return sizeof(struct data);
}

static struct data *data_copy(struct data *data)
{
	struct data *copy = sd_malloc(sizeof(struct data));
	if (copy == NULL)
	{
		sd_err("alloc rng copy failed.");
		return NULL;
	}
	memcpy(copy, data, sizeof(struct data));
	return copy;
}

static void data_free(struct data *data)
{
	sd_free(data);
}

sd_declare_tag_functions(sd_rng)

/* }}} */

/* sd_rng seed norm uniform fill norm {{{ */

static void rng_seed(struct sd_rng *sd_rng, uint32_t seed)
{
	struct data *d = sd_rng->data;
	d->seed = seed;
	sd_rng_mt_seed(seed, &d->rks);
}

static double rng_norm(struct sd_rng *sd_rng)
{
	struct data *d = sd_rng->data;
	return sd_rng_mt_gauss(&(d->rks));
}

static double rng_uniform(struct sd_rng *sd_rng)
{
	struct data *d = sd_rng->data;
	return sd_rng_mt_random(&(d->rks)) * 1.0 / RK_MAX;
}

static void rng_fill_norm(struct sd_rng *sd_rng, uint32_t n, double *x)
{
	uint32_t i;
	struct data *d = sd_rng->data;
	for (i=0; i<n; i++)
		x[i] = sd_rng_mt_gauss(&d->rks);
}

/* }}} */

static struct sd_rng sd_rng_defaults = {
	sd_declare_tag_vtable(sd_rng),
	.seed = &rng_seed,
	.norm = &rng_norm,
	.uniform = &rng_uniform,
	.fill_norm = &rng_fill_norm,
};

struct sd_rng *
sd_rng_new_mt(uint32_t seed)
{
	struct data *data;
	if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc rng failed.");
		return NULL;
	}
	data->seed = seed;
	data->sd_rng = sd_rng_defaults;
	data->sd_rng.data = data;
	sd_rng_mt_seed(seed, &data->rks);
	return &data->sd_rng;
}

/* vim: foldmethod=marker
 */
