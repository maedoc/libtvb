/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_IMAT_H
#define SK_IMAT_H

struct sk_imat
{
	int m, n;
	double *buf;
};

struct sk_imat *sk_imat_from_size(int m, int n);

void sk_imat_init(struct sk_imat *m);

void sk_imat_free(struct sk_imat *m);

double* sk_imat_addr(struct sk_imat *m, int i, int j);

void sk_imat_set(struct sk_imat *m, int i, int j, double value);

double sk_imat_get(struct sk_imat *m, int i, int j);

int sk_imat_get_m(struct sk_imat *m);

int sk_imat_get_n(struct sk_imat *m);

#endif
