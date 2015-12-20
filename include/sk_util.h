/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_UTIL_H
#define SK_UTIL_H

#include <stdio.h>

#include "randomkit.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sk_restrict should be used anywhere a function takes two or more
 * pointer arguments with same type:
 * http://cellperformance.beyond3d.com/articles/2006/05/demystifying-the-restrict-keyword.html
 * http://stackoverflow.com/a/5948101/5536371
 */
#if defined(__GNUC__) && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#   define restrict __restrict
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#   define restrict __restrict
#else
#   define restrict
#endif

/**
 * Build string of resource file name relative to compile time resource path.
 * Caller should free resulting string when done.
 * \param[in] relname relative name of resource file
 * \param[out] absname absolute name of resource file
 */
void sk_util_res_name(char *relname, char **absname);

int sk_util_uniqi(const int n,
		  const int * restrict ints, 
		  int * restrict nuniq, 
		  int ** restrict uints);

int sk_util_fill_gauss(rk_state *rng, int nx, double *x);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
