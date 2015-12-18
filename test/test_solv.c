/* Apache 2.0 INS-AMU 2015 */

#include "sk_test.h"
#include "sk_solv.h"
#include "randomkit.h"

typedef struct {
	int n_calls, nx, nc;
	double t, *x, *c, *f, *g, *Jf, *Jg;
} sys_data;

static SK_DEFSYS(test_sys)
{
	sys_data *d = data;
	/* unused */ (void) Jce; (void) hist; (void) i;
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

typedef struct {
	int n_calls;
	double dt;
	rk_state *rng;
} sch_data;

static SK_DEFSCH(test_sch)
{
	sch_data *d = data;
	d->n_calls++;
	d->dt = dt;
	d->rng = rng;
	(*sys)(sysd, hist, t, 0, nx, x, NULL, NULL, NULL, NULL, nc, c, NULL);
	return 0;
}

typedef struct {
	int nx;
	double tf, *x;
} out_data;

static SK_DEFOUT(test_out)
{
	out_data *d = data;
	/* unused */ (void) nc; (void) c;
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
	sys_data sysd;
	sch_data schd;
	out_data outd;
	sk_solv solv;
	rk_state rng;

	rk_seed(SEED, &rng);
	rand0 = rk_gauss(&rng);

	sysd.n_calls = 0;
	schd.n_calls = 0;
	vi[0] = 0;
	vi[1] = 1;
	vd[0] = 2.1;
	vd[1] = 0.42;

	sk_solv_init(&solv, &test_sys, &sysd,
		&test_sch, &schd, &test_out, &outd,
		&test_hist_filler, NULL, SEED, NX, x, NC, vi, vd,
		T0, DT);

	sk_test_true(rand0==rk_gauss(&solv.rng));

	outd.tf = T0 + DT;

	sk_solv_cont(&solv);

	sk_test_true(schd.n_calls==1);
	sk_test_true(schd.dt==DT);
	sk_test_true(schd.rng==&solv.rng);

	sk_test_true(sysd.n_calls==1);
	sk_test_true(sysd.nx==NX);
	sk_test_true(sysd.nc==NC);
	sk_test_true(sysd.t==T0);
	sk_test_true(solv.t==T0+DT);
	sk_test_true(sysd.x==solv.x);
	sk_test_true(sysd.c==solv.c);
	sk_test_true(sysd.f==NULL);
	sk_test_true(sysd.g==NULL);
	sk_test_true(sysd.Jf==NULL);
	sk_test_true(sysd.Jg==NULL);

	outd.tf = T0 + 17 * DT;
	sk_solv_cont(&solv);
	sk_test_true(sysd.n_calls==17);
	sk_test_tol(sysd.t+DT, outd.tf, 1e-15);

	sk_solv_free(&solv);
	return 0;
}

int main() {
	test_solv();
	return sk_test_report();
}
