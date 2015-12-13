/* Apache 2.0 INS-AMU 2015 */

#include "sk_solv.h"
#include "sk_sys.h"

SK_DEFSYS(sk_sys_exc)
{
	sk_sys_exc_dat *d = data;
	/* avoid unused parameter warnings from compiler */
	(void) t; (void) nx; (void) Jf; (void) Jg; (void) nc; (void) Jce; (void) hist;
	/* evaluate system */
	f[0] = (x[0] - x[0]*x[0]*x[0]/3.0 + x[1]) * d->tau;
	f[1] = (d->a - x[0] + d->k*c[0]) / d->tau;
	g[0] = d->D;
	g[1] = d->D;
	c[0] = x[0];
	return 0;
}
