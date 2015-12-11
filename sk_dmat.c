/* Apache 2.0 INS-AMU 2015 */

#define SKDEBUG

#ifdef SKDEBUG
#include "stdio.h"
#endif

#include "stdlib.h"

#include "sk_dmat.h"
#include "sk_util.h"

static char*
failed_bounds_check_msg = \
 "(i=%d, j=%d) o.o.b. on sk_dmat %p (m=%d, n=%d)\n";

struct sk_dmat *sk_dmat_from_size(int m, int n)
{
	struct sk_dmat *mat;
	SK_MALLOCHECK(mat = malloc (sizeof(struct sk_dmat)));
	mat->m = m;
	mat->n = n;
	sk_dmat_init(mat);
	return mat;
}

void sk_dmat_init(struct sk_dmat *m)
{
	SK_MALLOCHECK(m->buf = (double*) malloc(sizeof(double) * m->n * m->m));
}

void sk_dmat_free(struct sk_dmat *m)
{
	free(m->buf);
}

double* sk_dmat_addr(struct sk_dmat *m, int i, int j)
{
#ifdef SKDEBUG
	if ((i < 0) || (j < 0) || (i >= m->m) || (i >= m->n))
	{
		fprintf(stderr, failed_bounds_check_msg, i, j, m, m->m, m->n);
	}
#endif
	return m->buf + (i * m->m + j);
}

void sk_dmat_set(struct sk_dmat *m, int i, int j, double value)
{
	*sk_dmat_addr(m, i, j) = value;
}

double sk_dmat_get(struct sk_dmat *m, int i, int j)
{
	return *sk_dmat_addr(m, i, j);
}

int sk_dmat_get_m(struct sk_dmat *m)
{
	return m->m;
}

int sk_dmat_get_n(struct sk_dmat *m)
{
	return m->n;
}
