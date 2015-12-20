/* Apache 2.0 INS-AMU 2015 */

#include <math.h>

#include <stdlib.h>

#include "sk_scheme.h"
#include "sk_malloc.h"

int sk_sch_id_init(sk_sch_id_data *d, int nx)
{
	d->f=sk_malloc(sizeof(double)*nx);
	d->g=sk_malloc(sizeof(double)*nx);
	d->z=sk_malloc(sizeof(double)*nx);
	return 0;
}

void sk_sch_id_free(sk_sch_id_data *d)
{
	sk_free(d->f);
	sk_free(d->g);
	sk_free(d->z);
}

SK_DEFSCH(sk_sch_id) {
	int i;
	sk_sch_id_data *d;
	/* unused */ (void) dt;
	d = data;
	sk_hist_get(hist, t, c);	      /*  Jf    Jg           Jc */
	(*sys)(sysd, hist, t, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL);
	sk_util_fill_gauss(rng, nx, d->z);
	for (i=0; i<nx; i++)
		x[i] = d->f[i] + d->g[i] * d->z[i];
	sk_hist_set(hist, t, c);
	return 0;
}

int sk_sch_em_init(sk_sch_em_data *d, int nx)
{
	d->f=sk_malloc(sizeof(double)*nx);
	d->g=sk_malloc(sizeof(double)*nx);
	d->z=sk_malloc(sizeof(double)*nx);
	return 0;
}

void sk_sch_em_free(sk_sch_em_data *d)
{
	sk_free(d->f);
	sk_free(d->g);
	sk_free(d->z);
}

SK_DEFSCH(sk_sch_em)
{
	int i;
	double sqrt_dt;
	sk_sch_em_data *d = data;
	sk_hist_get(hist, t, c);	     /*  Jf    Jg           Jc */
	(*sys)(sysd, hist, t, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL);
	sk_util_fill_gauss(rng, nx, d->z);
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += dt * d->f[i] + sqrt_dt * d->g[i] * d->z[i];
	sk_hist_set(hist, t, c);
	return 0;
}

int sk_sch_emcolor_init(sk_sch_emcolor_data *d, int nx, double lam)
{
	d->f=sk_malloc(sizeof(double)*nx);
	d->g=sk_malloc(sizeof(double)*nx);
	d->z=sk_malloc(sizeof(double)*nx);
	d->eps=sk_malloc(sizeof(double)*nx);
	d->first_call = 1;
	d->lam = lam;
	return 0;
}

void sk_sch_emcolor_free(sk_sch_emcolor_data *d)
{
	sk_free(d->f);
	sk_free(d->g);
	sk_free(d->z);
	sk_free(d->eps);
}

SK_DEFSCH(sk_sch_emcolor)
{
	int i;
	double E; /* not stored so can be chaned while running */
	sk_sch_emcolor_data *d = data;
	if (d->first_call) {
		sk_util_fill_gauss(rng, nx, d->z);      /*  Jf    Jg           Jc */
		(*sys)(sysd, hist, t-dt, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL);
		for (i=0; i<nx; i++)
			d->eps[i] = sqrt(d->g[i] * d->lam) * d->z[i];
		d->first_call = 0;
	}
	E = exp(-d->lam * dt);
	sk_util_fill_gauss(rng, nx, d->z);
	sk_hist_get(hist, t, c);	     /*  Jf    Jg           Jc */
	(*sys)(sysd, hist, t, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL);
	for (i=0; i<nx; i++) {
		x[i] += dt * (d->f[i] + d->eps[i]);
		d->eps[i] *= E;
		d->eps[i] += sqrt(d->g[i] * d->lam * (1 - E*E)) * d->z[i];
	}
	sk_hist_set(hist, t, c);
	return 0;
}


int sk_sch_heun_init(sk_sch_heun_data *d, int nx)
{
	d->fl=sk_malloc(sizeof(double)*nx);
	d->fr=sk_malloc(sizeof(double)*nx);
	d->gl=sk_malloc(sizeof(double)*nx);
	d->gr=sk_malloc(sizeof(double)*nx);
	d->z=sk_malloc(sizeof(double)*nx);
	d->xr=sk_malloc(sizeof(double)*nx);
	return 0;
}

void sk_sch_heun_free(sk_sch_heun_data *d)
{
	sk_free(d->fl);
	sk_free(d->fr);
	sk_free(d->gl);
	sk_free(d->gr);
	sk_free(d->z);
	sk_free(d->xr);
}

SK_DEFSCH(sk_sch_heun)
{
	int i;
	double sqrt_dt;
	sk_sch_heun_data *d = data;
	/* predictor */
	sk_hist_get(hist, t, c);	     /*    Jf    Jg           Jc */
	(*sys)(sysd, hist, t, 0, nx, x, d->fl, d->gl, NULL, NULL, nc, c, NULL);
	for (i=0; i<nx; i++)
		d->xr[i] = x[i] + dt * d->fl[i];
	sk_hist_set(hist, t, c);
	/* corrector */
	sk_hist_get(hist, t+dt, c);	            /*    Jf    Jg           Jc */
	(*sys)(sysd, hist, t+dt, 0, nx, d->xr, d->fr, d->gr, NULL, NULL, nc, c, NULL);
	sk_util_fill_gauss(rng, nx, d->z);
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += 0.5 * (dt*(d->fl[i] + d->fr[i]) 
				+ sqrt_dt*(d->gl[i] + d->gr[i])*d->z[i]);
	/* TODO double check this has an effect */
	sk_hist_set(hist, t+dt, c);
	return 0;
}
