/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_SYS_H
#define SK_SYS_H

typedef int (*sk_sys)(
	int nx, double *x, double *f, double *g, double *Jf, double *Jg,
	int nc, double *c, void *data);

#endif
