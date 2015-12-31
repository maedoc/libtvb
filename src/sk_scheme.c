/* copyright 2016 Apache 2 sddekit authors */

#include <math.h>

#include <stdlib.h>

#include "sk_scheme.h"
#include "sk_malloc.h"
#include "sk_err.h"

struct sk_sch_id_data {
	double *f, *g, *z;
};

sk_sch_id_data *sk_sch_id_alloc() {
	sk_sch_id_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_sch_id_data));
	*new = zero;
	return new;
}

int sk_sch_id_init(sk_sch_id_data *d, int nx)
{
	int err;
	err = 0;
	err |= (d->f=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->g=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->z=sk_malloc(sizeof(double)*nx))==NULL;
	if (err) {
		if (d->f==NULL) sk_free(d->f);
		if (d->g==NULL) sk_free(d->g);
		if (d->z==NULL) sk_free(d->z);
		sk_err("memory alloc durong sch id init failed.");
		return 1;
	}
	return 0;
}

void sk_sch_id_free(sk_sch_id_data *d)
{
	if (d==NULL) {
		sk_err("returning early due to NULL instance pointer");
		return;
	}
	if (d->f!=NULL) sk_free(d->f);
	if (d->g!=NULL) sk_free(d->g);
	if (d->z!=NULL) sk_free(d->z);
	sk_free(d);
}

SK_DEFSCH(sk_sch_id) {
	int i, err;
	sk_sch_id_data *d;
	/* unused */ (void) dt;
	err = 0;
	d = data;
	sk_hist_get(hist, t, c);	      /*  Jf    Jg           Jc */
	err = (*sys)(sysd, hist, t, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL, NULL);
	if (err)
		return err;
	sk_util_fill_gauss(rng, nx, d->z);
	for (i=0; i<nx; i++)
		x[i] = d->f[i] + d->g[i] * d->z[i];
	sk_hist_set(hist, t, c);
	return 0;
}

struct sk_sch_em_data {
	double *f, *g, *z;
};

sk_sch_em_data *sk_sch_em_alloc() {
	sk_sch_em_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_sch_em_data));
	*new = zero;
	return new;
}

int sk_sch_em_init(sk_sch_em_data *d, int nx)
{
	int err;
	err = 0;
	err |= (d->f=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->g=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->z=sk_malloc(sizeof(double)*nx))==NULL;
	if (err) {
		if (d->f!=NULL) sk_free(d->f);
		if (d->g!=NULL) sk_free(d->g);
		if (d->z!=NULL) sk_free(d->z);
		sk_err("memory alloc durong sch em init failed.");
		return 1;
	}
	return 0;
}

void sk_sch_em_free(sk_sch_em_data *d)
{
	if (d==NULL) {
		sk_err("returning early due to NULL instance pointer");
		return;
	}
	if (d->f!=NULL) sk_free(d->f);
	if (d->g!=NULL) sk_free(d->g);
	if (d->z!=NULL) sk_free(d->z);
	sk_free(d);
}

SK_DEFSCH(sk_sch_em)
{
	int i, err;
	double sqrt_dt;
	sk_sch_em_data *d = data;
	err = 0;
	sk_hist_get(hist, t, c);	     /*  Jf    Jg           Jc */
	err = (*sys)(sysd, hist, t, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL, NULL);
	if (err)
		return 0;
	sk_util_fill_gauss(rng, nx, d->z);
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += dt * d->f[i] + sqrt_dt * d->g[i] * d->z[i];
	sk_hist_set(hist, t, c);
	return 0;
}

struct sk_sch_emcolor_data { 
	int first_call;
	double *f, *g, *z, *eps, lam; 
};

sk_sch_emcolor_data *sk_sch_emcolor_alloc() {
	sk_sch_emcolor_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_sch_emcolor_data));
	*new = zero;
	return new;
}

int sk_sch_emcolor_init(sk_sch_emcolor_data *d, int nx, double lam)
{
	int err;
	err = 0;
	err |= (d->f=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->g=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->z=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->eps=sk_malloc(sizeof(double)*nx))==NULL;
	if (err) {
		if (d->f!=NULL) sk_free(d->f);
		if (d->g!=NULL) sk_free(d->g);
		if (d->z!=NULL) sk_free(d->z);
		if (d->eps!=NULL) sk_free(d->eps);
		sk_err("memory alloc durong sch em color init failed.");
		return 1;
	}
	d->first_call = 1;
	d->lam = lam;
	return 0;
}

