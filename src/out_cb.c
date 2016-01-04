/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct data
{
	sd_out out;
	void *user_data;
	sd_stat (*user_apply)(void *, double t, 
	     uint32_t nx, double * restrict x,
	     uint32_t nc, double * restrict c);
} data;

static sd_stat apply(sd_out *out, double t, 
	     uint32_t nx, double * restrict x,
	     uint32_t nc, double * restrict c)
{
	data *d = out->ptr;
	return d->user_apply(d->user_data, t, nx, x, nc, c);
}

static void cb_free(sd_out *out)
{
	sd_free(out->ptr);
}

static sd_out defaults = {
	.ptr = NULL,
	.free = &cb_free,
	.apply = &apply
};

SD_API sd_out *
sd_out_new_cb(void *user_data,
	sd_stat (*user_apply)(void *, double t, 
	     uint32_t nx, double * restrict x,
	     uint32_t nc, double * restrict c))
{
	data *d;
        if ((d = sd_malloc(sizeof(data))) == NULL)
	{
		sd_err("alloc out cb failed.");
		return NULL;
	}
	d->out = defaults;
	d->out.ptr = d;
	d->user_data = user_data;
	d->user_apply = user_apply;
	return &(d->out);
}
