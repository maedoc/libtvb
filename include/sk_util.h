/* copyright 2016 Apache 2 sddekit authors */

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
 *
 * \note Caller must sk_free resulting string when done.
 *
 * \param[in] relname relative name of resource file.
 * \param[out] absname absolute name of resource file.
 */
void sk_util_res_name(char *relname, char **absname);

/**
 * Obtain unique sorted integers.
 *
 * \note Caller must free uints when done.
 *
 * \param n number of elements
 * \param ints array of at least n integers.
 * \param[out] nuniq address of number of unique integers.
 * \param[out] uints address of array of unique integers.
 * \return Returns 0 if call succeeds, 1 if error occurs.
 */
int sk_util_uniqi(const int n,
		  const int * restrict ints, 
		  int * restrict nuniq, 
		  int ** restrict uints);

/**
 * Fill buffer with random values from a normal distibution of zero mean and
 * unit standard deviation.
 *
 * \param rng random number generator state.
 * \param nx number of elements in x to fill.
 * \param x array with at least nx elements to write numbers to.
 */
void sk_util_fill_gauss(rk_state *rng, int nx, double *x);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
