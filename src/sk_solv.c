/* Apache 2.0 INS-AMU 2015 */

#include <string.h>
#include <stdlib.h>

#include "sk_solv.h"
#include "sk_malloc.h"


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
	return sk_malloc (sizeof(sk_solv));
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
	s->nx = nx;
	s->nc = nc;
	s->cont = 1;
	s->sys = sys;
	s->sysd = sys_data;
	s->sch = scheme;
	s->schd = scheme_data;
	s->out = out;
	s->outd = out_data;
	s->hf = hf;
	s->hfd = hfill_data;
	s->x = sk_malloc (sizeof(double) * nx);
	s->x0 = sk_malloc (sizeof(double) * nx);
	if (nc > 0 && vi!=NULL && vd!=NULL) {
		int cn;
		/* TODO allow hist dt to vary */
		s->hist = sk_hist_alloc();
		sk_hist_init(s->hist, nc, vi, vd, t0, dt);
		sk_hist_fill(s->hist, hf, hfill_data);
		cn = sk_hist_get_maxvi(s->hist);
		/* s->c big enough to accomate aff or eff */
		if (cn < s->nc)
			cn = s->nc;
		s->c = sk_malloc(sizeof(double) * cn);
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

	h = s->nc ? s->hist : NULL;
	s->cont = 1;

	do {
		s->sch(s->schd, h, &(s->rng), s->sys, s->sysd, s->t, s->dt,
		       s->nx, s->x, s->nc, s->c);
		s->t += s->dt;
		s->cont = s->out(s->outd, s->t, s->nx, s->x, s->nc, s->c);
	} while (s->cont);

	return 0;
}

int sk_solv_get_nc(sk_solv *s) {
	return s->nc;
}

sk_hist *sk_solv_get_hist(sk_solv *s) {
	return s->hist;
}

rk_state *sk_solv_get_rng(sk_solv *s) {
	return &s->rng;
}

double *sk_solv_get_c(sk_solv *s) {
	return s->c;
}

double *sk_solv_get_x(sk_solv *s) {
	return s->x;
}

double sk_solv_get_t(sk_solv *s) {
	return s->t;
}
