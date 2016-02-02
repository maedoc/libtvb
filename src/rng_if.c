/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

void sd_rng_seed(sd_rng*rng, uint32_t seed)
{
	rng->seed(rng, seed);
}

double sd_rng_norm(sd_rng *rng)
{
	return rng->norm(rng);
}

void sd_rng_fill_norm(sd_rng*rng, uint32_t n, double *x)
{
	rng->fill_norm(rng, n, x);
}

uint32_t sd_rng_nbytes(sd_rng*rng)
{
	return rng->nbytes(rng);
}

void sd_rng_free(sd_rng*rng)
{
	rng->free(rng);
}
