/* copyright 2016 Apache 2 sddekit authors */

#ifndef SK_HIST_H
#define SK_HIST_H

#include "sk_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque type containing history.
 */
typedef struct sk_hist sk_hist;

/**
 * Allocate a new history instance or NULL if allocation fails.
 */
sk_hist *sk_hist_alloc();

/**
 * Get the largest delayed variable index in history
 *
 * \param h initialized history instance.
 */
int sk_hist_get_maxvi(sk_hist *h);

/**
 * Map a delayed variable index to its compact index.
 *
 * \param h initialized history instance.
 * \param vi index of variable
 * \return index of vi in unique(vi array).
 */
int sk_hist_get_vi2i(sk_hist *h, int vi);

/**
 * Get the number of (unique) delayed variable indices.
 *
 * \param h initialized history instance.
 */
int sk_hist_get_nu(sk_hist *h);

/**
 * Aids in defining a new function to fill a history buffer.
 * See ::sk_hist_filler for details of the type signature.
 * \param name name of function being defined.
 */
#define SK_DEFHFILL(name) int name\
	(void * restrict data, int n, double * restrict t, int * restrict indices, double * restrict buf)

/**
 * Signature of callback to fill a history buffer expected.
 *
 * \param[in] data user data for history filler function.
 * \param[in] n number of elements in the history buffer.
 * \param[in] t vector of time for each element in history buffer.
 * \param[in] indices variable index for each element in history buffer.
 * \param[out] buf history buffer to fill .
 * \return 0 if filler succeeds, 1 if error occurs.
 */
typedef SK_DEFHFILL((*sk_hist_filler));

/**
 * Initialize an history instance.
 *
 * nd is len(afferent), max(vi) implicitly len(efferent)
 *
 * \param h history instance.
 * \param nd number of delayed coupling terms.
 * \param vi efferent index of each delayed coupling term.
 * \param vd delay of each delayed coupling term.
 * \param t0 starting time.
 * \param dt time-step to use in history buffer (need not equal solution dt).
 * \return 0 if init succeeds, 1 if error occurs.
 */
int sk_hist_init(sk_hist * restrict h, int nd, int * restrict vi, double * restrict vd, double t0, double dt);

/**
 * Free memory allocated for history instance.
 *
 * \param h allocated history instance.
 */
void sk_hist_free(sk_hist *h);

/**
 * Fill history buffer with some user defined function of time.
 *
 * \param h initialized history instance.
 * \param filler callback to fill history buffer.
 * \param fill_data user data provided to filler.
 * \return 0 if fill succeeds, 1 if error occurred.
 */
int sk_hist_fill(sk_hist * restrict h, sk_hist_filler filler, void * restrict fill_data);

/**
 * Get delayed data from history buffer.
 *
 * If a and e denote afferent and efferent coupling terms, then 
 * this compute a[i] = e[vi[i]](t - vd[i]).
 *
 * \note len(aff) == nd
 *
 * \param[in,out] h history instance; if NULL, call is no-op.
 * \param[in] t current time.
 * \param[out] aff vector of afferent coupling terms, determined by vi/vd.
 */
void sk_hist_get(sk_hist * restrict h, double t, double * restrict aff);

/**
 * Update history buffer with new data.
 *
 * \note len(eff) == max(vi)
 *
 * \param[in,out] h history instance; if NULL, call is no-op.
 * \param[in] t current time.
 * \param[in] eff vector of efferent coupling terms, determined by system.
 */
void sk_hist_set(sk_hist * restrict h, double t, double * restrict eff);

int sk_hist_nbytes(sk_hist *h);

/**
 * Fills the history with zeros. See ::sk_hist_filler for description of arguments
 * and return.
 */
int sk_hist_zero_filler(void * restrict data, int n, double * restrict t, int * restrict indices, double * restrict buf);

/**
 * Get element of history buffer by linear index
 *
 * \param h history instance.
 * \param index linear index in buffer.
 */
double sk_hist_get_buf_lin(sk_hist *h, int index);

/**
 * Get number of delays in history.
 */
int sk_hist_get_nd(sk_hist *h);

/**
 * Get current time in history.
 *
 * \param h history instance.
 */
double sk_hist_get_t(sk_hist *h);

/**
 * Get time step of history buffer.
 *
 * \param h history instance.
 */
double sk_hist_get_dt(sk_hist *h);

/**
 * Get limit of variable storage in buffer.
 *
 * \param h history instance.
 * \param i index of limit.
 */
int sk_hist_get_lim(sk_hist *h, int i);

/**
 * Get length of variable storage in buffer.
 *
 * \param h history instance.
 * \param i index of limit.
 */
int sk_hist_get_len(sk_hist *h, int i);

/**
 * Get the current pos of delayed variable in buffer.
 *
 * \param h history instance.
 * \param i index of variable.
 */
int sk_hist_get_pos(sk_hist *h, int i);

/**
 * Get unique variable index.
 *
 * \param h history instance.
 * \param i index of variable.
 */
int sk_hist_get_uvi(sk_hist *h, int i);

/**
 * Get max delay for variable.
 *
 * \param h history instance.
 * \param i index of variable.
 */
double sk_hist_get_maxd(sk_hist *h, int i);

/**
 * Get variable index.
 *
 * \param h history instance.
 * \param i index of variable.
 */
int sk_hist_get_vi(sk_hist *h, int i);

/**
 * Get variable delay.
 *
 * \param h history instance.
 * \param i index of variable.
 */
double sk_hist_get_vd(sk_hist *h, int i);

/**
 * Get status of delay buffer. 
 *
 * \note provided for unit tests, not generally useful.
 *
 * \param h history instance.
 */
int sk_hist_buf_is_null(sk_hist *h);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
