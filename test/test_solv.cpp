/* Apache 2.0 INS-AMU 2015 */

#include "gtest/gtest.h"

#include "sddekit.h"

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

TEST(solv, simple) {
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

	EXPECT_EQ(rk_gauss(&solv.rng),rand0);

	outd.tf = T0 + DT;

	sk_solv_cont(&solv);

	EXPECT_EQ(1,schd.n_calls);
	EXPECT_EQ(DT,schd.dt);
	EXPECT_EQ(&solv.rng,schd.rng);

	EXPECT_EQ(1,sysd.n_calls);
	EXPECT_EQ(NX,sysd.nx);
	EXPECT_EQ(NC,sysd.nc);
	EXPECT_EQ(T0,sysd.t);
	EXPECT_EQ(T0+DT,solv.t);
	EXPECT_EQ(solv.x,sysd.x);
	EXPECT_EQ(solv.c,sysd.c);
	EXPECT_EQ(NULL,sysd.f);
	EXPECT_EQ(NULL,sysd.g);
	EXPECT_EQ(NULL,sysd.Jf);
	EXPECT_EQ(NULL,sysd.Jg);

	outd.tf = T0 + 17 * DT;
	sk_solv_cont(&solv);
	EXPECT_EQ(17,sysd.n_calls);
	ASSERT_NEAR(sysd.t+DT, outd.tf, 1e-14);

	sk_solv_free(&solv);
}
