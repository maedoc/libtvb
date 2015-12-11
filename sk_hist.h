/* Apache 2.0 INS-AMU 2015 */
#ifndef SK_HIST_H
#define SK_HIST_H

/**
 * t - time of positions in buffer
 */
struct sk_hist 
{
	/*           nu+1   nu    nu    nu   nd, maxvi */
	int nd, nu, *lim, *len, *pos, *uvi, *vi, *vi2i, maxvi;
	/*   sum(len)  nu     nd 		*/
	double *buf, *maxd, *del, dt, t;
};

typedef void(*sk_hist_filler)(int n, double *t, int *indices, double *buf);

void sk_hist_init(struct sk_hist *h, int nd, int *vi, double *vd, double dt);

void sk_hist_free(struct sk_hist *h);

void sk_hist_fill(struct sk_hist *h, sk_hist_filler filler);

void sk_hist_get(struct sk_hist *h, double t, double *c);

void sk_hist_set(struct sk_hist *h, double t, double *x);

int sk_hist_nbytes(struct sk_hist *h);

#endif
