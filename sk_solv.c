/* Apache 2.0 INS-AMU 2015 */

#include <string.h>
#include <stdlib.h>

#include "sk_solv.h"
#include "sk_util.h"


struct sk_solv *sk_solv_init(
	sk_sys sys, void *sys_data,
	sk_sch scheme, void *scheme_data,
	sk_out out, void *out_data,
	sk_hist_filler hf,
	int seed,
	int nx, double *x0,
	int nc, int *vi, double *vd,
	double t0, double dt
	)
{
	struct sk_solv *s = malloc (sizeof(struct sk_solv));
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
	s->hist = malloc (sizeof(struct sk_hist));
	sk_hist_init(s->hist, nc, vi, vd, t0, dt);
	sk_hist_fill(s->hist, hf);
	rk_seed(seed, &(s->rng));
	SK_MALLOCHECK(s->x = malloc (sizeof(double) * nx));
	SK_MALLOCHECK(s->c = malloc(sizeof(double) * s->nc));
	memcpy(s->x, x0, sizeof(double) * s->nx);
	s->t = t0;
	s->dt = dt;
	return s;
}

void sk_solv_free(struct sk_solv *s)
{
	free(s->x);
	free(s->c);
	sk_hist_free(s->hist);
	free(s->hist);
	free(s);
}

int sk_solv_cont(struct sk_solv *s)
{
	s->cont = 1;
	do
	{
		s->t += s->dt;
		sk_hist_get(s->hist, s->t, s->c);
		s->sch(s->schd, s->sys, s->sysd, s->t, s->dt,
		       s->nx, s->x, s->nc, s->c);
		sk_hist_set(s->hist, s->t, s->x);
		s->cont = s->out(s->outd, s->t, s->nx, s->x);
	}
	while (s->cont);
	return 0;
}
