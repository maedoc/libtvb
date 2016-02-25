/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "sch_base.h"

struct data {
	struct sch_base base;
	double *f, *g, *z, sqrt_dt;
};

void one_step_free(struct sd_sch *sch)
{
	struct data *d = sch->ptr;
	sd_free(d->f);
	sd_free(d->g);
	sd_free(d->z);
	sd_free(d);
}

/* apply {{{ */

static sd_stat one_step_apply(struct sd_sch *sch, double *t, double *x, double *c)
{
	sd_stat stat;
	struct data *d = sch->ptr;
	d->base.hist->get(d->base.hist, *t, c);
	sd_sys_in in = { .t = *t, .nx = d->base.nx, .x = x, .i = c,
			 .hist = d->base.hist, .rng = d->base.rng };
	sd_sys_out out = {.f=d->f, .g=d->g, .o=c};
	if ((stat=d->base.sys->apply(d->base.sys, &in, &out))!=SD_OK)
		return stat;
	d->base.rng->fill_norm(d->base.rng, d->base.nx, d->z);
	/* compute step & set history */
	return SD_OK;
}

static sd_stat id_apply(struct sd_sch *sch, double *t, double *x, double *c)
{
	uint32_t i;
	sd_stat stat;
	struct data *d = sch->ptr;
	if ((stat = one_step_apply(sch, t, x, c))!=SD_OK)
		return stat;
	for (i=0; i<d->base.nx; i++)
		x[i] = d->f[i] + d->g[i] * d->z[i];
	*t += 1;
	d->base.hist->set(d->base.hist, *t, c);
	return stat;
}

static sd_stat em_apply(struct sd_sch *sch, double *t, double *x, double *c)
{
	uint32_t i;
	sd_stat stat;
	struct data *d = sch->ptr;
	if ((stat = one_step_apply(sch, t, x, c)) != SD_OK)
		return stat;
	for (i=0; i<d->base.nx; i++)
		x[i] += d->base.dt * d->f[i] + d->sqrt_dt * d->g[i] * d->z[i];
	*t += d->base.dt;
	d->base.hist->set(d->base.hist, *t, c);
	return 0;
}

/* }}} */

/* constructors {{{ */

static struct sd_sch *
new_one_step(double dt, struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct data *d, z = {0};;
	/* n_dim, n_in, n_out allocations here, scheme owns it all */
	uint32_t nx = sys->ndim(sys);
	if ((d = sd_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->f = sd_malloc(sizeof(double)*nx)) == NULL
	 || (d->g = sd_malloc(sizeof(double)*nx)) == NULL
	 || (d->z = sd_malloc(sizeof(double)*nx)) == NULL
		) 
	{
		if (d->f!=NULL) sd_free(d->f);
		if (d->g!=NULL) sd_free(d->g);
		if (d != NULL) sd_free(d);
		sd_err("alloc scheme failed.");
		return NULL;
	}
	d->sqrt_dt = sqrt(dt);
	sch_base_init(&(d->base), nx, dt, sys, hist, rng);
	d->base.sch.ptr = d;
	d->base.sch.free = &one_step_free;
	return &d->base.sch;
}

struct sd_sch *
sd_sch_new_id(struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct sd_sch *new = new_one_step(1.0, sys, hist, rng);
	new->apply = &id_apply;
	return new;
}

struct sd_sch *
sd_sch_new_em(double dt, struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct sd_sch *new = new_one_step(dt, sys, hist, rng);
	new->apply = &em_apply;
	return new;
}

/* }}} */

/* vim: foldmethod=marker
 */
