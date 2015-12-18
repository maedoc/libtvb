/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <string.h>

#include "sk_test.h"
#include "sk_hist.h"
#include "sk_sys.h"
#include "sk_net.h"
#include "sk_sparse.h"
#include "sk_solv.h"
#include "sk_scheme.h"
#include "sk_out.h"

static void hist_t_fill(void *data, int n, double *t, int *indices, double *buf) {
	/* suppress unused arguments */
	(void) data; (void) indices;
	/* fill buffer from times */
	memcpy(buf, t, n*sizeof(double));
}

#define ND 3

int test_hist() {
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
	h = malloc (sizeof(sk_hist));

	sk_hist_init(h, ND, vi, vd, 0.0, dt);
	sk_test_true(h->nd==ND);
	sk_test_true(h->t==0.0);
	sk_test_true(h->dt==dt);
	sk_test_true(h->nu==2);
	sk_test_true(h->lim[0]==0);
	sk_test_true(h->lim[1]==36);
	sk_test_true(h->lim[2]==8 + 36);
	sk_test_true(h->len[0]==36);
	sk_test_true(h->len[1]==8);
	sk_test_true(h->pos[0]==0);
	sk_test_true(h->pos[1]==0);
	sk_test_true(h->uvi[0]==0);
	sk_test_true(h->uvi[1]==1);
	sk_test_true(h->maxvi==1);
	sk_test_true(h->vi2i[0]==0);
	sk_test_true(h->vi2i[1]==1);
	sk_test_true(h->maxd[1]==vd[0]);
	sk_test_true(h->maxd[0]==vd[2]);
	sk_test_true(h->vi[0]==1);
	sk_test_true(h->vi[1]==1);
	sk_test_true(h->vi[2]==0);
	sk_test_true(h->del[0]==vd[0]);
	sk_test_true(h->del[1]==vd[1]);
	sk_test_true(h->del[2]==vd[2]);
	sk_test_true(h->buf!=NULL);

	sk_hist_fill(h, &hist_t_fill, NULL);
	for (i=0; i<35; i++)
		sk_test_true(h->buf[i]==-i*dt);
	sk_test_true(h->buf[35]==dt);
	for (i=0; i<7; i++)
		sk_test_true(h->buf[36+i]==-i*dt);
	sk_test_true(h->buf[36+7]==dt);

	sk_hist_get(h, dt/3, x);
	sk_test_tol(x[0], -vd[0]+dt/3, 1e-15);
	sk_test_tol(x[1], -vd[1]+dt/3, 1e-15);
	sk_test_tol(x[2], -vd[2]+dt/3, 1e-15);

	x[0] = 1.5;
	x[1] = 1.0;
	sk_hist_set(h, dt/2.0, x);
	sk_test_tol(h->buf[35], 3.0, 1e-15);
	sk_test_tol(h->buf[36 + 7], 2.0, 1e-15);

	sk_hist_free(h);
	free(h);

	return 0;
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
	sk_test_true(nx==4);
	for (i=0; i<4; i++)
		sk_test_true(xexpect[(int) t][i]==x[i]);
	return t < 11;
}

int test_hist_exact() {
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
	sk_test_true(Or[0]==0);
	sk_test_true(Or[1]==1);
	sk_test_true(Or[2]==2);
	sk_test_true(Or[3]==3);
	sk_test_true(Ic[0]==1);
	sk_test_true(Ic[1]==2);
	sk_test_true(Ic[2]==3);
	sk_test_true(nzw[0]==1);
	sk_test_true(nzw[1]==1);
	sk_test_true(nzw[2]==1);
	sk_test_true(nzd[0]==1);
	sk_test_true(nzd[1]==6);
	sk_test_true(nzd[2]==11);

	sk_net_init1(&net, n, hist_exact_sys, NULL, 1, 1, nnz, Or, Ic, nzw, nzd);

	sk_test_true(nnz==3);
	sk_test_true(net.ne==4);

	/* setup scheme & driver */
	sk_sch_id_init(&schd, n);
	sk_solv_init(&sol, sk_net_sys, &net, sk_sch_id, &schd,
			hist_exact_out, NULL, hist_fill_ones, NULL, 42,
			n, x0, nnz, Ic, nzd, 0.0, 1.0);

	sk_test_true(sol.nc==3);
	sk_test_true(sol.hist.nu==3);

	/* run */
	sk_solv_cont(&sol);

	/* tests performed in out function.. */

	/* clean up */
	sk_solv_free(&sol);
	sk_sch_id_free(&schd);
	sk_net_free(&net);
	free(Or);
	free(Ic);
	free(nzw);
	free(nzd);

	return 0;
}

int main() {
	test_hist();
	test_hist_exact();
	return sk_test_report();
}
