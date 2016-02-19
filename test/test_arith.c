/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

TEST(arith, sum)
{
	const uint32_t n=10000;
	double x[n];
	struct sd_rng *rng = sd_rng_new_default();
	rng->seed(rng, 42);
	for (uint32_t i=0; i<n/2; i++)
		x[n-1-i] = -(x[i] = pow(rng->norm(rng)*10, 8.0));
	sd_log_info("residual %g", sd_arith_sum0(n, x));
	sd_log_info("residual %g", sd_arith_sum1(n, x));
	for (uint32_t i=0; i<n; i++)
		x[i] = 1.0;
	EXPECT_EQ(0, sd_arith_sum0(n, x)/n-1.0);
	EXPECT_EQ(0, sd_arith_sum1(n, x)/n-1.0);
	rng->free(rng);
}
