/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <string.h>

#include "sddekit.h"

static void hist_t_fill(void *data, int n, double *t, int *indices, double *buf) {
	/* suppress unused arguments */
	(void) data; (void) indices;
	/* fill buffer from times */
	memcpy(buf, t, n*sizeof(double));
}

#define ND 3

TEST(hist, basic) {
	int i, vi[ND];
	double dt, vd[ND], x[3];
	sk_hist *h;

	/* set up */
	dt = 0.1;
	vi[0] = 1;
	vi[1] = 1;
	vi[2] = 0;
	vd[0] = 5.5 * dt;
	vd[1] = 4.5 * dt;
	vd[2] = 33.3 * dt;
	h = (sk_hist*) sk_malloc (sizeof(sk_hist));

	sk_hist_init(h, ND, vi, vd, 0.0, dt);
	EXPECT_EQ(ND,h->nd);
	EXPECT_EQ(0.0,h->t);
	EXPECT_EQ(dt,h->dt);
	EXPECT_EQ(2,h->nu);
	EXPECT_EQ(0,h->lim[0]);
	EXPECT_EQ(36,h->lim[1]);
	EXPECT_EQ(8 + 36,h->lim[2]);
	EXPECT_EQ(36,h->len[0]);
	EXPECT_EQ(8,h->len[1]);
	EXPECT_EQ(0,h->pos[0]);
	EXPECT_EQ(0,h->pos[1]);
	EXPECT_EQ(0,h->uvi[0]);
	EXPECT_EQ(1,h->uvi[1]);
	EXPECT_EQ(1,h->maxvi);
	EXPECT_EQ(0,h->vi2i[0]);
	EXPECT_EQ(1,h->vi2i[1]);
	EXPECT_EQ(vd[0],h->maxd[1]);
	EXPECT_EQ(vd[2],h->maxd[0]);
	EXPECT_EQ(1,h->vi[0]);
	EXPECT_EQ(1,h->vi[1]);
	EXPECT_EQ(0,h->vi[2]);
	EXPECT_EQ(vd[0],h->del[0]);
	EXPECT_EQ(vd[1],h->del[1]);
	EXPECT_EQ(vd[2],h->del[2]);
	EXPECT_TRUE(NULL!=h->buf);

	sk_hist_fill(h, &hist_t_fill, NULL);
	for (i=0; i<35; i++)
		EXPECT_EQ(-i*dt,h->buf[i]);
	EXPECT_EQ(dt,h->buf[35]);
	for (i=0; i<7; i++)
		EXPECT_EQ(-i*dt,h->buf[36+i]);
	EXPECT_EQ(dt,h->buf[36+7]);

	sk_hist_get(h, dt/3, x);
	ASSERT_NEAR(x[0], -vd[0]+dt/3, 1e-15);
	ASSERT_NEAR(x[1], -vd[1]+dt/3, 1e-15);
	ASSERT_NEAR(x[2], -vd[2]+dt/3, 1e-15);

	x[0] = 1.5;
	x[1] = 1.0;
	sk_hist_set(h, dt/2.0, x);
	ASSERT_NEAR(h->buf[35], 3.0, 1e-15);
	ASSERT_NEAR(h->buf[36 + 7], 2.0, 1e-15);

	sk_hist_free(h);
	sk_free(h);
}

/* port of TVB's history test */
static void hist_fill_ones(void *data, int n, double *t, int *indices, double *buf) {
	int i;
	/* suppress unused arguments */
	(void) data; (void) indices; (void) t;
	/* fill buffer from times */
	for (i=0; i<n; i++)
		buf[i] = 1.0;
}

static SK_DEFSYS(hist_exact_sys) {
	(void) data; (void) nx; (void) nc; (void) t; (void) Jf; (void) Jg; 
	(void) Jce; (void) hist; (void) i;
	f[0] = x[0] + c[0];
	g[0] = 0.0;
	c[0] = x[0];
	return 0;
}

