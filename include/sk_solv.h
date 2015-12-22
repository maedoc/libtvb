/* Apache 2.0 INS-AMU 2015 */

/**
 * \file sk_solv.h
 *
 * \brief sk_solv.h defines sddekit's solver framework in terms of a system, 
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

typedef struct sk_solv sk_solv;

/**
 * Allocate memory for a solver instance.
 */
sk_solv *sk_solv_alloc();

/**
 * Initialize a solver.
 *
 * \note references are maintained to all parameters, thus must remain
 * valid for the lifetime of the solver instance.
 *
 * \param solv solver to initialize.
 * \param sys system to be integrated
 * \param sys_data user data passed to sys
 * \param scheme time-stepping scheme to use for solution
 * \param scheme_data user data passed to scheme
 * \param out output handler
 * \param out_data 
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
 * \param s solver
 */
void sk_solv_free(sk_solv *s);

/**
 * Continue solution described in *s
 *
 * \param s solver.
 * \return 0 if successful else 1.
 */
int sk_solv_cont(sk_solv *s);

/**
 * Get number of coupling variables.
 *
 * \param s solver instance.
 */
int sk_solv_get_nc(sk_solv *s);

/**
 * Get history instance.
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
