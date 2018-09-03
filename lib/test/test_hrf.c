/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "test.h"

TEST(hrf, glover) 
{
	double h[30];

	tvb_hrf_glover(30, 1.0, h);

	ASSERT_NEAR(0.33669481233352266, h[5], 1e-15);
	ASSERT_NEAR(-0.086627346331239793, h[12], 1e-15);
}

TEST(hrf, volt1) 
{
	double h[30];

	tvb_hrf_volt1(30, 1.0, h);

	ASSERT_NEAR(1.1600215169875137, h[1], 1e-15);
	ASSERT_NEAR(-0.31379368102799787, h[3], 1e-15);
}
