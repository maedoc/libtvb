/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

double
sd_arith_sum0(uint32_t n, double *x)
{
	double sum = 0.0;
	for (uint32_t i=0; i<n; i++)
		sum += x[i];
	return sum;
}

double
sd_arith_sum1(uint32_t n, double *x)
{
	if (n > 1)
		return sd_arith_sum1(n/2, x)
		     + sd_arith_sum1(n - n/2, x + n/2);
	return *x;
}
