/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <string.h>

#include "sk_out.h"
#include "sk_util.h"
#include "sk_malloc.h"
#include "sk_err.h"

#define RETNULL(p, v) if ((p)==NULL) { \
	sk_err("returning early due to NULL pointer."); \
	return v; \
}

/* write data to file */

struct sk_out_file_data {
	FILE *fd;
	int isstd;
};

sk_out_file_data *sk_out_file_alloc() {
	sk_out_file_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_out_file_data));
	*new = zero;
	return new;
}

int sk_out_file_is_std(sk_out_file_data *d) {
	RETNULL(d, 0);
	return d->isstd;
}

int sk_out_file_from_fname(sk_out_file_data *d, char *fname) {
	RETNULL(d, 1);
	d->fd = fopen(fname, "w");
	if (d->fd==NULL) {
		sk_err("unable to open file for writing.");
		return 1;
	}
	d->isstd = 0;
	return d->fd==NULL;
}

int sk_out_file_from_std(sk_out_file_data *d, FILE *std) {
	RETNULL(d, 1);
	if (!(std==stdout || std==stderr)) {
		sk_err("std file is neither stdout nor stderr");
		return 1;
	}
	d->fd = std;
	d->isstd = 1;
	return 0;
}

SK_DEFOUT(sk_out_file) {
	int i;
	sk_out_file_data *d = data;
	RETNULL(d, 1);
	fprintf(d->fd, "%f %d ", t, nx);
	for (i=0; i<nx; i++) fprintf(d->fd, "%f ", x[i]);
	fprintf(d->fd, "%d ", nc);
	for (i=0; i<nc; i++) fprintf(d->fd, "%f ", c[i]);
	fprintf(d->fd, "\n");
	return 1;
}

void sk_out_file_free(sk_out_file_data *d) {
	if (d==NULL) {
		sk_err("cowardly refusing to free NULL pointer.");
		return;
	}
	if (!(d->isstd))
		fclose(d->fd);
	sk_free(d);
}

/* auto-allocating array */
struct sk_out_mem_data {
	int n_sample, capacity, nx, nc;
	double *xs, *cs;
};

sk_out_mem_data *sk_out_mem_alloc() {
	sk_out_mem_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_out_mem_data));
	*new = zero;
	return new;
}

int sk_out_mem_get_n_sample(sk_out_mem_data *d) {
	return d->n_sample;
}

int sk_out_mem_get_nx(sk_out_mem_data *d) {
	return d->nx;
}

int sk_out_mem_get_nc(sk_out_mem_data *d) {
	RETNULL(d, 0);
	return d->nc;
}

double *sk_out_mem_get_xs(sk_out_mem_data *d) {
	RETNULL(d, NULL);
	return d->xs;
}

double *sk_out_mem_get_cs(sk_out_mem_data *d) {
	RETNULL(d, NULL);
	return d->cs;
}

int sk_out_mem_init(sk_out_mem_data *d) {
	RETNULL(d, 1);
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
		int err;
		/* first alloc */
		d->nx = nx;
		d->nc = nc;
		err = (d->xs = sk_malloc (sizeof(double)*nx))==NULL;
	       	err |= (d->cs = sk_malloc (sizeof(double)*nc))==NULL;
		if (err) {
			sk_err("failed to allocate memory.");
			if (d->xs!=NULL) sk_free(d->xs);
			if (d->cs!=NULL) sk_free(d->cs);
			return 0;
		}
		d->capacity = 1;
	}
	memcpy(d->xs + d->n_sample*nx, x, sizeof(double)*nx);
	memcpy(d->cs + d->n_sample*nc, c, sizeof(double)*nc);
	d->n_sample++;
	if (d->n_sample==d->capacity) {
		double *x_, *c_;
		/* expand buffer */
		x_ = sk_realloc (d->xs, sizeof(double)*nx*2*d->capacity);
		if (x_==NULL) {
			sk_err("failed to allocate memory.");
			return 0;
		} else {
			/* save new ptr in case c_ realloc fails, free can still
			 * handle x_ 
			 */
			d->xs = x_;
		}
		c_ = sk_realloc (d->cs, sizeof(double)*nc*2*d->capacity);
		if (c_==NULL) {
			sk_err("failed to allocate memory.");
			return 0;
		}
		d->capacity *= 2;
		d->xs = x_;
		d->cs = c_;
	}
	return 1;
}

void sk_out_mem_free(sk_out_mem_data *d) {
	RETNULL(d, );
	if (d->xs!=NULL)
		sk_free(d->xs);
	if (d->cs!=NULL)
		sk_free(d->cs);
	sk_free(d);
}

/* split n-ways */

struct sk_out_tee_data {
	int nout;
	sk_out *outs;
	void **outd;
};

sk_out_tee_data *sk_out_tee_alloc() {
	sk_out_tee_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_out_tee_data));
	*new = zero;
	return new;
}

int sk_out_tee_init(sk_out_tee_data *d, int nout) {
	int err;
	d->nout = nout;
	err = (d->outs = sk_malloc (sizeof(sk_out) * nout))==NULL;
	err |= (d->outd = sk_malloc (sizeof(void*) * nout))==NULL;
	if (err) {
		sk_err("unable to allocate memory.");
		if (d->outs!=NULL) sk_free(d->outs);
		if (d->outd!=NULL) sk_free(d->outd);
		return 1;
	}
	return 0;
}

int sk_out_tee_set_out(sk_out_tee_data *d, int i, sk_out out, void *data) {
	RETNULL(d, 1);
	if (i < d->nout) {
		d->outs[i] = out;
		d->outd[i] = data;
		return 0;
	}
	sk_err("out of bounds index for splitter output.");
	return 1;
}

