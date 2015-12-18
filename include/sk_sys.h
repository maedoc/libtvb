/* Apache 2.0 INS-AMU 2015 */

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
		double * restrict Jf, double * restrict Jg,\
		int nc, double * restrict c, double * restrict Jce)

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
 * \param data user data passed to system for defining e.g. parameters of the system.
 * \param hist history of system.
 * \param t current time in solution.
 * \param i index of system (relevant for composite systems).
 * \param nx number of state variables of system.
 * \param x vector of current state variable values.
 * \param f vector of drift terms per state variable.
 * \param f vector of diffusion terms per state variable.
 * \param Jf Jacobian of drift terms wrt x & aff c. If not required, NULL.
 * \param Jg Jacobian of diffusion terms wrt x & aff c. If not required, NULL.
 * \param nc number of coupling terms.
 * \param c vector of coupling terms.
 * \param Jce Jacbobian of efferent coupling terms. If not required, NULL.
 * \return 0 to indicate success.
 */
typedef SK_DEFSYS((*sk_sys));

typedef struct {
    double a, tau, D, k;
} sk_sys_exc_dat;

SK_DEFSYS(sk_sys_exc);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
