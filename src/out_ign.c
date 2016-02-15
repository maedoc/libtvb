/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	bool ignore_x, ignore_c;
	struct sd_out * next;
	struct sd_out this;
};

static sd_stat apply(sd_out *out, double t, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c)
{
	struct data *d = (struct data *) out->ptr;
	uint32_t nx_=nx, nc_=nc;
	double * restrict x_=x, * restrict c_=c;
	if (d->ignore_x)
	{
		nx_ = 0;
		x_ = NULL;
	}
	if (d->ignore_c)
	{
		nc_ = 0;
		c_ = NULL;
	}
	return d->next->apply(d->next, t, nx_, x_, nc_, c_);
}

static void _free(sd_out *out) { sd_free(out->ptr); }

struct sd_out *
sd_out_new_ign(bool ignore_x, bool ignore_c, struct sd_out *next)
{
	struct data *d;
	if (next==NULL)
	{
		sd_err("NULL next.");
		return NULL;
	}
	if ((d = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc ign data failed.");
		return NULL;
	}
	d->ignore_x = ignore_x;
	d->ignore_c = ignore_c;
	d->next = next;
	d->this.ptr = d;
	d->this.free = &_free;
	d->this.apply = &apply;
	return &(d->this);
}
