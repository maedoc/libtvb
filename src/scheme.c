/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct one_step_data {
    int nx;
	double *f, *g, *z;
	sd_sch sch;
} one_step_data;

static uint32_t one_step_get_nx(sd_sch *s) { return ((one_step_data*)s->ptr)->nx; }

void one_step_free(sd_sch *sch)
{
	one_step_data *d = sch->ptr;
	sd_free(d->f);
	sd_free(d->g);
	sd_free(d->z);
	sd_free(d);
}

static sd_sch *
new_one_step(uint32_t nx)
{
	bool err;
	one_step_data *d;
	if ((d = sd_malloc(sizeof(one_step_data))) == NULL) {
		sd_err("memory alloc for one step sch failed.");
		return NULL;
	}
	{
		one_step_data zero = { 0 };
		*d = zero;
	}
	err = (d->f = sd_malloc(sizeof(double)*nx)) == NULL;
	err |= (d->g = sd_malloc(sizeof(double)*nx)) == NULL;
	err |= (d->z = sd_malloc(sizeof(double)*nx)) == NULL;
	if (err) {
		if (d->f!=NULL) sd_free(d->f);
		if (d->g!=NULL) sd_free(d->g);
		if (d->z!=NULL) sd_free(d->z);
		if (d != NULL) sd_free(d);
		sd_err("memory alloc for one step sch failed.");
		return NULL;
	}
    d->nx = nx;
	d->sch.ptr = d;
	d->sch.get_nx = &one_step_get_nx;
	d->sch.free = &one_step_free;
	return &(d->sch);
}

static sd_stat one_step_apply(
	sd_sch *sch, sd_hist *hist, sd_rng *rng, sd_sys *sys,
	double t, double dt,
	uint32_t nx, double * restrict x,
	uint32_t nc, double * restrict c)
{
	(void) dt;
	sd_stat stat;
	one_step_data *d = sch->ptr;
	hist->get(hist, t, c);
	sd_sys_in in = { .t = t, .nx = nx, .x = x, .nc = nc, .i = c, .hist = hist, .rng = rng };
	sd_sys_out out = {.f=d->f, .g=d->g, .o=c};
	if ((stat=sys->apply(sys, &in, &out))!=SD_OK)
		return stat;
	rng->fill_norm(rng, nx, d->z);
	/* compute step & set history */
	return SD_OK;
}

static sd_stat id_apply(
	    sd_sch *sch, sd_hist *hist, sd_rng *rng, sd_sys *sys,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c)
{
	uint32_t i;
	sd_stat stat;
	one_step_data *d = sch->ptr;
	if ((stat = one_step_apply(sch, hist, rng, sys, t, dt, nx, x, nc, c))!=SD_OK)
		return stat;
	for (i=0; i<nx; i++)
		x[i] = d->f[i] + d->g[i] * d->z[i];
	hist->set(hist, t, c);
	return stat;
}

static sd_stat em_apply(
	    sd_sch *sch, sd_hist *hist, sd_rng *rng, sd_sys *sys,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c)
{
	uint32_t i;
	sd_stat stat;
	double sqrt_dt;
	one_step_data *d = sch->ptr;
	if ((stat = one_step_apply(sch, hist, rng, sys, t, dt, nx, x, nc, c)) != SD_OK)
		return stat;
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += dt * d->f[i] + sqrt_dt * d->g[i] * d->z[i];
	hist->set(hist, t, c);
	return 0;
}


sd_sch *sd_sch_new_id(uint32_t nx)
{
	sd_sch *new = new_one_step(nx);
	new->apply = &id_apply;
	return new;
}

sd_sch *sd_sch_new_em(uint32_t nx)
{
	sd_sch *new = new_one_step(nx);
	new->apply = &em_apply;
	return new;
}


typedef struct emc_data { 
	bool first_call;
	uint32_t nx;
	double *f, *g, *z, *eps, lam; 
} emc_data;

static uint32_t
emc_get_nx(sd_sch *sch) 
{ 
	return ((emc_data*)sch->ptr)->nx;
}

double sd_sch_emc_get_lam(sd_sch *sch) 
{
	return ((emc_data*)sch)->lam;
}

static void
emc_free(sd_sch *sch)
{
	emc_data *d = sch->ptr;
	if (d==NULL) {
		sd_err("returning early due to NULL instance pointer");
		return;
	}
	if (d->f!=NULL) sd_free(d->f);
	if (d->g!=NULL) sd_free(d->g);
	if (d->z!=NULL) sd_free(d->z);
	if (d->eps!=NULL) sd_free(d->eps);
	sd_free(d);
	sd_free(sch);
}

static sd_stat emc_apply(
	sd_sch *sch, sd_hist *hist, sd_rng *rng, sd_sys *sys,
	double t, double dt,
	uint32_t nx, double * restrict x,
	uint32_t nc, double * restrict c)
{
	uint32_t i;
	sd_stat stat;
	double E;
	emc_data *d = sch->ptr;
	sd_sys_in in = { .t = t, .nx = nx, .x = x, .nc = nc, .i = c, .hist = hist, .rng = rng };
	sd_sys_out out = {.f=d->f, .g=d->g, .o=c};
	if (d->first_call) {
		rng->fill_norm(rng, nx, d->z);
		if ((stat = sys->apply(sys, &in, &out)) != SD_OK)
			return stat;
		for (i=0; i<nx; i++)
			d->eps[i] = sqrt(d->g[i] * d->lam) * d->z[i];
		d->first_call = false;
	}
	E = exp(-d->lam * dt);
	rng->fill_norm(rng, nx, d->z);
	hist->get(hist, t, c);
	if ((stat = sys->apply(sys, &in, &out)) != SD_OK)
		return stat;
	for (i=0; i<nx; i++) {
		x[i] += dt * (d->f[i] + d->eps[i]);
		d->eps[i] *= E;
		d->eps[i] += sqrt(d->g[i] * d->lam * (1 - E*E)) * d->z[i];
	}
	hist->set(hist, t, c);
	return SD_OK;
}

