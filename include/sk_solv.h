/* Apache 2.0 INS-AMU 2015 */

/**
 * sddekit's solver drives time evolution given a system, 
 * a time-stepping scheme and an output handling callback.
 */

#ifndef SK_SOLV_H
#define SK_SOLV_H


#include "randomkit.h"
#include "sk_hist.h"
#include "sk_util.h"
#include "sk_sys.h"
#include "sk_scheme.h"
#include "sk_out.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque type representing a solver instance.
 */
typedef struct sk_solv sk_solv;

/**
 * Allocate memory for a solver instance, or return NULL if allocation fails.
 */
sk_solv *sk_solv_alloc();

/**
 * Initialize a solver.
 *
 * \note References are maintained to all parameters, thus must remain
 * valid for the lifetime of the solver instance.
 *
 * \param solv allocated solver instance to initialize.
 * \param sys system to be integrated.
 * \param sys_data user data passed to sys.
 * \param scheme time-stepping scheme to use for solution.
 * \param scheme_data user data passed to scheme.
 * \param out output handler.
 * \param out_data.
 * \return 0 if init succeeded, 1 if error occurred.
 */
int sk_solv_init(
	sk_solv * restrict solv,
	sk_sys sys, void * restrict sys_data,
	sk_sch scheme, void * restrict scheme_data,
	sk_out out, void * restrict out_data,
	sk_hist_filler hf, void * restrict hfill_data,
	int seed,
	int nx, double * restrict x0,
	int nc, int * restrict vi, double * restrict vd,
	double t0, double dt
	);

/**
 * Frees memory occupied by solver instance.
 *
 * \param s allocated solver instance.
 */
void sk_solv_free(sk_solv *s);

/**
 * Continue stepping in time until one or more outputs returns 0 to stop.
 *
 * \note An error during execution of output callback is not currently distinct
 * from an indication by the output callback to stop the solution.
 *
 * \param s initialized solver instance.
 * \return 0 if continuation succeeds, 1 if error occurs.
 */
int sk_solv_cont(sk_solv *s);

/**
 * Get number of coupling variables.
 *
 * \param s solver instance.
 */
int sk_solv_get_nc(sk_solv *s);

/**
 * Get history instance or NULL if no delayed terms in solution.
 *
 * \param s solver instance.
 */
sk_hist *sk_solv_get_hist(sk_solv *s);

/**
 * Get rng instance.
 *
 * \param s solver instance.
 */
rk_state *sk_solv_get_rng(sk_solv *s);

/**
 * Get current time in solution.
 *
 * \param s solver instance.
 */
double sk_solv_get_t(sk_solv *s);

/**
 * Get current state vector in solution.
 *
 * \param s solver instance.
 */
double *sk_solv_get_x(sk_solv *s);

/**
 * Get current coupling vector in solution.
 *
 * \param s solver instance.
 */
double *sk_solv_get_c(sk_solv *s);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
