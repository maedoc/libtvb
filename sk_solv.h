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

/**
 * SK_DEFSYS aids in creating a new system defintion.
 * See ::sk_sys for explanation of callback signature.
 *
 * \param name name of expanded system definition.
 */
#define SK_DEFSYS(name) int name(\
		void *data,\
		double t,\
		int nx, double *x, double *f, double *g,\
		double *Jf, double *Jg,\
		int nc, double *c)

/**
 * Callback signature expected by solver framework for system definitions.
 * Use #SK_DEFSYS to declare or define a new system.
 *
 * \param data user data passed to system for defining e.g. parameters of the system.
 * \param t current time in solution.
 * \param nx number of state variables of system.
 * \param x vector of current state variable values.
 * \param f vector of drift terms per state variable.
 * \param f vector of diffusion terms per state variable.
 * \param Jf Jacobian of drift terms.
 * \param Jg Jacobian of diffusion terms.
 * \param nc number of coupling terms.
 * \param c vector of afferent coupling terms as input, efferent coupling as output.
 * \return 0 to indicate success.
 */
typedef SK_DEFSYS((*sk_sys));

/** SK_DEFSCH aids in creating a new scheme definition. 
 * See ::sk_sch for details of the generated callback signature.
 *
 * \param name name of scheme being defined.
 */

#define SK_DEFSCH(name) int name(\
	void *data, rk_state *rng,\
	sk_sys sys, void *sysd,\
	double t, double dt,\
	int nx, double *x,\
	int nc, double *c)

/**
 * Callback signature expected by solver framework for scheme definitions.
 * Use #SK_DEFSCH to declare or define a new scheme.
 *
 * \param data user data for scheme such as storage for intermediate steps
 * \param rng random number generator state
 * \param sys system being solved
 * \param sysd user data for system
 * \param t current time
 * \param dt current time step to use
 * \param nx number of state variables
 * \param x state variable vector
 * \param nc number of coupling variables
 * \param c coupling variable vector
 * \return 0 in case of success
 */
typedef SK_DEFSCH((*sk_sch));

/** SK_DEFOUT aids in creating a new output definition.
 * See ::sk_out for details of the generated output callback signature.
 *
 * \param name name of output callback being defined.
 */
#define SK_DEFOUT(name) int name(void *data,\
		double t,\
		int nx, double *x)

/**
 * Callback signature expected by solver framework for output callbacks.
 * Use #SK_DEFOUT to declare or define a new output callback.
 *
 * \param data user data for output function such as simulation length.
 * \param t current time.
 * \param nx number of state variables.
 * \param x state variable vector.
 * \return 1 if the solver should continue, 0 to stop solver.
 */
typedef SK_DEFOUT((*sk_out));

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
	rk_state rng;
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
	sk_solv *solv,
	sk_sys sys, void *sys_data,
	sk_sch scheme, void *scheme_data,
	sk_out out, void *out_data,
	sk_hist_filler hf, void *hfill_data,
	int seed,
	int nx, double *x0,
	int nc, int *vi, double *vd,
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
