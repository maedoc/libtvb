/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "randomkit.h"

struct rng_data {
	uint64_t ncall;
	uint32_t seed;
	rk_state rks;
};

static void rng_seed(sd_rng *r, uint32_t seed)
{
	struct rng_data *d = r->ptr;
	d->seed = seed;
	d->ncall = 0;
	rk_seed(seed, &d->rks);
}

static double rng_norm(sd_rng *r)
{
	struct rng_data *d = r->ptr;
	return rk_gauss(&(d->rks));
}

static double rng_uniform(sd_rng *r)
{
	struct rng_data *d = r->ptr;
	return rk_random(&(d->rks)) * 1.0 / RK_MAX;
}

static void rng_fill_norm(sd_rng *r, uint32_t n, double *x)
{
	uint32_t i;
	struct rng_data *d = r->ptr;
	for (i=0; i<n; i++)
		x[i] = rk_gauss(&d->rks);
}

static void rng_free(sd_rng *r)
{
	sd_free(r->ptr);
	sd_free(r);
}

static uint32_t rng_nbytes(sd_rng *r)
{
	(void) r;
	return sizeof(struct rng_data) + sizeof(sd_rng);
}

static sd_rng rng_default = {
	.ptr = NULL,
	.seed = &rng_seed,
	.norm = &rng_norm,
	.uniform = &rng_uniform,
	.fill_norm = &rng_fill_norm,
	.nbytes = &rng_nbytes,
	.free = &rng_free
};

sd_rng *sd_rng_new_default()
{
	sd_rng *r;
    if ((r = sd_malloc (sizeof(sd_rng))) == NULL
	 || (*r = rng_default, 0)
	 || (r->ptr = sd_malloc (sizeof(struct rng_data))) == NULL)
	{
		sd_free(r);
		sd_err("alloc rng failed.");
		return NULL;
	}
	return r;
}
