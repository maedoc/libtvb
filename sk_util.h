/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_UTIL_H
#define SK_UTIL_H

#ifdef SKDEBUG
#include "stdio.h"
#endif

#include "randomkit.h"

/* sk_restrict should be used anywhere a function takes two or more
 * pointer arguments with same type:
 * http://cellperformance.beyond3d.com/articles/2006/05/demystifying-the-restrict-keyword.html
 * http://stackoverflow.com/a/5948101/5536371
 */
#if defined(__GNUC__) && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#   define sk_restrict __restrict
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#   define sk_restrict __restrict
#else
#   define sk_restrict
#endif

int sk_util_uniqi(const int n, 
		  const int * sk_restrict ints, 
		  int * sk_restrict nuniq, 
		  int ** sk_restrict uints);

int sk_util_fill_gauss(rk_state *rng, int nx, double *x);

#ifdef SKDEBUG
#define SK_MALLOCHECK(ptr) \
	if ((ptr)==NULL) \
		fprintf(stderr, "[sk_util] NULL malloc at %s:%d `%s'\n", __FILE__, __LINE__, #ptr);
#else
#define SK_MALLOCHECK(ptr)  ptr
#endif


#endif
