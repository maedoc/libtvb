/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct data
{
	sd_sch sch;
	uint32_t nx;
	void *user_data;
	sd_stat (*user_apply)(void *, sd_hist *, sd_rng *, sd_sys *,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c);
} data;

static sd_stat apply(sd_sch *sch, sd_hist *hist, sd_rng *rng, sd_sys *sys,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c)
{
	data *d = sch->ptr;
	return d->user_apply(d->user_data, hist, rng, sys, t, dt, nx, x, nc, c);
}

static void cb_free(sd_sch *sch)
{
	sd_free(sch->ptr);
}

static uint32_t get_nx(sd_sch *sch) { return ((data*) sch->ptr)->nx; }

static sd_sch defaults = {
	.ptr = NULL,
	.get_nx = &get_nx,
	.free = &cb_free,
	.apply = &apply
};

SD_API sd_sch *
sd_sch_new_cb(uint32_t nx, void *user_data,
	sd_stat (*user_apply)(void *, sd_hist *, sd_rng *, sd_sys *,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c)
	)
{
	data *d;
        if ((d = sd_malloc(sizeof(data))) == NULL)
	{
		sd_err("alloc sch cb failed.");
		return NULL;
	}
	d->sch = defaults;
	d->sch.ptr = d;
	d->user_data = user_data;
	d->user_apply = user_apply;
	return &(d->sch);
}
