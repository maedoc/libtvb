/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "sch_base.h"

struct data
{ 
	struct sch_base base;
	bool first_call;
	double *f, *g, *z, *eps, lam;
};

/* obj free n byte copy {{{ */

static void
emc_free(struct sd_sch *sch)
{
	struct data *d = sch->data;
	sd_free(d->f);
	sd_free(d->g);
	sd_free(d->z);
	sd_free(d->eps);
	sd_free(d);
	sd_free(sch);
}

static uint32_t
emc_n_byte(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double ) * data->base.n_dim * 4;
	byte_count += sch_base_pointers_n_byte(&data->base);
	return byte_count;
}

static struct sd_sch*
emc_copy(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	struct sch_base *base = &data->base;
	struct sd_sch *copy;
	copy = sd_sch_new_emc(base->dt, data->lam, base->sys, base->hist, base->rng);
	if (copy == NULL)
	{
		sd_err("copy emc sch failed.");
	}
	return copy;
}

/* }}} */

/* apply {{{ */

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

/* }}} */

struct sd_sch *
sd_sch_new_emc(double dt, double lam,
	       struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct data *d, z={0};
	uint32_t n_dim = sys->get_n_dim(sys)
	       , n_in  = sys->get_n_in(sys)
	       , n_out = sys->get_n_out(sys)
	       ;
	if ((d = sd_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->f=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->g=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->z=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->eps=sd_malloc(sizeof(double)*n_dim))==NULL
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
	sch_base_init(&d->base,
		n_dim, n_in, n_out, dt, 
		sys, hist, rng, 
		emc_n_byte, emc_free, emc_copy, emc_apply);
	d->base.sch.data = d;
	return &(d->base.sch);
}

/* vim: foldmethod=marker
 */
