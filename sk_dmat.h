/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_DMAT_H
#define SK_DMAT_H

struct sk_dmat
{
	int m, n;
	double *buf;
};

struct sk_dmat *sk_dmat_from_size(int m, int n);

void sk_dmat_init(struct sk_dmat *m);

void sk_dmat_free(struct sk_dmat *m);

double* sk_dmat_addr(struct sk_dmat *m, int i, int j);

void sk_dmat_set(struct sk_dmat *m, int i, int j, double value);

double sk_dmat_get(struct sk_dmat *m, int i, int j);

int sk_dmat_get_m(struct sk_dmat *m);

int sk_dmat_get_n(struct sk_dmat *m);

#endif
