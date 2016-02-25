/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "sch_base.h"

struct data { 
	struct sch_base base;
	bool first_call;
	double *f, *g, *z, *eps, lam;
};

static void
emc_free(struct sd_sch *sch)
{
	struct data *d = sch->ptr;
	if (d->f!=NULL) sd_free(d->f);
	if (d->g!=NULL) sd_free(d->g);
	if (d->z!=NULL) sd_free(d->z);
	if (d->eps!=NULL) sd_free(d->eps);
	sd_free(d);
	sd_free(sch);
}

static enum sd_stat emc_apply(struct sd_sch *sch, double *t, double *x, double *c)
{
	uint32_t i;
	enum sd_stat stat;
	double E;
	struct data *d = sch->ptr;
	struct sch_base *b = &(d->base);
	sd_sys_in in = { .t = *t, .nx = b->nx, .x = x, .i = c, 
			 .hist = b->hist, .rng = b->rng };
	sd_sys_out out = {.f=d->f, .g=d->g, .o=c};
	if (d->first_call) {
		b->rng->fill_norm(b->rng, b->nx, d->z);
		if ((stat = b->sys->apply(b->sys, &in, &out)) != SD_OK)
			return stat;
		for (i=0; i<b->nx; i++)
			d->eps[i] = sqrt(d->g[i] * d->lam) * d->z[i];
		d->first_call = false;
	}
	E = exp(-d->lam * b->dt);
	b->rng->fill_norm(b->rng, b->nx, d->z);
	b->hist->get(b->hist, *t, c);
	if ((stat = b->sys->apply(b->sys, &in, &out)) != SD_OK)
		return stat;
	for (i=0; i<b->nx; i++) {
		x[i] += b->dt * (d->f[i] + d->eps[i]);
		d->eps[i] *= E;
		d->eps[i] += sqrt(d->g[i] * d->lam * (1 - E*E)) * d->z[i];
	}
	*t += b->dt;
	b->hist->set(b->hist, *t, c);
	return SD_OK;
}

struct sd_sch *
sd_sch_new_emc(double dt, struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng, double lam)
{
	struct data *d, z={0};
	uint32_t nx = sys->ndim(sys);
	if ((d = sd_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->f=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->g=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->z=sd_malloc(sizeof(double)*nx))==NULL
	 || (d->eps=sd_malloc(sizeof(double)*nx))==NULL
	)
	{
		if (d->f!=NULL) sd_free(d->f);
		if (d->g!=NULL) sd_free(d->g);
		if (d->z!=NULL) sd_free(d->z);
		if (d != NULL) sd_free(d);
		sd_err("alloc for emc scheme failed.");
		return NULL;
	}
	d->first_call = true;
	d->lam = lam;
	sch_base_init(&(d->base), nx, dt, sys, hist, rng);
	d->base.sch.ptr = d;
	d->base.sch.apply = &emc_apply;
	d->base.sch.free = &emc_free;
	return &(d->base.sch);
}
