/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* temporal convolution */

typedef struct {
	/* pos of latest sample in buffer, len of buffer */
	uint32_t pos, len;

	/* downsample factor & counter */
	uint32_t ds, ds_count;

	/* length of x & c inputs */
	uint32_t nx, nc;

	/* state, coupling buffers & filter / conv kernel coefs */
	double * restrict x,
	       * restrict c,
	       * restrict x_out,
	       * restrict c_out,
	       * restrict filt;

	/* out to which we'll pass data */
	sd_out *next_out;

	/* this sd_out interface */
	sd_out out_if;

	/* this sd_out_conv interface */
	sd_out_conv conv_if;
} conv;

static void _free(conv *c)
{
	sd_free(c->x);
	sd_free(c->c);
	sd_free(c->x_out);
	sd_free(c->c_out);
	sd_free(c->filt);
	sd_free(c); 
}

static void conv_free(sd_out_conv *c) { _free(c->ptr); }
static void out_free(sd_out *c) { _free(c->ptr); }

static sd_stat apply(sd_out *out, double t, 
		   uint32_t nx, double * restrict x,
		   uint32_t nc, double * restrict c)
{
	sd_stat stat;
	conv *d = out->ptr;
	if (d->x == NULL)
	{
		d->nx = nx;
		d->nc = nc;
		/* first call, alloc buffers */
		if ((d->x = sd_malloc(sizeof(double) * d->len * nx)) == NULL
		 || (d->c = sd_malloc(sizeof(double) * d->len * nc)) == NULL
		 || (d->x_out = sd_malloc(sizeof(double) * nx)) == NULL
		 || (d->c_out = sd_malloc(sizeof(double) * nc)) == NULL
		 ) 
		{
			if (d->x != NULL) sd_free(d->x);
			if (d->c != NULL) sd_free(d->c);
			if (d->x_out != NULL) sd_free(d->x_out);
			sd_err("alloc conv buffers failed.");
			return SD_ERR;
		}
		d->ds_count = d->ds;
		d->pos = d->len - 1; /* so pos resets to 0 on first call */
	}
	/* store sample */
	d->pos++;
	if (d->pos == d->len)
		d->pos = 0;
	memcpy(d->x + d->pos*nx, x, sizeof(double) * nx);
	memcpy(d->c + d->pos*nc, c, sizeof(double) * nc);
	if (--d->ds_count == 0)
	{
		uint32_t i;

		/* zero output buffers */
		for (i=0; i<nx; i++)
			d->x_out[i] = 0.0;
		for (i=0; i<nc; i++)
			d->c_out[i] = 0.0;

		/* integrate over time */
		for (i=0; i<d->len; i++)
		{
			uint32_t ci, fi, j;

			/* circular index on buffer starts at oldest sample, moving forward through time */
			ci = (d->pos + 1 + i) % d->len;

			/* filter index moves backward through time */
			fi = d->len - i - 1;

			/* increment weighted sums */
			for (j=0; j<nx; j++)
				d->x_out[j] += d->filt[fi] * d->x[ci * nx + j];

			for (j=0; j<nc; j++)
				d->c_out[j] += d->filt[fi] * d->c[ci * nc + j];
		
		}
		stat = d->next_out->apply(d->next_out, t, nx, d->x_out, nc, d->c_out);
		if (stat != SD_CONT)
			return stat;
		d->ds_count = d->ds;
	}
	return SD_CONT;
}

static uint32_t get_pos(sd_out_conv *c) { return ((conv*) c->ptr)->pos; }
static uint32_t get_len(sd_out_conv *c) { return ((conv*) c->ptr)->len; }
static uint32_t get_ds(sd_out_conv *c) { return ((conv*) c->ptr)->ds; }
static uint32_t get_ds_count(sd_out_conv *c) { return ((conv*) c->ptr)->ds_count; }
static sd_out *get_next_out(sd_out_conv *c) { return ((conv*) c->ptr)->next_out; }
static uint32_t get_nx(sd_out_conv *c) { return ((conv*) c->ptr)->nx; }
static uint32_t get_nc(sd_out_conv *c) { return ((conv*) c->ptr)->nc; }

static sd_out *get_out_interface(sd_out_conv *out)
{
	return &(((conv*)out->ptr)->out_if);
}

static sd_out_conv conv_defaults = {
	.ptr = NULL,
	.out = &get_out_interface,
	.free = &conv_free,
	.get_pos = &get_pos,
	.get_len = &get_len,
	.get_ds = &get_ds,
	.get_ds_count = &get_ds_count,
	.get_next_out = &get_next_out,
	.get_nx = &get_nx,
	.get_nc = &get_nc
};

static sd_out conv_out_defaults = {
	.ptr = NULL,
	.apply = &apply,
	.free = &out_free
};

sd_out_conv *
sd_out_conv_new(uint32_t len, double *filt, sd_out *out)
{
	uint32_t ds = 1;
	conv *d, z = { 0 };
	if ((d = sd_malloc(sizeof(conv))) == NULL 
	    || (*d = z, out == NULL)
	    || (d->filt = sd_malloc(sizeof(double) * len)) == NULL
	    )
	{
		if (d != NULL) sd_free(d);
		sd_err("alloc fail or NULL next_out.");
		return NULL;
	}
	d->next_out = out;
	d->out_if = conv_out_defaults;
	d->conv_if = conv_defaults;
	d->out_if.ptr = d->conv_if.ptr = d;
	d->len = len;
	d->ds = ds;
	memcpy(d->filt, filt, sizeof(double) * len);
	return &(d->conv_if);
}
