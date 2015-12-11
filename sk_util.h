/* Apache 2.0 INS-AMU 2015 */
#ifndef SK_UTIL_H
#define SK_UTIL_H

#ifdef SKDEBUG
#include "stdio.h"
#endif

int sk_util_uniqi(const int n, const int *ints, int *nuniq, int **uints);

#ifdef SKDEBUG
#define SK_MALLOCHECK(ptr) \
	if ((ptr)==NULL) \
		fprintf(stderr, "malloc failed at %s:%d\n", __FILE__, __LINE__);
#else
#define SK_MALLOCHECK(ptr) 
#endif

#endif
