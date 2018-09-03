/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "test.h"

TEST(arith, sum)
{
	const uint32_t n=10000;
	double x[n];
	struct tvb_rng *rng = tvb_rng_new_default();
	rng->seed(rng, 42);
	for (uint32_t i=0; i<n/2; i++)
		x[n-1-i] = -(x[i] = pow(rng->norm(rng)*10, 8.0));
	tvb_log_info("residual %g", tvb_arith_sum0(n, x));
	tvb_log_info("residual %g", tvb_arith_sum1(n, x));
	for (uint32_t i=0; i<n; i++)
		x[i] = 1.0;
	EXPECT_EQ(0, tvb_arith_sum0(n, x)/n-1.0);
	EXPECT_EQ(0, tvb_arith_sum1(n, x)/n-1.0);
	rng->free(rng);
}