sd_sch * sd_sch_new_emc(uint32_t nx, double lam)
{
	bool err;
	emc_data *d;
	sd_sch *sch;
	if ((d = sd_malloc(sizeof(emc_data))) == NULL) {
		sd_err("memory alloc for one step sch failed.");
		return NULL;
	}
	{
		emc_data zero = { 0 };
		*d = zero;
	}
    d->nx = nx;
	err = (sch = sd_malloc(sizeof(sd_sch))) == NULL;
	err |= (d->f=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->g=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->z=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->eps=sd_malloc(sizeof(double)*nx))==NULL;
	if (err) {
		if (d->f!=NULL) sd_free(d->f);
		if (d->g!=NULL) sd_free(d->g);
		if (d->z!=NULL) sd_free(d->z);
		if (d->eps!=NULL) sd_free(d->eps);
		if (d != NULL) sd_free(d);
		if (sch != NULL) sd_free(sch);
		sd_err("memory alloc for sch em color failed.");
		return NULL;
	}
	d->first_call = true;
	d->lam = lam;
	sch->ptr = d;
	sch->get_nx = &emc_get_nx;
	sch->apply = &emc_apply;
	sch->free = &emc_free;
	return sch;
}

typedef struct heun_data {
    int nx;
	double *fl, *fr, *gl, *gr, *z, *xr;
} heun_data;

static uint32_t
heun_get_nx(sd_sch *sch)
{
	return ((heun_data*)sch->ptr)->nx;
}

static void
heun_free(sd_sch *sch)
{
	heun_data *d = sch->ptr;
	sd_free(d->fl);;
	sd_free(d->fr);;
	sd_free(d->gl);;
	sd_free(d->gr);;
	sd_free(d->z);;
	sd_free(d->xr);;
	sd_free(d);
	sd_free(sch);
}

static sd_stat heun_apply(
	sd_sch *sch, sd_hist *hist, sd_rng *rng, sd_sys *sys,
	double t, double dt,
	uint32_t nx, double * restrict x,
	uint32_t nc, double * restrict c)
{
	uint32_t i;
	sd_stat stat;
	double sqrt_dt;
	heun_data *d = sch->ptr;
	sd_sys_in in = { .t = t, .nx = nx, .x = x, .nc = nc, .i = c, .hist = hist, .rng = rng };
	sd_sys_out out = { .f = d->fl, .g = d->gl, .o = c };
	/* predictor */
	hist->get(hist, t, c);
	if ((stat = sys->apply(sys, &in, &out)) != SD_OK)
		return stat;
	for (i=0; i<nx; i++)
		d->xr[i] = x[i] + dt * d->fl[i];
	hist->set(hist, t, c);
	/* corrector */
	hist->get(hist, t + dt, c);
	in.t = t + dt;
	in.x = d->xr;
	out.f = d->fr;
	out.g = d->gr;
	if ((stat = sys->apply(sys, &in, &out)) != SD_OK)
		return stat;
	rng->fill_norm(rng, nx, d->z);
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += 0.5 * (dt*(d->fl[i] + d->fr[i]) 
				+ sqrt_dt*(d->gl[i] + d->gr[i])*d->z[i]);
	hist->set(hist, t + dt, c);
	return 0;
}

sd_sch *
sd_sch_new_heun(uint32_t nx)
{
	bool err;
	heun_data *d;
	sd_sch *sch;
	if ((d = sd_malloc(sizeof(heun_data))) == NULL)
	{
		sd_err("memory alloc for heun scheme failed.");
		return NULL;
	}
	{
		heun_data zero = { 0 };
		*d = zero;
	}
	d->nx = nx;
	err = (sch = sd_malloc(sizeof(sd_sch)))==NULL;
	err |= (d->fl=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->fr=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->gl=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->gr=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->z=sd_malloc(sizeof(double)*nx))==NULL;
	err |= (d->xr=sd_malloc(sizeof(double)*nx))==NULL;
	if (err) {
		if (d->fl!=NULL) sd_free(d->fl);;
		if (d->fr!=NULL) sd_free(d->fr);;
		if (d->gl!=NULL) sd_free(d->gl);;
		if (d->gr!=NULL) sd_free(d->gr);;
		if (d->z!=NULL) sd_free(d->z);;
		if (d->xr!=NULL) sd_free(d->xr);;
		if (d != NULL) sd_free(d);
		if (sch != NULL) sd_free(sch);
		sd_err("memory alloc durong sch em init failed.");
		return NULL;
	}
	sch->ptr = d;
	sch->get_nx = &heun_get_nx;
	sch->apply = &heun_apply;
	sch->free = &heun_free;
	return sch;
}
