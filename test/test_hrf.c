/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

TEST(hrf, glover) 
{
	uint32_t i, n = 30;
	double dt = 1.0, t[30], h[30];

	for (i=0; i<n; i++) t[i] = i * 1.0;

	sd_hrf_glover(n, t, h);

	ASSERT_NEAR(0.33669481233352266, h[5], 1e-15);
	ASSERT_NEAR(-0.086627346331239793, h[12], 1e-15);
}

TEST(hrf, volt1) 
{
	uint32_t i, n = 30;
	double dt = 1.0, t[30], h[30];

	for (i=0; i<n; i++) t[i] = i * 1.0;

	sd_hrf_volt1(n, t, h);

	ASSERT_NEAR(1.1600215169875137, h[1], 1e-15);
	ASSERT_NEAR(-0.31379368102799787, h[3], 1e-15);
}
