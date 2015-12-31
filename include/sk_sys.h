/* copyright 2016 Apache 2 sddekit authors */

#ifndef SK_SYS_H
#define SK_SYS_H


#include "sk_hist.h"
#include "sk_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * SK_DEFSYS aids in creating a new system defintion.
 * See ::sk_sys for explanation of callback signature.
 *
 * \param name name of expanded system definition.
 */
#define SK_DEFSYS(name) int name(\
		void * restrict data,\
		sk_hist * restrict hist,\
		double t, int i,\
		int nx, double * restrict x, \
		double * restrict f, double * restrict g,\
		double * restrict F, double * restrict G,\
		int nc, double * restrict c, \
		double * restrict Cf, double * restrict Cg)

/**
 * Callback signature expected by solver framework for system definitions.
 * Use #SK_DEFSYS to declare or define a new system.
 *
 * The coupling term array has two uses. On entry to system callback,
 * the array contains elements for every delayed term defined using the
 * nc/vi/vd arguments to sk_solv_init, which are used to define the delayed
 * coupling structure of the system. On exit, the array should contain
 * values to be used/stored for delayed coupling. The array vi determines
 * the mapping from efferent coupling terms to afferent terms.
 *
 * \note The partial derivative terms F, G, Cf, Cg should only be set if
 * the scheme requires them; they will be NULL otherwise. F & G have a dense
 * nx x nx row-major matrix layout whereas Cf & Cg have the same sparse layout
 * as provided to the solver.
 *
 * \param data user data passed to system for defining e.g. parameters of the system.
 * \param hist history of system.
 * \param t current time in solution.
 * \param i index of system (relevant for composite systems).
 * \param nx number of state variables of system.
 * \param x vector of current state variable values.
 * \param f vector of drift terms per state variable.
 * \param f vector of diffusion terms per state variable.
 * \param F partial derivatives of drift terms with respect to x.
 * \param G partial derivatives of diffusion terms with respect to x.
 * \param nc number of coupling terms.
 * \param c vector of coupling terms.
 * \param Cf partial derivatives of drift terms with respect to c.
 * \param Cg partial derivatives of diffusion terms with respect to c.
 * \return 0 if system evaluation succeeded, 1 if error occurred.
 */
typedef SK_DEFSYS((*sk_sys));

typedef struct sk_sys_exc_dat sk_sys_exc_dat;

/**
 * Allocate memory for Excitator system
 */
sk_sys_exc_dat *sk_sys_exc_alloc();

/**
 * Free memory for Excitator instance.
 */
void sk_sys_exc_free(sk_sys_exc_dat *d);


/**
 * Get the a parameter value.
 *
 * \param d Excitator system instance.
 */
double sk_sys_exc_get_a(sk_sys_exc_dat *d);

/**
 * Set the a parameter value.
 *
 * \param d Excitator system instance.
 * \param new_a new value of a.
 */
void sk_sys_exc_set_a(sk_sys_exc_dat *d, double new_a);

/**
 * Get the tau parameter value.
 *
 * \param d Excitator system instance.
 */
double sk_sys_exc_get_tau(sk_sys_exc_dat *d);

/**
 * Set the tau parameter value.
 *
 * \param d Excitator system instance.
 * \param new_tau new value of tau.
 */
void sk_sys_exc_set_tau(sk_sys_exc_dat *d, double new_tau);

/**
 * Get the D parameter value.
 *
 * \param d Excitator system instance.
 */
double sk_sys_exc_get_D(sk_sys_exc_dat *d);

/**
 * Set the D parameter value.
 *
 * \param d Excitator system instance.
 * \param new_D new value of D.
 */
void sk_sys_exc_set_D(sk_sys_exc_dat *d, double new_D);

/**
 * Get the k parameter value.
 *
 * \param d Excitator system instance.
 */
double sk_sys_exc_get_k(sk_sys_exc_dat *d);

/**
 * Set the k parameter value.
 *
 * \param d Excitator system instance.
 * \param new_k new value of k.
 */
void sk_sys_exc_set_k(sk_sys_exc_dat *d, double new_k);

SK_DEFSYS(sk_sys_exc);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