SK_DEFOUT(sk_out_tee) {
	int i, flag;
	sk_out_tee_data *d = data;
	flag = 1;
	for (i=0; i<d->nout; i++)
		flag &= (*(d->outs[i]))(d->outd[i], t, nx, x, nc, c);
	return flag;
}

void sk_out_tee_free(sk_out_tee_data *d) {
	RETNULL(d, );
	sk_free(d->outs);
	sk_free(d->outd);
	sk_free(d);
}

/* temporal average / downsample */

struct sk_out_tavg_data {
	int pos, len;
	double *x, *c, t;
	sk_out out;
	void *outd;
};

sk_out_tavg_data *sk_out_tavg_alloc() {
	sk_out_tavg_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_out_tavg_data));
	*new = zero;
	return new;
}

int sk_out_tavg_init(sk_out_tavg_data *d, int len, sk_out out, void *outd) {
	RETNULL(d, 1);
	d->len = len;
	d->pos = 0;
	d->t = 0.0;
	if (out==NULL) {
		sk_err("tavg passed NULL output.");
		return 1;
	}
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
	flag = 0; 
	if (d->x==NULL) {
		flag = (d->x = sk_malloc (sizeof(double) * nx))==NULL;
		flag |= (d->c = sk_malloc (sizeof(double) * nc))==NULL;
		if (flag) {
			if (d->x) sk_free(d->x);
			if (d->c) sk_free(d->c);
			sk_err("failed to allocate memory for temporal average buffer.");
			return 0;
		}
		ALL(nx) d->x[i] = 0.0;
		ALL(nc) d->c[i] = 0.0;
	}
	flag = 1;
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
	RETNULL(d, );
	if (d->x!=NULL) sk_free(d->x);
	if (d->c!=NULL) sk_free(d->c);
	sk_free(d);
}

/* spatial filter (bank) 
 *
 * xfilts laid out as filter per row, i.e. shape [nfilt nx] & [nfilt nc]
 */

struct sk_out_sfilt_data {
	int nfilt, filtlen;
	double *xfilts, *cfilts, *x, *c;
	sk_out out;
	void *outd;
};

sk_out_sfilt_data *sk_out_sfilt_alloc() {
	sk_out_sfilt_data *new, zero = {0};
	new = sk_malloc (sizeof(sk_out_sfilt_data));
	*new = zero;
	return new;
}

int sk_out_sfilt_init(sk_out_sfilt_data *d, int nfilt, int filtlen, 
		double *xfilts, double *cfilts, sk_out out, void *outd) {
	int nb, err;
	d->nfilt = nfilt;
	d->filtlen = filtlen;
	nb = nfilt * filtlen * sizeof(double);
	err = (d->xfilts = sk_malloc(nb))==NULL;
	err |= (d->cfilts = sk_malloc(nb))==NULL;
	err |= (d->x = sk_malloc (sizeof(double) * nfilt))==NULL;
	err |= (d->c = sk_malloc (sizeof(double) * nfilt))==NULL;
	if (err) {
		if (d->xfilts!=NULL) sk_free(d->xfilts);
		if (d->cfilts!=NULL) sk_free(d->cfilts);
		if (d->x!=NULL) sk_free(d->x);
		if (d->c!=NULL) sk_free(d->c);
		sk_err("failed to allocate memory during spatial filter allocation.");
		return 1;
	}
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
	if (d->xfilts!=NULL) sk_free(d->xfilts);
	if (d->cfilts!=NULL) sk_free(d->cfilts);
	if (d->x!=NULL) sk_free(d->x);
	if (d->c!=NULL) sk_free(d->c);
	sk_free(d);
}

FILE *sk_out_file_get_fd(sk_out_file_data *d) { 
	RETNULL(d, 0);
	return d->fd;
}

int sk_out_mem_get_capacity(sk_out_mem_data *d) {
	RETNULL(d, 0);
       	return d->capacity; 
}

int sk_out_tee_get_nout(sk_out_tee_data *d) { RETNULL(d, 0);  return d->nout; }
int sk_out_tee_outs_is_null(sk_out_tee_data *d) { RETNULL(d, 1);  return d->outs == NULL; }
int sk_out_tee_outd_is_null(sk_out_tee_data *d) { RETNULL(d, 1);  return d->outd == NULL; }
sk_out sk_out_tee_get_out_i(sk_out_tee_data *d, int i) {
       	RETNULL(d, 0);  
	if (i>=0 && i<d->nout)
		return d->outs[i];
	sk_err("out of bounds getting tee out");
	return NULL;
}
void *sk_out_tee_get_outd_i(sk_out_tee_data *d, int i) {
       	RETNULL(d, 0);  
	if (i>=0 && i<d->nout)
		return d->outd[i];
	sk_err("out of bounds getting tee out user data.");
	return NULL;
}
int sk_out_tavg_get_len(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->len; }
int sk_out_tavg_get_pos(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->pos; }
double sk_out_tavg_get_t(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->t; }
sk_out sk_out_tavg_get_out(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->out; }
void *sk_out_tavg_get_outd(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->outd; }
double *sk_out_tavg_get_x(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->x; }
double *sk_out_tavg_get_c(sk_out_tavg_data *d) { RETNULL(d, 0);  return d->c; }
int sk_out_sfilt_get_nfilt(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->nfilt; }
int sk_out_sfilt_get_filtlen(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->filtlen; }
double *sk_out_sfilt_get_xfilts(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->xfilts; }
double *sk_out_sfilt_get_cfilts(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->cfilts; }
double *sk_out_sfilt_get_x(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->x; }
double *sk_out_sfilt_get_c(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->c; }
sk_out sk_out_sfilt_get_out(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->out; }
void *sk_out_sfilt_get_outd(sk_out_sfilt_data *d) { RETNULL(d, 0);  return d->outd; }