void sk_sch_emcolor_free(sk_sch_emcolor_data *d)
{
	if (d==NULL) {
		sk_err("returning early due to NULL instance pointer");
		return;
	}
	if (d->f!=NULL) sk_free(d->f);
	if (d->g!=NULL) sk_free(d->g);
	if (d->z!=NULL) sk_free(d->z);
	if (d->eps!=NULL) sk_free(d->eps);
	sk_free(d);
}

SK_DEFSCH(sk_sch_emcolor)
{
	int i, err;
	double E; /* not stored so can be chaned while running */
	sk_sch_emcolor_data *d = data;
	err = 0;
	if (d->first_call) {
		sk_util_fill_gauss(rng, nx, d->z);      /*  Jf    Jg           Jc */
		err = (*sys)(sysd, hist, t-dt, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL, NULL);
		if (err)
			return err;
		for (i=0; i<nx; i++)
			d->eps[i] = sqrt(d->g[i] * d->lam) * d->z[i];
		d->first_call = 0;
	}
	E = exp(-d->lam * dt);
	sk_util_fill_gauss(rng, nx, d->z);
	sk_hist_get(hist, t, c);	     /*  Jf    Jg           Jc */
	err = (*sys)(sysd, hist, t, 0, nx, x, d->f, d->g, NULL, NULL, nc, c, NULL, NULL);
	if (err)
		return err;
	for (i=0; i<nx; i++) {
		x[i] += dt * (d->f[i] + d->eps[i]);
		d->eps[i] *= E;
		d->eps[i] += sqrt(d->g[i] * d->lam * (1 - E*E)) * d->z[i];
	}
	sk_hist_set(hist, t, c);
	return 0;
}


struct sk_sch_heun_data {
	double *fl, *fr, *gl, *gr, *z, *xr;
};

sk_sch_heun_data *sk_sch_heun_alloc() {
	sk_sch_heun_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_sch_heun_data));
	*new = zero;
	return new;
}

int sk_sch_heun_init(sk_sch_heun_data *d, int nx)
{
	int err;
	err = 0;
	err |= (d->fl=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->fr=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->gl=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->gr=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->z=sk_malloc(sizeof(double)*nx))==NULL;
	err |= (d->xr=sk_malloc(sizeof(double)*nx))==NULL;
	if (err) {
		if (d->fl!=NULL) sk_free(d->fl);;
		if (d->fr!=NULL) sk_free(d->fr);;
		if (d->gl!=NULL) sk_free(d->gl);;
		if (d->gr!=NULL) sk_free(d->gr);;
		if (d->z!=NULL) sk_free(d->z);;
		if (d->xr!=NULL) sk_free(d->xr);;
		sk_err("memory alloc durong sch em init failed.");
		return 1;
	}
	return 0;
}

void sk_sch_heun_free(sk_sch_heun_data *d)
{
	if (d->fl!=NULL) sk_free(d->fl);;
	if (d->fr!=NULL) sk_free(d->fr);;
	if (d->gl!=NULL) sk_free(d->gl);;
	if (d->gr!=NULL) sk_free(d->gr);;
	if (d->z!=NULL) sk_free(d->z);;
	if (d->xr!=NULL) sk_free(d->xr);;
	sk_free(d);
}

SK_DEFSCH(sk_sch_heun)
{
	int i, err;
	double sqrt_dt;
	sk_sch_heun_data *d = data;
	/* predictor */
	sk_hist_get(hist, t, c);	     /*    Jf    Jg           Jc */
	err = (*sys)(sysd, hist, t, 0, nx, x, d->fl, d->gl, NULL, NULL, nc, c, NULL, NULL);
	if (err)
		return err;
	for (i=0; i<nx; i++)
		d->xr[i] = x[i] + dt * d->fl[i];
	sk_hist_set(hist, t, c);
	/* corrector */
	sk_hist_get(hist, t+dt, c);	            /*    Jf    Jg           Jc */
	err = (*sys)(sysd, hist, t+dt, 0, nx, d->xr, d->fr, d->gr, NULL, NULL, nc, c, NULL, NULL);
	if (err)
		return err;
	sk_util_fill_gauss(rng, nx, d->z);
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += 0.5 * (dt*(d->fl[i] + d->fr[i]) 
				+ sqrt_dt*(d->gl[i] + d->gr[i])*d->z[i]);
	/* TODO double check this has an effect */
	sk_hist_set(hist, t+dt, c);
	return 0;
}
