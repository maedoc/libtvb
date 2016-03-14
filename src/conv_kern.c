/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

void sd_conv_kern_flat(uint32_t n, double *kernel)
{
	double value = 1.0 / n;
	for (uint32_t i=0; i<n; i++)
		kernel[i] = value;
}

void sd_conv_kern_hanning(uint32_t n, double *kernel)
{
	double inv_n_m_1 = 1.0 / (n - 1.0);
	for (uint32_t i=0; i<n; i++)
		kernel[i] = 0.5 * (1.0 - cos(2.0 * M_PI * i * inv_n_m_1));
}

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

void sd_hrf_glover(uint32_t n, double dt, double *x)
{
	uint32_t i;
	gamma_params gp1 = compute_gamma_params(5.4, 5.2),
		     gp2 = compute_gamma_params(10.8, 7.35);

	if (n < 2 || dt<=0.0 || x==NULL)
	{
		sd_err("n<2, non-positive dt or NULL x pointers");
		return ;
	}

	for (i=0; i<n; i++)
		x[i] = gamma_eval(i * dt, gp1) - 0.35 * gamma_eval(i * dt, gp2);

	normalize(n, x, dt);
}

void sd_hrf_volt1(uint32_t n, double dt, double *x)
{
	uint32_t i;
	double tau_s = 0.8,
	       tau_f = 0.4,
	       k_1 = 5.6,
	       V_0 = 0.02;

	(void) k_1; (void) V_0;

	if (n < 2 || dt<=0.0 || x==NULL)
	{
		sd_err("n<2, non-positive dt or NULL x pointers");
		return ;
	}

	for (i=0; i<n; i++)
		x[i] = 1/3. * exp(-0.5*((i * dt) / tau_s))  \
			* (sin(sqrt(1./tau_f - 1./(4.*pow(tau_s, 2))) * (i * dt)))  \
			/ (sqrt(1./tau_f - 1./(4.*pow(tau_s, 2))));

	normalize(n, x, dt);
}
