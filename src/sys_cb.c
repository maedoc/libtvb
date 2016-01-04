/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct data {
	sd_sys sys;
	uint32_t ndim, ndc, nobs, nrpar, nipar;
	void *user_data;
	sd_stat (*user_apply)(void*, sd_sys_in*, sd_sys_out*);
} data;

static uint32_t ndim(sd_sys *sys) { return ((data*) sys->ptr)->ndim; }
static uint32_t ndc(sd_sys *sys) { return ((data*) sys->ptr)->ndc; }
static uint32_t nobs(sd_sys *sys) { return ((data*) sys->ptr)->nobs; }
static uint32_t nrpar(sd_sys *sys) { return ((data*) sys->ptr)->nrpar; }
static uint32_t nipar(sd_sys *sys) { return ((data*) sys->ptr)->nipar; }

static void cb_free(sd_sys *sys) { sd_free(sys->ptr); }

static sd_stat apply(sd_sys *sys, sd_sys_in *in, sd_sys_out *out)
{
	data *d = sys->ptr;
	return d->user_apply(d->user_data, in, out);
}

static sd_sys defaults = {
	.ndim = &ndim,
	.ndc = &ndc,
	.nobs = &nobs,
	.nrpar = &nrpar,
	.nipar = &nipar,
	.apply = &apply,
	.free = &cb_free,
	.ptr = NULL
};

sd_sys *
sd_sys_new_cb(uint32_t ndim, uint32_t ndc, uint32_t nobs, 
	uint32_t nrpar, uint32_t nipar,
	void *user_data,
	sd_stat (*user_apply)(void *, sd_sys_in*, sd_sys_out*))
{
	data *d;
        if ((d = sd_malloc(sizeof(data))) == NULL)
	{
		sd_err("alloc sys cb failed.");
		return NULL;
	}
	d->ndim = ndim;
	d->ndc = ndc;
	d->nobs = nobs;
	d->nrpar = nrpar;
	d->nipar = nipar;
	d->sys = defaults;
	d->sys.ptr = d;
	d->user_data = user_data;
	d->user_apply = user_apply;
	return &(d->sys);
}
