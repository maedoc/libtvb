/* Apache 2.0 INS-AMU 2015 */

#include <math.h>

#include "sk_sys.h"


typedef struct {
	double k_e, k_i, r_e, r_i, tau_e, tau_i, c_1, c_2, c_3,
	       c_4, a_e, a_i, b_e, b_i, theta_e, theta_i, alpha_e,
	       alpha_i, P, Q, c_e, c_i, c_ee, c_ie, c_ei, c_ii;
	double D, k;
} sk_sys_wc_data;

sk_sys_wc_data sk_sys_wc_sl14 = {
	/* Sanz-Leon 2014 */
	.k_e = 1.0, .k_i = 1.0,
	.r_e = 0.0, .r_i = 0.0,
	.tau_e = 10.0, .tau_i = 10.0,
	.c_1 = 10.0,
	.c_2 = 6.0,
	.c_3 = 1.0,
	.c_4 = 1.0,
	.a_e = 1.0, .a_i = 1.0,
	.b_e = 0.0, .b_i = 0.0,
	.theta_e = 2.0, .theta_i = 3.5,
	.alpha_e = 1.2, .alpha_i = 2.0,
	.P = 0.5, .Q = 0.0,
	.c_e = 1.0, .c_i = 1.0,
	/* defaults */
	.c_ee = 12.0, .c_ie = 4.0, .c_ei = 13.0, .c_ii = 11.0
};
	
/**
 * Wilson-Cowan population model without symmetry breaking and with
 * additive noise.
 */
SK_DEFSYS(sk_sys_wc) {
	sk_sys_wc_data *d = data;
	(void) hist; (void) t; (void) nx; (void) nc; (void) i;
	(void) Jf; (void) Jg; (void) Jce;
	f[0] = d->alpha_e * (d->c_ee * x[0] - d->c_ei * x[1] + d->P
		- d->theta_e + d->k*(c[0] + c[1]));
	f[1] = d->alpha_i * (d->c_ie * x[0] - d->c_ii * x[1] + d->Q
		- d->theta_i + d->k*(c[0] + c[1]));
	f[0] = d->c_e / (1.0 + exp(-d->a_e * (f[0] - d->b_e)));
	f[1] = d->c_i / (1.0 + exp(-d->a_i * (f[1] - d->b_i)));
	f[0] = (-x[0] + (d->k_e - d->r_e * x[0]) * f[0]) / d->tau_e;
	f[1] = (-x[1] + (d->k_i - d->r_i * x[1]) * f[1]) / d->tau_i;
	g[0] = d->D;
	g[1] = d->D;
	c[0] = x[0];
	c[1] = x[1];
	return 0;
}
