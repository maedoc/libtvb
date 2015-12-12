/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_SOLV_H
#define SK_SOLV_H

#include "randomkit.h"
#include "sk_hist.h"

#define SK_DEFSYS(name) int name(void *data,\
		double t,\
		int nx, double *x, double *f, double *g,\
		double *Jf, double *Jg,\
		int nc, double *c)

typedef SK_DEFSYS((*sk_sys));

#define SK_DEFSCH(name) int name(\
	void *data,\
	sk_sys sys, void *sysd,\
	double t, double dt,\
	int nx, double *x,\
	int nc, double *c)

typedef SK_DEFSCH((*sk_sch));

#define SK_DEFOUT(name) int name(void *data,\
		double t,\
		int nx, double *x)

typedef SK_DEFOUT((*sk_out));

struct sk_solv
{
	int nx, nc, cont;
        sk_sys sys;
	sk_sch sch;
	sk_out out;
	void *sysd, *schd, *outd;
	sk_hist_filler hf;
	struct sk_hist *hist; /* nd==nc, ci, cd */
	rk_state rng;
	double t, dt, *x, *c;
};

/* usr handles data alloc, init, free, etc */
struct sk_solv *sk_solv_init(
	sk_sys sys, void *sys_data,
	sk_sch scheme, void *scheme_data,
	sk_out out, void *out_data,
	sk_hist_filler hf,
	int seed,
	int nx, double *x0,
	int nc, int *vi, double *vd,
	double t0, double dt
	);

void sk_solv_free(struct sk_solv *s);

int sk_solv_cont(struct sk_solv *s);

#endif
