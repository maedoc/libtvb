/* Apache 2.0 INS-AMU 2015 */

#define SKDEBUG

#ifdef SKDEBUG
#include "stdio.h"
#endif

#include "stdlib.h"

#include "sk_imat.h"
#include "sk_util.h"

static char*
failed_bounds_check_msg = \
 "(i=%d, j=%d) o.o.b. on sk_imat %p (m=%d, n=%d)\n";

struct sk_imat *sk_imat_from_size(int m, int n)
{
	struct sk_imat *mat;
	SK_MALLOCHECK(mat = malloc (sizeof(struct sk_imat)));
	mat->m = m;
	mat->n = n;
	sk_imat_init(mat);
	return mat;
}

void sk_imat_init(struct sk_imat *m)
{
	SK_MALLOCHECK(m->buf = (double*) malloc(sizeof(double) * m->n * m->m));
}

void sk_imat_free(struct sk_imat *m)
{
	free(m->buf);
}

double* sk_imat_addr(struct sk_imat *m, int i, int j)
{
#ifdef SKDEBUG
	if ((i < 0) || (j < 0) || (i >= m->m) || (i >= m->n))
	{
		fprintf(stderr, failed_bounds_check_msg, i, j, m, m->m, m->n);
	}
#endif
	return m->buf + (i * m->m + j);
}

void sk_imat_set(struct sk_imat *m, int i, int j, double value)
{
	*sk_imat_addr(m, i, j) = value;
}

double sk_imat_get(struct sk_imat *m, int i, int j)
{
	return *sk_imat_addr(m, i, j);
}

int sk_imat_get_m(struct sk_imat *m)
{
	return m->m;
}

int sk_imat_get_n(struct sk_imat *m)
{
	return m->n;
}
