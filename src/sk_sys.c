/* Apache 2.0 INS-AMU 2015 */

#include "sk_solv.h"
#include "sk_sys.h"
#include "sk_malloc.h"

struct sk_sys_exc_dat {
    double a, tau, D, k;
};

sk_sys_exc_dat *sk_sys_exc_alloc() {
	return sk_malloc (sizeof(sk_sys_exc_dat));
}

void sk_sys_exc_free(sk_sys_exc_dat *d) {
	sk_free(d);
}

double sk_sys_exc_get_a(sk_sys_exc_dat *d) {
	return d->a;
}

void sk_sys_exc_set_a(sk_sys_exc_dat *d, double new_a) {
	d->a = new_a;
}

double sk_sys_exc_get_tau(sk_sys_exc_dat *d) {
	return d->tau;
}

void sk_sys_exc_set_tau(sk_sys_exc_dat *d, double new_tau) {
	d->tau = new_tau;
}

double sk_sys_exc_get_D(sk_sys_exc_dat *d) {
	return d->D;
}

void sk_sys_exc_set_D(sk_sys_exc_dat *d, double new_D) {
	d->D = new_D;
}

double sk_sys_exc_get_k(sk_sys_exc_dat *d) {
	return d->k;
}

void sk_sys_exc_set_k(sk_sys_exc_dat *d, double new_k) {
	d->k = new_k;
}

SK_DEFSYS(sk_sys_exc)
{
	sk_sys_exc_dat *d = data;
	/* avoid unused parameter warnings from compiler */
	(void) t; (void) nx; (void) nc; (void) hist;
	(void) F; (void) G; (void) Cf; (void) Cg;
	(void) i;
	/* evaluate system */
	f[0] = (x[0] - x[0]*x[0]*x[0]/3.0 + x[1]) * d->tau;
	f[1] = (d->a - x[0] + d->k*c[0]) / d->tau;
	g[0] = d->D;
	g[1] = d->D;
	c[0] = x[0];
	return 0;
}