/* The values are obtained by stepping through time according to the
 * connecting
 *
 * w = [ 0 1 0 0      d = [ .  1  .  . 
 *       0 0 1 0 	    .  .  6  .
 *       0 0 0 1            .  .  . 11
 *       0 0 0 0 ]	    .  .  .  . ] 
 *
 *
 *    ...
 *    1  1  1  1
 * [  1  1  1  1    t = 0
 *    2  2  2  1 	1
 *    3  3  3  1	2
 *    5  4  4  1        3
 *    8  5  5  1        4
 *   12  6  6  1        5
 *   17  7  7  1        6
 *   23  8  8  1        7
 *   30 10  9  1        8
 *   38 13 10  1        9
 *   ....
 *
 */

static double xexpect[12][4] = {
	{1, 1, 1, 1},
	{2, 2, 2, 1},
	{3, 3, 3, 1},
	{5, 4, 4, 1},
	{8, 5, 5, 1},
	{12, 6, 6, 1},
	{17, 7, 7, 1},
	{23, 8, 8, 1},
	{30, 10, 9, 1},
	{38, 13, 10, 1},
	{48, 17, 11, 1},
	{61, 22, 12, 1}
};

static SK_DEFOUT(hist_exact_out) {
	int i;
	/* unused */ (void) nc; (void) c; (void) data;
	EXPECT_EQ(4,nx);
	for (i=0; i<4; i++)
		EXPECT_EQ(x[i], xexpect[(int) t][i]);
	return t < 11;
}

TEST(hist, exact) {
	int i, n=4, nnz, *Or, *Ic;
	double w[16], d[16], *nzw, *nzd, x0[4];
	sk_net_data net;
	sk_solv sol;
	sk_sch_id_data schd;

	x0[0] = 1;
	x0[1] = 1;
	x0[2] = 1;
	x0[3] = 1;
	for (i=0; i<16; i++) {
		w[i] = 0.0;
		d[i] = (double) i;
	}
	for (i=0; i<n-1; i++)
		w[i*n+i+1] = 1;

	/* 3 nnz, so hist expects c size 3, but net setups for c size 4 */

	/* setup network */
	sk_sparse_from_dense(n, n, w, d, 0.0, &nnz, &Or, &Ic, &nzw, &nzd);
	EXPECT_EQ(0,Or[0]);
	EXPECT_EQ(1,Or[1]);
	EXPECT_EQ(2,Or[2]);
	EXPECT_EQ(3,Or[3]);
	EXPECT_EQ(1,Ic[0]);
	EXPECT_EQ(2,Ic[1]);
	EXPECT_EQ(3,Ic[2]);
	EXPECT_EQ(1,nzw[0]);
	EXPECT_EQ(1,nzw[1]);
	EXPECT_EQ(1,nzw[2]);
	EXPECT_EQ(1,nzd[0]);
	EXPECT_EQ(6,nzd[1]);
	EXPECT_EQ(11,nzd[2]);

	sk_net_init1(&net, n, hist_exact_sys, NULL, 1, 1, nnz, Or, Ic, nzw, nzd);

	EXPECT_EQ(3,nnz);
	EXPECT_EQ(4,net.ne);

	/* setup scheme & driver */
	sk_sch_id_init(&schd, n);
	sk_solv_init(&sol, sk_net_sys, &net, sk_sch_id, &schd,
			hist_exact_out, NULL, hist_fill_ones, NULL, 42,
			n, x0, nnz, Ic, nzd, 0.0, 1.0);

	EXPECT_EQ(3,sol.nc);
	EXPECT_EQ(3,sol.hist.nu);

	/* run */
	sk_solv_cont(&sol);

	/* tests performed in out function.. */

	/* clean up */
	sk_solv_free(&sol);
	sk_sch_id_free(&schd);
	sk_net_free(&net);
	sk_free(Or);
	sk_free(Ic);
	sk_free(nzw);
	sk_free(nzd);
}
