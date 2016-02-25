/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "sch_base.h"

struct data {
	struct sch_base base;
	double *fl, *fr, *gl, *gr, *z, *xr, sqrt_dt;
};

static void heun_free(struct sd_sch *sch)
{
	struct data *d = sch->ptr;
	sd_free(d->fl);;
	sd_free(d->fr);;
	sd_free(d->gl);;
	sd_free(d->gr);;
	sd_free(d->z);;
	sd_free(d->xr);;
	sd_free(d);
}

static sd_stat heun_apply(struct sd_sch *sch, double *t, double *x, double *c)
{
	uint32_t i;
	sd_stat stat;
	struct data *d = sch->ptr;
	struct sch_base *b = &(d->base);
	sd_sys_in in = { .t = *t, .nx = b->nx, .x = x, .i = c,
			 .hist = b->hist, .rng = b->rng };
	sd_sys_out out = { .f = d->fl, .g = d->gl, .o = c };
	/* predictor */
	b->hist->get(b->hist, *t, c);
	if ((stat = b->sys->apply(b->sys, &in, &out)) != SD_OK)
		return stat;
	for (i=0; i<b->nx; i++)
		d->xr[i] = x[i] + b->dt * d->fl[i];
	b->hist->set(b->hist, *t, c);
	/* corrector */
	b->hist->get(b->hist, *t + b->dt, c);
	in.t = *t + b->dt;
	in.x = d->xr;
	out.f = d->fr;
	out.g = d->gr;
	if ((stat = b->sys->apply(b->sys, &in, &out)) != SD_OK)
		return stat;
	b->rng->fill_norm(b->rng, b->nx, d->z);
	for (i=0; i<b->nx; i++)
		x[i] += 0.5 * (b->dt*(d->fl[i] + d->fr[i]) 
				+ d->sqrt_dt*(d->gl[i] + d->gr[i])*d->z[i]);
	b->hist->set(b->hist, *t + b->dt, c);
	return 0;
}

struct sd_sch *
sd_sch_new_heun(double dt, struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct data *d, z = {0};
	uint32_t nx = sys->ndim(sys);
	if ((d = sd_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->fl=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->fr=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->gl=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->gr=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->z=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->xr=sd_malloc(sizeof(double)*nx))==NULL
	)
	{
		if (d->fl!=NULL) sd_free(d->fl);;
		if (d->fr!=NULL) sd_free(d->fr);;
		if (d->gl!=NULL) sd_free(d->gl);;
		if (d->gr!=NULL) sd_free(d->gr);;
		if (d->z!=NULL) sd_free(d->z);;
		if (d != NULL) sd_free(d);
		sd_err("alloc for heun scheme failed.");
		return NULL;
	}
	sch_base_init(&(d->base), nx, dt, sys, hist, rng);
	d->base.sch.ptr = d;
	d->base.sch.apply = &heun_apply;
	d->base.sch.free = &heun_free;
	return &(d->base.sch);
}
