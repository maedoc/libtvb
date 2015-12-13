/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_UTIL_H
#define SK_UTIL_H

#ifdef SKDEBUG
#include "stdio.h"
#endif

#include "randomkit.h"

int sk_util_uniqi(const int n, const int *ints, int *nuniq, int **uints);

int sk_util_fill_gauss(rk_state *rng, int nx, double *x);

#ifdef SKDEBUG
#define SK_MALLOCHECK(ptr) \
	if ((ptr)==NULL) \
		fprintf(stderr, "[sk_util] NULL malloc at %s:%d `%s'\n", __FILE__, __LINE__, #ptr);
#else
#define SK_MALLOCHECK(ptr)  ptr
#endif

#endif
