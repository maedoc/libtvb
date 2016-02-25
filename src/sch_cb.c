/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include "sch_base.h"

struct data
{
	struct sch_base base;
	void *user_data;
	sd_stat(*user_apply)(void *, double *t, double *, double *);
};

static sd_stat apply(struct sd_sch *sch, double *t, double *x, double *c)
{
	struct data *d = sch->ptr;
	return d->user_apply(d->user_data, t, x, c);
}

static void cb_free(struct sd_sch *sch)
{
	sd_free(sch->ptr);
}

struct sd_sch *
sd_sch_new_cb(
	double dt,
	struct sd_sys *sys,
	struct sd_hist *hist,
	struct sd_rng *rng,
	void *user_data,
	sd_stat(*user_apply)(void *, double *t, double *, double *) )
{
	struct data *d;
	if ((d = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc sch cb failed.");
		return NULL;
	}
	sch_base_init(&(d->base), sys->ndim(sys), dt, sys, hist, rng);
	d->base.sch.ptr = d;
	d->base.sch.ptr = d;
	d->user_data = user_data;
	d->user_apply = user_apply;
	return &d->base.sch;
}
