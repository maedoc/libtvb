/* Apache 2.0 INS-AMU 2015 */

#include <string.h>
#include <stdlib.h>

#include "sk_solv.h"
#include "sk_util.h"


int sk_solv_init(
	sk_solv *s,
	sk_sys sys, void *sys_data,
	sk_sch scheme, void *scheme_data,
	sk_out out, void *out_data,
	sk_hist_filler hf, void *hfill_data,
	int seed,
	int nx, double *x0,
	int nc, int *vi, double *vd,
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
	SK_MALLOCHECK(s->x = malloc (sizeof(double) * nx));
	SK_MALLOCHECK(s->x0 = malloc (sizeof(double) * nx));
	if (nc > 0 && vi!=NULL && vd!=NULL) {
		sk_hist_init(&s->hist, nc, vi, vd, t0, dt);
		sk_hist_fill(&s->hist, hf, hfill_data);
		SK_MALLOCHECK(s->c = malloc(sizeof(double) * s->nc));
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
	free(s->x);
	free(s->x0);
	if (s->c != NULL) {
		free(s->c);
		sk_hist_free(&s->hist);
	}
}

int sk_solv_cont(sk_solv *s)
{
	s->cont = 1;
	if (s->nc)
		do {
			s->t += s->dt;
			sk_hist_get(&s->hist, s->t, s->c);
			s->sch(s->schd, &(s->rng), s->sys, s->sysd, s->t, s->dt,
			       s->nx, s->x, s->nc, s->c);
			sk_hist_set(&s->hist, s->t, s->x);
			s->cont = s->out(s->outd, s->t, s->nx, s->x);
		} while (s->cont);
	else
		do {
			s->t += s->dt;
			s->sch(s->schd, &(s->rng), s->sys, s->sysd, s->t, s->dt,
			       s->nx, s->x, s->nc, s->c);
			s->cont = s->out(s->outd, s->t, s->nx, s->x);
		} while (s->cont);

	return 0;
}
