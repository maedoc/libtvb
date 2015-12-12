/* Apache 2.0 INS-AMU 2015 */

#include "sk_test.h"
#include "sk_solv.h"
#include "randomkit.h"

struct sys_data {
	int n_calls, nx, nc;
	double t, *x, *c, *f, *g, *Jf, *Jg;
};

static SK_DEFSYS(test_sys)
{
	struct sys_data *d = (struct sys_data*) data;
	d->n_calls++;
	d->t = t;
	d->nx = nx;
	d->x = x;
	d->nc = nc;
	d->c = c;
	d->f = f;
	d->g = g;
	d->Jf = Jf;
	d->Jg = Jg;
	return 0;
}

struct sch_data {
	int n_calls;
	double dt;
};

static SK_DEFSCH(test_sch)
{
	struct sch_data *d = (struct sch_data*) data;
	d->n_calls++;
	d->dt = dt;
	(*sys)(sysd, t, nx, x, NULL, NULL, NULL, NULL, nc, c);
	return 0;
}

struct out_data {
	int nx;
	double tf, *x;
};

static SK_DEFOUT(test_out)
{
	struct out_data *d = (struct out_data*) data;
	d->nx = nx;
	d->x = x;
	return t < d->tf;
}

static void test_hist_filler()
{
}

#define SEED 42
#define T0 2.34
#define DT 0.12
#define NX 3
#define NC 2

int test_solv()
{
	int vi[NC];
	double x[NX], vd[NX], rand0;
	struct sys_data sysd;
	struct sch_data schd;
	struct out_data outd;
	struct sk_solv *s;
	rk_state rng;

	rk_seed(SEED, &rng);
	rand0 = rk_gauss(&rng);


	sysd.n_calls = 0;
	schd.n_calls = 0;
	vi[0] = 0;
	vi[1] = 1;
	vd[0] = 2.1;
	vd[1] = 0.42;

	s = sk_solv_init(&test_sys, &sysd,
		&test_sch, &schd, &test_out, &outd,
		&test_hist_filler, SEED, NX, x, NC, vi, vd,
		T0, DT);

	sk_test_true(rand0==rk_gauss(&s->rng));

	outd.tf = T0 + DT;

	sk_solv_cont(s);

	sk_test_true(schd.n_calls==1);
	sk_test_true(schd.dt==DT);

	sk_test_true(sysd.n_calls==1);
	sk_test_true(sysd.nx==NX);
	sk_test_true(sysd.nc==NC);
	sk_test_true(sysd.t==T0+DT);
	sk_test_true(sysd.x==s->x);
	sk_test_true(sysd.c==s->c);
	sk_test_true(sysd.f==NULL);
	sk_test_true(sysd.g==NULL);
	sk_test_true(sysd.Jf==NULL);
	sk_test_true(sysd.Jg==NULL);

	outd.tf = T0 + 17 * DT;
	sk_solv_cont(s);
	sk_test_true(sysd.n_calls==17);
	sk_test_tol(sysd.t, outd.tf, 1e-15);

	sk_solv_free(s);
	return 0;
}
