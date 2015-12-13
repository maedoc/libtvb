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

/* TODO typedef */
typedef struct
{
	int nx, nc, cont;
        sk_sys sys;
	sk_sch sch;
	sk_out out;
	void *sysd, *schd, *outd, *hfd;
	sk_hist_filler hf;
	sk_hist hist; /* nd==nc, ci, cd */
	rk_state rng; /* TODO mv to scheme? */
	double t, dt, *x, *c, *x0;
} sk_solv;

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
 * Frees the internal data structures in *s, but user is 
 * responsible for free the memory at s.
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

#endif
