/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* temporal average / downsample */

typedef struct tavg {
	uint32_t pos, len;
	double * restrict x, * restrict c, t;
	sd_out *next_out; /* out we'll call after tavg */
	sd_out out_if; /* sd_out interface to this */
	sd_out_tavg tavg_if;
} tavg;

static uint32_t get_len(sd_out_tavg *out) { return ((tavg*)out->ptr)->len; }
static uint32_t get_pos(sd_out_tavg *out) { return ((tavg*)out->ptr)->pos; }
static double get_t(sd_out_tavg *out) { return ((tavg*)out->ptr)->t; }
static sd_out *get_out(sd_out_tavg *out) { return ((tavg*)out->ptr)->next_out; }
static double *get_x(sd_out_tavg *out) { return ((tavg*)out->ptr)->x; }
static double *get_c(sd_out_tavg *out) { return ((tavg*)out->ptr)->c; }

static void tavg_free(sd_out *out) 
{
	tavg *d = out->ptr;
	sd_free(d->x);
	sd_free(d->c);
	sd_free(d);
}

static sd_stat setup_buffers(tavg *d, uint32_t nx, uint32_t nc)
{
	uint32_t i;
	if ((d->x = sd_malloc (sizeof(double) * nx))==NULL
	 || (d->c = sd_malloc (sizeof(double) * nc))==NULL)
	{
		sd_free(d->x);
		sd_err("failed to allocate memory for temporal average buffer.");
		return SD_ERR;
	}
	for (i = 0; i < nx; i++) 
		d->x[i] = 0.0;
	for (i = 0; i < nc; i++) 
		d->c[i] = 0.0;
	return SD_OK;
}

static sd_stat apply(sd_out *out, double t, 
		   uint32_t nx, double * restrict x,
		   uint32_t nc, double * restrict c)
{
	uint32_t i;
	sd_stat stat;
	tavg *d = out->ptr;
	if (d->x==NULL && setup_buffers(d, nx, nc) != SD_OK) 
	{
		sd_err("failed to setup tavg buffers.");
		return SD_ERR;
	}
	/* sum */
	for (i = 0; i < nx; i++) 
		d->x[i] += x[i];
	for (i = 0; i < nc; i++) 
		d->c[i] += c[i];
	d->t += t;
	d->pos++;
	if (d->pos==d->len) {
		/* div */
		for (i = 0; i < nx; i++) 
			d->x[i] /= d->len;
		for (i = 0; i < nc; i++) 
			d->c[i] /= d->len;
		d->t /= d->len;
		/* pass on to next output */
		if ((stat = d->next_out->apply(d->next_out, d->t, nx, d->x, nc, d->c)) != SD_CONT)
			return stat;
		/* reset for next time window */
		d->pos = 0;
		for (i = 0; i < nx; i++) 
			d->x[i] = 0.0;
		for (i = 0; i < nc; i++) 
			d->c[i] = 0.0;
		d->t = 0.0;
	}
	return SD_CONT;
}

static sd_out *get_out_interface(sd_out_tavg *out)
{
	return &(((tavg*)out->ptr)->out_if);
}

static sd_out_tavg tavg_defaults = {
	.ptr = NULL,
	.out = &get_out_interface,
	.get_len = &get_len,
	.get_pos = &get_pos,
	.get_t = &get_t,
	.get_out = &get_out,
	.get_x = &get_x,
	.get_c = &get_c
};

static sd_out tavg_out_defaults = {
	.ptr = NULL,
	.apply = &apply,
	.free = &tavg_free
};

sd_out_tavg *
sd_out_tavg_new(uint32_t len, sd_out *next_out)
{
	tavg *d, z = { 0 };
	if ((d = sd_malloc(sizeof(tavg))) == NULL
		|| (*d = z, d->next_out = next_out, 0))
	{
		sd_err("alloc fail or NULL next_out.");
		return NULL;
	}
	d->out_if = tavg_out_defaults;
	d->tavg_if = tavg_defaults;
	d->out_if.ptr = d->tavg_if.ptr = d;
	d->len = len;
	return &(d->tavg_if);
}
