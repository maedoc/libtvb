/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* auto-allocating array */
typedef struct mem_data {
	sd_out out_if;
	sd_out_mem mem_if;
	uint32_t n_sample, capacity, nx, nc;
	double *xs, *cs;
} mem_data;

static uint32_t 
mem_get_n_sample(sd_out_mem *out) 
{ 
	return ((mem_data*) out->ptr)->n_sample; 
}

static uint32_t 
mem_get_nx(sd_out_mem *out) 
{ 
	return ((mem_data*) out->ptr)->nx; 
}

static uint32_t 
mem_get_nc(sd_out_mem *out) 
{ 
	return ((mem_data*) out->ptr)->nc; 
}

static double *
mem_get_xs(sd_out_mem *out) 
{ 
	return ((mem_data*) out->ptr)->xs; 
}

static double *
mem_get_cs(sd_out_mem *out) 
{ 
	return ((mem_data*) out->ptr)->cs; 
}

static sd_out *
mem_get_out(sd_out_mem *out)
{
	return &(((mem_data*)out->ptr)->out_if);
}

static uint32_t
mem_get_capacity(sd_out_mem *out)
{
	return ((mem_data*)out->ptr)->capacity;
}

static void 
mem_free(sd_out *out) 
{
	mem_data *d = out->ptr;
	if (d->xs!=NULL)
		sd_free(d->xs);
	if (d->cs!=NULL)
		sd_free(d->cs);
	sd_free(d);
}

static sd_stat
mem_apply(sd_out *out, double t, 
		   uint32_t nx, double * restrict x,
		   uint32_t nc, double * restrict c)
{
	mem_data *d = out->ptr;
	(void) t;
	if (d->capacity==0) {
		int err;
		/* first alloc */
		d->nx = nx;
		d->nc = nc;
		err = (d->xs = sd_malloc (sizeof(double)*nx))==NULL;
	       	err |= (d->cs = sd_malloc (sizeof(double)*nc))==NULL;
		if (err) {
			sd_err("failed to allocate memory.");
			if (d->xs!=NULL) sd_free(d->xs);
			if (d->cs!=NULL) sd_free(d->cs);
			return SD_ERR;
		}
		d->capacity = 1;
	}
	memcpy(d->xs + d->n_sample*nx, x, sizeof(double)*nx);
	memcpy(d->cs + d->n_sample*nc, c, sizeof(double)*nc);
	d->n_sample++;
	if (d->n_sample==d->capacity) {
		double *x_, *c_;
		/* expand buffer */
		x_ = sd_realloc (d->xs, sizeof(double)*nx*2*d->capacity);
		if (x_==NULL) {
			sd_err("failed to allocate memory.");
			return SD_ERR;
		} else {
			/* save new ptr in case c_ realloc fails, free can still
			 * handle x_ 
			 */
			d->xs = x_;
		}
		c_ = sd_realloc (d->cs, sizeof(double)*nc*2*d->capacity);
		if (c_==NULL) {
			sd_err("failed to allocate memory.");
			return SD_ERR;
		}
		d->capacity *= 2;
		d->xs = x_;
		d->cs = c_;
	}
	return SD_CONT;
}

static sd_out_mem
mem_defaults = { .out = &mem_get_out, .get_nx=&mem_get_nx, .get_nc=&mem_get_nc,
	.get_n_sample=&mem_get_n_sample, .get_capacity=&mem_get_capacity,
	.get_xs=&mem_get_xs, .get_cs=&mem_get_cs
};

static sd_out
mem_out_defaults = { .free = &mem_free,.apply = &mem_apply };

sd_out_mem *
sd_out_mem_new() 
{
	mem_data *d = NULL;
	if ((d = sd_malloc(sizeof(mem_data))) == NULL)
	{
		sd_err("alloc failed for new mem output.");
		return NULL;
	}
	d->xs = NULL;
	d->cs = NULL;
	d->n_sample = 0;
	d->capacity = 0;
	d->mem_if = mem_defaults;
	d->out_if = mem_out_defaults;
	d->out_if.ptr = d->mem_if.ptr = d;
	return &(d->mem_if);
}
