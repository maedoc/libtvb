/* copyright 2016 Apache 2 sddekit authors */

#include <stdio.h>

#include "sddekit.h"
#include "test.h"

#define SEED 42

TEST(prng, simple) {
	float *x, n;
	sd_prng *prng;

	n = 10000;

	prng = sd_prng_new_default();
	prng->seed(prng, SEED);

	x = (float *) sd_malloc(n * sizeof(float));
	prng->fill_norm(prng, n, x);
	prng->fill_uniform(prng, n, x);

	sd_free(x);
	prng->free(prng);
}


