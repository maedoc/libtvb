/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_HIST_H
#define SK_HIST_H

/**
 * t - time of positions in buffer
 */
typedef struct 
{
	/*           nu+1   nu    nu    nu   nd, maxvi */
	int nd, nu, *lim, *len, *pos, *uvi, *vi, *vi2i, maxvi;
	/*   sum(len)  nu     nd 		*/
	double *buf, *maxd, *del, dt, t;
} sk_hist;

/**
 * Aids in defining a new function to fill a history buffer.
 * See ::sk_hist_filler for details of the type signature.
 * \param name name of function being defined.
 */
#define SK_DEFHFILL(name) void name\
	(void *data, int n, double *t, int *indices, double *buf)

/**
 * Signature of callback to fill a history buffer expected.
 * \param[in] data user data for history filler function
 * \param[in] n number of elements in the history buffer
 * \param[in] t vector of time for each element in history buffer
 * \param[in] indices variable index for each element in history buffer
 * \param[out] buf history buffer to fill 
 */
typedef SK_DEFHFILL((*sk_hist_filler));

void sk_hist_init(sk_hist *h, int nd, int *vi, double *vd, double t0, double dt);

void sk_hist_free(sk_hist *h);

void sk_hist_fill(sk_hist *h, sk_hist_filler filler, void *fill_data);

void sk_hist_get(sk_hist *h, double t, double *c);

void sk_hist_set(sk_hist *h, double t, double *x);

int sk_hist_nbytes(sk_hist *h);

/**
 * Fills the history with zeros.
 */
void sk_hist_zero_filler(void *data, int n, double *t, int *indices, double *buf);

#endif
