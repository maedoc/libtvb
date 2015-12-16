/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <string.h>

#include "sk_out.h"
#include "sk_util.h"

/* write data to file */


int sk_out_file_from_fname(sk_out_file_data *d, char *fname) {
	d->fd = fopen(fname, "w");
	d->isstd = 0;
	return d->fd==NULL;
}

int sk_out_file_from_std(sk_out_file_data *d, FILE *std) {
	d->fd = std;
	d->isstd = 1;
	return 0;
}

SK_DEFOUT(sk_out_file) {
	int i;
	sk_out_file_data *d = data;
	fprintf(d->fd, "%f %d ", t, nx);
	for (i=0; i<nx; i++) fprintf(d->fd, "%f ", x[i]);
	fprintf(d->fd, "%d ", nc);
	for (i=0; i<nc; i++) fprintf(d->fd, "%f ", c[i]);
	fprintf(d->fd, "\n");
	return 0;
}

void sk_out_file_free(sk_out_file_data *d) {
	if (!(d->isstd))
		fclose(d->fd);
}

/* auto-allocating array */

int sk_out_mem_init(sk_out_mem_data *d) {
	d->xs = NULL;
	d->cs = NULL;
	d->n_sample = 0;
	d->capacity = 0;
	return 0;
}

SK_DEFOUT(sk_out_mem) {
	sk_out_mem_data *d = data;
	(void) t;
	if (d->capacity==0) {
		/* first alloc */
		SK_MALLOCHECK(d->xs = malloc (sizeof(double)*nx));
		SK_MALLOCHECK(d->cs = malloc (sizeof(double)*nc));
		d->capacity = 1;
	}
	memcpy(d->xs + d->n_sample*nx, x, sizeof(double)*nx);
	memcpy(d->cs + d->n_sample*nc, c, sizeof(double)*nc);
	d->n_sample++;
	if (d->n_sample==d->capacity) {
		double *x_, *c_;
		/* expand buffer */
		x_ = realloc (d->xs, sizeof(double)*nx*2*d->capacity);
		if (x_==NULL)
			return 1;
		c_ = realloc (d->cs, sizeof(double)*nc*2*d->capacity);
		if (c_==NULL)
			return 1;
		d->capacity *= 2;
		d->xs = x_;
		d->cs = c_;
	}
	return 0;
}

void sk_out_mem_free(sk_out_mem_data *d) {
	if (d->xs!=NULL)
		free(d->xs);
	if (d->cs!=NULL)
		free(d->cs);
}

/* split n-ways */

int sk_out_tee_init(sk_out_tee_data *d, int nout) {
	d->nout = nout;
	SK_MALLOCHECK(d->outs = malloc (sizeof(sk_out) * nout));
	SK_MALLOCHECK(d->outd = malloc (sizeof(void*) * nout));
	return 0;
}

int sk_out_tee_set_out(sk_out_tee_data *d, int i, sk_out out, void *data) {
	if (i < d->nout) {
		d->outs[i] = out;
		d->outd[i] = data;
		return 0;
	}
	return 1;
}

SK_DEFOUT(sk_out_tee) {
	int i, flag;
	sk_out_tee_data *d = data;
	flag = 0;
	for (i=0; i<d->nout; i++)
		flag |= (*(d->outs[i]))(d->outd[i], t, nx, x, nc, c);
	return flag;
}

void sk_out_tee_free(sk_out_tee_data *d) {
	free(d->outs);
	free(d->outd);
}

/* temporal average / downsample */

int sk_out_tavg_init(sk_out_tavg_data *d, int len, sk_out out, void *outd) {
	d->len = len;
	d->pos = 0;
	d->t = 0.0;
	d->out = out;
	d->outd = outd;
	d->x = NULL;
	d->c = NULL;
	return 0;
}

SK_DEFOUT(sk_out_tavg) {
	int i;
	int flag;
	sk_out_tavg_data *d;
	d = data;
#define ALL(lim) for(i=0;i<(lim);i++)
	if (d->x==NULL) {
		SK_MALLOCHECK(d->x = malloc (sizeof(double) * nx));
		SK_MALLOCHECK(d->c = malloc (sizeof(double) * nc));
		ALL(nx) d->x[i] = 0.0;
		ALL(nc) d->c[i] = 0.0;
	}
	flag = 0;
	ALL(nx) d->x[i] += x[i];
	ALL(nc) d->c[i] += c[i];
	d->t += t;
	d->pos++;
	if (d->pos==d->len) {
		ALL(nx) d->x[i] /= d->len;
		ALL(nc) d->c[i] /= d->len;
		d->t /= d->len;
		flag = (*(d->out))(d->outd, d->t, nx, d->x, nc, d->c);
		d->pos = 0;
		ALL(nx) d->x[i] = 0.0;
		ALL(nc) d->c[i] = 0.0;
		d->t = 0.0;
	}
#undef ALL
	return flag;
}

void sk_out_tavg_free(sk_out_tavg_data *d) {
	free(d->x);
	free(d->c);
}

/* spatial filter (bank) 
 *
 * xfilts laid out as filter per row, i.e. shape [nfilt nx] & [nfilt nc]
 */

int sk_out_sfilt_init(sk_out_sfilt_data *d, int nfilt, int filtlen, 
		double *xfilts, double *cfilts, sk_out out, void *outd) {
	int nb;
	d->nfilt = nfilt;
	d->filtlen = filtlen;
	nb = nfilt * filtlen * sizeof(double);
	SK_MALLOCHECK(d->xfilts = malloc(nb));
	SK_MALLOCHECK(d->cfilts = malloc(nb));
	SK_MALLOCHECK(d->x = malloc (sizeof(double) * nfilt));
	SK_MALLOCHECK(d->c = malloc (sizeof(double) * nfilt));
	memcpy(d->xfilts, xfilts, nb);
	memcpy(d->cfilts, cfilts, nb);
	d->out = out;
	d->outd = outd;
	return 0;
}

SK_DEFOUT(sk_out_sfilt) {
	int i, j;
	sk_out_sfilt_data *d = data;
	/* unused */ (void) nx; (void) nc;
	for (i=0; i<d->nfilt; i++) {
		d->x[i] = d->c[i] = 0.0;
		for (j=0; j<d->filtlen; j++) {
			d->x[i] += d->xfilts[i*d->filtlen+j] * x[j];
			d->c[i] += d->cfilts[i*d->filtlen+j] * c[j];
		}
	}
	return (*(d->out))(d->outd, t, d->nfilt, d->x, d->nfilt, d->c);
}

void sk_out_sfilt_free(sk_out_sfilt_data *d) {
	free(d->xfilts);
	free(d->cfilts);
	free(d->x);
	free(d->c);
}

