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

#ifdef __cplusplus
extern "C" {
#endif

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
 * \param data user data for scheme such as storage for intermediate steps.
 * \param hist history instance.
 * \param rng random number generator state.
 * \param sys system being solved.
 * \param sysd user data for system.
 * \param t current time.
 * \param dt current time step to use.
 * \param nx number of state variables.
 * \param x state variable vector.
 * \param nc number of coupling variables.
 * \param c coupling variable vector.
 * \return 0 when step succeeds, 1 if error occurs.
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
SK_DEFSCH(sk_sch_id);

typedef struct sk_sch_id_data sk_sch_id_data;

/**
 * Allocate memory for identity integration scheme, or return NULL if no memory 
 * available.
 */
sk_sch_id_data *sk_sch_id_alloc();

/**
 * Initialize an identity integration scheme.
 *
 * \param d allocated scheme instance.
 * \param nx number of state variables.
 * \return 0 if init succeeds, 1 if error occurs.
 */
int sk_sch_id_init(sk_sch_id_data *d, int nx);

/**
 * Free memory for identity scheme.
 *
 * \param d identity scheme instance.
 */
void sk_sch_id_free(sk_sch_id_data *d);

/* Euler-Maruyama O(1) general purpose */
SK_DEFSCH(sk_sch_em);

typedef struct sk_sch_em_data sk_sch_em_data;

/**
 * Allocate memory for Euler-Maruyama integration scheme, or return NULL if no memory 
 * available.
 */
sk_sch_em_data *sk_sch_em_alloc();

/**
 * Initialize an Euler-Maruyama integration scheme.
 *
 * \param d scheme instance.
 * \param nx number of state variables.
 * \return 0 if init succeeds, 1 if error occurs.
 */
int sk_sch_em_init(sk_sch_em_data *d, int nx);

/**
 * Free memory for Euler-Maruyama scheme.
 *
 * \param d Euler-Maruyama scheme instance.
 */
void sk_sch_em_free(sk_sch_em_data *d);

/* E-M for colored noise, derived from Fox 1998, 
 * for additive noise.
 */
SK_DEFSCH(sk_sch_emcolor);

typedef struct sk_sch_emcolor_data sk_sch_emcolor_data; 

/**
 * Allocate memory for colored noise Euler-Maruyama integration scheme.
 */
sk_sch_emcolor_data *sk_sch_emcolor_alloc();

/**
 * Initialize a colored noise Euler-Maruyama scheme instance.
 *
 * \param d scheme instance.
 * \param nx number of state variables.
 * \param lam damping factor determining color; cf Fox et al 98.
 * \return 0 if init succeeds; 1 if error occurs.
 */
int sk_sch_emcolor_init(sk_sch_emcolor_data *d, int nx, double lam);

/**
 * Free memory for colored noise Euler-Maruyama scheme.
 *
 * \param d scheme instance.
 */
void sk_sch_emcolor_free(sk_sch_emcolor_data *d);

/* c.f. Manella 2002, O(2) in drift term, additive noise only */
SK_DEFSCH(sk_sch_heun);

typedef struct sk_sch_heun_data sk_sch_heun_data;

/**
 * Allocate memory for Heun integration scheme.
 */
sk_sch_heun_data *sk_sch_heun_alloc();

/**
 * Initialize Heun scheme.
 *
 * \param d allocated Heun scheme instance.
 * \param nx number of state variables.
 * \return 0 if init succeeds, 0 if error occurs.
 */
int sk_sch_heun_init(sk_sch_heun_data *d, int nx);

/**
 * Free memory for Heun scheme.
 *
 * \param d Heun scheme instance.
 */
void sk_sch_heun_free(sk_sch_heun_data *d);

/* TODO http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */
SK_DEFSCH(sk_sch_llmult);

/* TODO Küchler & Platen semi-implicit Milstein for SDDEs */
SK_DEFSCH(sk_sch_kpsimp);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
