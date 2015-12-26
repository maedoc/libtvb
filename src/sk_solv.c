/* Apache 2.0 INS-AMU 2015 */

#include <string.h>
#include <stdlib.h>

#include "sk_solv.h"
#include "sk_malloc.h"
#include "sk_err.h"
#include "sk_log.h"

struct sk_solv {
	int nx, nc, cont;
        sk_sys sys;
	sk_sch sch;
	sk_out out;
	void *sysd, *schd, *outd, *hfd;
	sk_hist_filler hf;
	sk_hist *hist; /* nd==nc, ci, cd */
	rk_state rng; /* TODO mv to scheme? */
	double t, dt, *x, *c, *x0;
};

sk_solv *sk_solv_alloc() {
	sk_solv *new, zero = {0};
	new = sk_malloc (sizeof(sk_solv));
	*new = zero;
	return new;
}

int sk_solv_init(
	sk_solv * restrict s,
	sk_sys sys, void * restrict sys_data,
	sk_sch scheme, void * restrict scheme_data,
	sk_out out, void * restrict out_data,
	sk_hist_filler hf, void * restrict hfill_data,
	int seed,
	int nx, double * restrict x0,
	int nc, int * restrict vi, double * restrict vd,
	double t0, double dt
	)
{
	char *errmsg;
#define FAILIF(cond, msg)\
       	if (cond) { \
		errmsg = msg;\
		goto uhoh;\
	}
	FAILIF(s==NULL, "cannot initialize NULL solver instance.")
	FAILIF(sys==NULL || scheme==NULL || hf==NULL,
	       "cannot initialize solver with NULL system, scheme or history function.")
	s->nx = nx;
	s->nc = nc;
	s->cont = 1;
	s->sys = sys;
#define WARNNULL(arg) if ((arg)==NULL)\
	sk_log_debug("solver init %s is NULL.", #arg)
	WARNNULL(s->sysd = sys_data);
	s->sch = scheme;
	WARNNULL(s->schd = scheme_data);
	WARNNULL(s->out = out);
	WARNNULL(s->outd = out_data);
	s->hf = hf;
	WARNNULL(s->hfd = hfill_data);
#undef WARNNULL
	FAILIF((s->x = sk_malloc (sizeof(double) * nx))==NULL, "failed to alloc solver x")
	FAILIF((s->x0 = sk_malloc (sizeof(double) * nx))==NULL, "failed to alloc solver x0")
	if (nc > 0 && vi!=NULL && vd!=NULL) {
		int cn;
		/* TODO allow hist dt to vary */
		FAILIF((s->hist = sk_hist_alloc())==NULL, "failed to allocate history.")
		FAILIF(sk_hist_init(s->hist, nc, vi, vd, t0, dt), "history init failed.")
		FAILIF(sk_hist_fill(s->hist, hf, hfill_data), "history fill failed.")
		cn = sk_hist_get_maxvi(s->hist);
		/* s->c big enough to accomate aff or eff */
		if (cn < s->nc)
			cn = s->nc;
		FAILIF((s->c = sk_malloc(sizeof(double) * cn))==NULL,
			"alloc coupling array failed.")
	} else {
		s->nc = 0;
		s->c = NULL;
	}
	rk_seed(seed, &(s->rng));
	memcpy(s->x, x0, sizeof(double) * s->nx);
	memcpy(s->x0, x0, sizeof(double) * s->nx);
	s->t = t0;
	s->dt = dt;
	return 0;
uhoh:
	if (s->x!=NULL) sk_free(s->x);
	if (s->x0!=NULL) sk_free(s->x0);
	if (s->c!=NULL) sk_free(s->c);
	if (s->hist!=NULL) sk_hist_free(s->hist);
	sk_err(errmsg);
	return 1;
}

void sk_solv_free(sk_solv *s)
{
	sk_free(s->x);
	sk_free(s->x0);
	if (s->c != NULL) {
		sk_free(s->c);
		sk_hist_free(s->hist);
	}
	sk_free(s);
}

int sk_solv_cont(sk_solv *s)
{
	sk_hist *h;

	if (s==NULL) {
		sk_err("NULL solver pointer.");
		return 1;
	}

	h = s->nc ? s->hist : NULL;
	s->cont = 1;
	do {
		if (s->sch(s->schd, h, &(s->rng), s->sys, s->sysd, s->t, s->dt,
		       s->nx, s->x, s->nc, s->c)) {
			sk_err("scheme failure.");
			return 1;
		}
		s->t += s->dt;
		s->cont = s->out(s->outd, s->t, s->nx, s->x, s->nc, s->c);
	} while (s->cont);

	return 0;
}

int sk_solv_get_nc(sk_solv *s) {
	if (s==NULL) {
		sk_err("NULL solver instance.");
		return 0;
	}
	return s->nc;
}

sk_hist *sk_solv_get_hist(sk_solv *s) {
	if (s==NULL) {
		sk_err("NULL solver instance.");
		return NULL;
	}
	return s->hist;
}

rk_state *sk_solv_get_rng(sk_solv *s) {
	if (s==NULL) {
		sk_err("NULL solver instance.");
		return NULL;
	}
	return &s->rng;
}

double *sk_solv_get_c(sk_solv *s) {
	if (s==NULL) {
		sk_err("NULL solver instance.");
		return NULL;
	}
	return s->c;
}

double *sk_solv_get_x(sk_solv *s) {
	if (s==NULL) {
		sk_err("NULL solver instance.");
		return NULL;
	}
	return s->x;
}

double sk_solv_get_t(sk_solv *s) {
	if (s==NULL) {
		sk_err("NULL solver instance.");
		return 0;
	}
	return s->t;
}
