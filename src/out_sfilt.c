/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* spatial filter (bank) 
 *
 * xfilts laid out as filter per row, i.e. shape [nfilt nx] & [nfilt nc]
 */

typedef struct sfiltd {
	sd_out_sfilt *sfilt;
	sd_out *out;
	uint32_t nfilt, filtlen;
	double * restrict xfilts, * restrict cfilts, * restrict x, * restrict c;
	sd_out *next_out;
} sfiltd;

uint32_t get_nfilt(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->nfilt; }
uint32_t get_filtlen(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->filtlen; }
double *get_xfilts(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->xfilts; }
double *get_cfilts(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->cfilts; }
double *get_x(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->x; }
double *get_c(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->c; }
sd_out *get_out(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->out; }
sd_out *get_next_out(sd_out_sfilt *out) { return ((sfiltd*)out->ptr)->next_out; }

static sd_stat apply(sd_out *out, double t, 
		   uint32_t nx, double * restrict x,
		   uint32_t nc, double * restrict c)
{
	(void) nx; (void) nc;
	uint32_t i, j;
	sfiltd *d = out->ptr;
	for (i=0; i<d->nfilt; i++) {
		d->x[i] = d->c[i] = 0.0;
		for (j=0; j<d->filtlen; j++) {
			d->x[i] += d->xfilts[i*d->filtlen+j] * x[j];
			d->c[i] += d->cfilts[i*d->filtlen+j] * c[j];
		}
	}
	return d->next_out->apply(d->next_out, t, d->nfilt, d->x, d->nfilt, d->c);
}

void sfilt_free(sd_out *out) {
	sfiltd *d = out->ptr;
	sd_free(d->xfilts);
	sd_free(d->cfilts);
	sd_free(d->x);
	sd_free(d->c);
	sd_free(d->out);
	sd_free(d->sfilt);
	sd_free(d);
}

static sd_out sfilt_out_defaults = {
	.ptr = NULL,
	.apply = &apply,
	.free = &sfilt_free
};

static sd_out_sfilt sfilt_defaults = {
	.ptr = NULL,
	.get_nfilt = &get_nfilt,
	.get_filtlen = &get_filtlen,
	.get_xfilts = &get_xfilts,
	.get_cfilts = &get_cfilts,
	.get_x = &get_x,
	.get_c = &get_c,
	.out = &get_out,
	.get_out = &get_next_out,
};

sd_out_sfilt *
sd_out_sfilt_new(uint32_t nfilt, uint32_t filtlen, 
				 double * restrict xfilts, double * restrict cfilts, 
			     sd_out *next_out)
{
	uint32_t n_filt_bytes;
	sfiltd *d, zd = { 0 };
	n_filt_bytes = nfilt * filtlen * sizeof(double);
	if ((d = sd_malloc(sizeof(sfiltd))) == NULL
		|| (*d = zd, nfilt < 1 || filtlen < 1)
		|| (d->out = sd_malloc(sizeof(sd_out))) == NULL
		|| (d->sfilt = sd_malloc(sizeof(sd_out_sfilt))) == NULL
		|| (d->xfilts = sd_malloc(n_filt_bytes)) == NULL
		|| (d->cfilts = sd_malloc(n_filt_bytes)) == NULL
		|| (d->x = sd_malloc(sizeof(double) * nfilt)) == NULL
		|| (d->c = sd_malloc(sizeof(double) * nfilt)) == NULL
		)
	{
		if (d->xfilts!=NULL) sd_free(d->xfilts);
		if (d->cfilts!=NULL) sd_free(d->cfilts);
		if (d->x!=NULL) sd_free(d->x);
		if (d->sfilt != NULL) sd_free(d->sfilt);
		if (d->out != NULL) sd_free(d->out);
		sd_free(d);
		sd_err("nfilt < 1, filtlen < 1 or memory alloc failed.");
		return NULL;
	}
	d->nfilt = nfilt;
	d->filtlen = filtlen;
	memcpy(d->xfilts, xfilts, n_filt_bytes);
	memcpy(d->cfilts, cfilts, n_filt_bytes);
	d->next_out = next_out;
	*(d->out) = sfilt_out_defaults;
	*(d->sfilt) = sfilt_defaults;
	d->out->ptr = d->sfilt->ptr = d;
	return d->sfilt;
}
