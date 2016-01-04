/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* split n-ways */

typedef struct tee_data {
	sd_out *out;
	sd_out_tee *tee;
	uint32_t nout;
	sd_out **outs; /* these are the outputs we'll call */
} tee_data;

static sd_stat tee_set_out(sd_out_tee *tee, uint32_t i, sd_out *out) {
	tee_data *d = tee->ptr;
	if (i < d->nout) {
		d->outs[i] = out;
		return SD_OK;
	}
	sd_err("out of bounds index for splitter output.");
	return SD_ERR;
}

static sd_stat tee_apply(sd_out *out, double t, 
		  uint32_t nx, double * restrict x,
		  uint32_t nc, double * restrict c)
{
	uint32_t i;
	sd_stat stat;
	tee_data *d = out->ptr;
	sd_out **o = d->outs;
	for (i = 0; i < d->nout; i++, o++)
		if ((stat = ((*o)->apply)(*o, t, nx, x, nc, c)) != SD_CONT)
			return stat;
	return SD_CONT;
}

static void tee_free(sd_out *out)
{
	tee_data *d = out->ptr;
	sd_free(d->outs);
	sd_free(d->out);
	sd_free(d->tee);
	sd_free(d);
	/* TODO not done yet ! */
}

static sd_out * tee_get_out_if(sd_out_tee *out) { return ((tee_data*)out->ptr)->out; }

static uint32_t tee_get_nout(sd_out_tee *tee) { return ((tee_data*)tee->ptr)->nout; }

bool tee_outs_is_null(sd_out_tee *tee) { return ((tee_data*)tee->ptr)->outs == NULL; }

static sd_out * tee_get_out(sd_out_tee *tee, uint32_t i)
{
	tee_data *d = tee->ptr;
	if (i < d->nout)
		return d->outs[i];
	sd_err("out of bounds getting tee out");
	return NULL;
}

static sd_out tee_out_defaults = {
	.ptr = NULL,
	.apply = &tee_apply,
	.free = &tee_free
};

static sd_out_tee tee_defaults = {
	.ptr = NULL,
	.out = &tee_get_out_if,
	.get_nout = &tee_get_nout,
	.outs_is_null = &tee_outs_is_null,
	.set_out = &tee_set_out,
	.get_out = &tee_get_out
};

sd_out_tee *
sd_out_tee_new(uint32_t nout)
{
	tee_data *d, zd = { 0 };
	if ((d = sd_malloc(sizeof(tee_data))) == NULL
		|| (*d = zd, 0)
		|| (d->outs = sd_malloc(sizeof(sd_out) * nout)) == NULL
		|| (d->out = sd_malloc(sizeof(sd_out))) == NULL
		|| (d->tee = sd_malloc(sizeof(sd_out_tee))) == NULL) 
	{
		if (d != NULL)
		{
			if (d->out!=NULL) sd_free(d->out);
			if (d->outs!=NULL) sd_free(d->outs);
			sd_free(d);
		}
		sd_err("alloc for tee failed.");
		return NULL;
	}
	d->nout = nout;
	*(d->out) = tee_out_defaults;
	*(d->tee) = tee_defaults;
	d->tee->ptr = d->out->ptr = d;
	return d->tee;
}
