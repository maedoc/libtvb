/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct data
{
	sd_out out;
	double time;
} data;

static sd_stat apply(sd_out *out, double t, 
	     uint32_t nx, double * restrict x,
	     uint32_t nc, double * restrict c)
{
	(void) nx; (void) x; (void) nc; (void) c;
	data *d = out->ptr;
	return t < d->time ? SD_CONT : SD_STOP;
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
sd_out_new_until(double time)
{
	data *d;
        if ((d = sd_malloc(sizeof(data))) == NULL)
	{
		sd_err("alloc out until failed.");
		return NULL;
	}
	d->out = defaults;
	d->out.ptr = d;
	d->time = time;
	return &(d->out);
}
