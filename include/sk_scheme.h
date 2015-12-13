/* Apache 2.0 INS-AMU 2015 */

/**
 * Defines time-stepping schemes for the solution to SDDE systems.
 *
 * \note each responsible for managing Jacobians if required!
 */

#ifndef SK_SCHEME_H
#define SK_SCHEME_H

#include "sk_hist.h"
#include "randomkit.h"
#include "sk_sys.h"
#include "sk_util.h"

/** SK_DEFSCH aids in creating a new scheme definition. 
 * See ::sk_sch for details of the generated callback signature.
 *
 * \param name name of scheme being defined.
 */

#define SK_DEFSCH(name) int name(\
	void * restrict data, \
	sk_hist * restrict hist, rk_state * restrict rng,\
	sk_sys sys, void * restrict sysd,\
	double t, double dt,\
	int nx, double * restrict x,\
	int nc, double * restrict c)

/**
 * Callback signature expected by solver framework for scheme definitions.
 * Use #SK_DEFSCH to declare or define a new scheme.
 *
 * \param data user data for scheme such as storage for intermediate steps
 * \param hist history instance
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

/**
 * Identity scheme
 *
 * The identity schemes updates the state following f & g directly, i.e.
 *
 * x_{t+1} = f(x_t) + g(x_t) * z
 *
 * This is useful for difference equations, for example.
 */
typedef struct {
	double *f, *g, *z;
} sk_sch_id_data;

int sk_sch_id_init(sk_sch_id_data *d, int nx);

void sk_sch_id_free(sk_sch_id_data *d);

SK_DEFSCH(sk_sch_id);

/**@{*/
/* Euler-Maruyama O(1) general purpose */
typedef struct {
	double *f, *g, *z;
} sk_sch_em_data;

int sk_sch_em_init(sk_sch_em_data *d, int nx);

void sk_sch_em_free(sk_sch_em_data *d);

SK_DEFSCH(sk_sch_em);
/**@}*/

/**@{*/
/* E-M for colored noise, derived from Fox 1998, 
 * (no proof of convergence for multiplicate noise!)
 */
typedef struct { 
	int first_call;
	double *f, *g, *z, *eps, lam; 
} sk_sch_emcolor_data;

int sk_sch_emcolor_init(sk_sch_emcolor_data *d, int nx, double lam);

void sk_sch_emcolor_free(sk_sch_emcolor_data *d);

SK_DEFSCH(sk_sch_emcolor);
/**@}*/

/**@{*/
/* c.f. Manella 2002, O(2) in drift term, additive noise only */
typedef struct {
	double *fl, *fr, *gl, *gr, *z, *xr;
} sk_sch_heun_data;

int sk_sch_heun_init(sk_sch_heun_data *d, int nx);

void sk_sch_heun_free(sk_sch_heun_data *d);

SK_DEFSCH(sk_sch_heun);
/**@}*/

/* TODO http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */
SK_DEFSCH(sk_sch_llmult);

#endif
