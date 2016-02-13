/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* common operation to normalize hrf */

static void normalize(uint32_t n, double *x, double dt)
{
	uint32_t i;
	double sum = 0.0;

	for (i=0; i<n; i++)
		sum += x[i];

	sum *= dt;

	for (i=0; i<n; i++)
		x[i] /= sum;
}

/* Based on Glover 1999 & NiPy source */

typedef struct { double shape, scale, coef; } gamma_params;

static gamma_params compute_gamma_params(double loc, double width)
{
	gamma_params gp = {
		.shape = pow(loc/width, 2.0) * 8 * log(2.0),
		.scale = pow(width, 2.0) / loc / 8 / log(2.0),
	};
	gp.coef = pow(loc, -gp.shape) * exp(loc / gp.scale);
	return gp;
}

static double gamma_eval(double T, gamma_params gp)
{
	double pos = T >= 0 ? 1.0 : 0.0;
	return gp.coef * pow(pos * (T + 1e-14), gp.shape) \
		* exp(-(T + 1e-14)/gp.scale);
}

void sd_hrf_glover(uint32_t n, double *t, double *x)
{
	uint32_t i;
	gamma_params gp1 = compute_gamma_params(5.4, 5.2),
		     gp2 = compute_gamma_params(10.8, 7.35);

	if (n < 2 || t==NULL || x==NULL)
	{
		sd_err("n<2, NULL t or NULL x pointers");
		return ;
	}

	for (i=0; i<n; i++)
		x[i] = gamma_eval(t[i], gp1) - 0.35 * gamma_eval(t[i], gp2);

	normalize(n, x, t[1] - t[0]);
}
