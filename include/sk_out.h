/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_OUT_H
#define SK_OUT_H

/** SK_DEFOUT aids in creating a new output definition.
 * See ::sk_out for details of the generated output callback signature.
 *
 * \param name name of output callback being defined.
 */
#define SK_DEFOUT(name) int name(void * restrict data,\
		double t,\
		int nx, double * restrict x,\
		int nc, double * restrict c)

/**
 * Callback signature expected by solver framework for output callbacks.
 * Use #SK_DEFOUT to declare or define a new output callback.
 *
 * \param data user data for output function such as simulation length.
 * \param t current time.
 * \param nx number of state variables.
 * \param x state variable vector.
 * \param nc number of coupling terms.
 * \param c coupling term vector.
 * \return 1 if the solver should continue, 0 to stop solver.
 */
typedef SK_DEFOUT((*sk_out));

#endif
