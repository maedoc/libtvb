/* copyright 2016 Apache 2 sddekit authors */

#include <stdlib.h>
#include <string.h>

#include "sddekit.h"
#include "test.h"

static sd_stat hf_t_apply(sd_hfill *data, uint32_t n, 
				double * restrict t, uint32_t *indices, double * restrict buf) {
	(void) data; (void) indices;
	/* fill buffer from times */
	memcpy(buf, t, n*sizeof(double));
	return SD_OK;
}

sd_hfill *hf_t_new()
{
	sd_hfill *hf = sd_malloc(sizeof(sd_hfill));
	hf->free = (void(*)(sd_hfill*)) &sd_free;
	hf->apply = &hf_t_apply;
	hf->ptr = NULL;
	return hf;
}

#define ND 4

TEST(hist, basic) {
	uint32_t i, vi[ND];
	double dt, vd[ND], x[ND];
	sd_hist *h;

	/* set up */
	dt = 0.1;
	vi[0] = 1;
	vi[1] = 1;
	vi[2] = 0;
	vi[3] = 0;
	vd[0] = 5.5 * dt;
	vd[1] = 4.5 * dt;
	vd[2] = 33.3 * dt;
	vd[3] = 0.0;
	h = sd_hist_new_default(ND, vi, vd, 0.0, dt);

	EXPECT_EQ(ND, h->get_nd(h));
	EXPECT_EQ(0.0, h->get_t(h));
	EXPECT_EQ(dt, h->get_dt(h));
	EXPECT_EQ(2, h->get_nu(h));
	EXPECT_EQ(0,h->get_lim(h, 0));
	EXPECT_EQ(36,h->get_lim(h, 1));
	EXPECT_EQ(8 + 36,h->get_lim(h, 2));
	EXPECT_EQ(36, h->get_len(h, 0));
	EXPECT_EQ(8, h->get_len(h, 1));
	EXPECT_EQ(0, h->get_pos(h, 0));
	EXPECT_EQ(0, h->get_pos(h, 1));
	EXPECT_EQ(0, h->get_uvi(h, 0));
	EXPECT_EQ(1, h->get_uvi(h, 1));
	EXPECT_EQ(1, h->get_maxvi(h));
	EXPECT_EQ(0, h->get_vi2i(h, 0));
	EXPECT_EQ(1, h->get_vi2i(h, 1));
	EXPECT_EQ(vd[0], h->get_maxd(h, 1));
	EXPECT_EQ(vd[2], h->get_maxd(h, 0));
	EXPECT_EQ(1, h->get_vi(h, 0));
	EXPECT_EQ(1, h->get_vi(h, 1));
	EXPECT_EQ(0, h->get_vi(h, 2));
	EXPECT_EQ(0, h->get_vi(h, 3));
	EXPECT_EQ(vd[0], h->get_vd(h, 0));
	EXPECT_EQ(vd[1], h->get_vd(h, 1));
	EXPECT_EQ(vd[2], h->get_vd(h, 2));
	EXPECT_EQ(vd[3], h->get_vd(h, 3));
	EXPECT_TRUE(!h->buf_is_null(h));

	sd_hfill *hf = hf_t_new();
	h->fill(h, hf);
	hf->free(hf);
	for (i=0; i<35; i++)
		EXPECT_EQ(-(i*dt), h->get_buf_lin(h, i));
	EXPECT_EQ(dt, h->get_buf_lin(h, 35));
	for (i=0; i<7; i++)
		EXPECT_EQ(-(i*dt), h->get_buf_lin(h, 36+i));
	EXPECT_EQ(dt, h->get_buf_lin(h, 36+7));

	h->get(h, dt/3, x);
	ASSERT_NEAR(x[0], -vd[0]+dt/3, 1e-15);
	ASSERT_NEAR(x[1], -vd[1]+dt/3, 1e-15);
	ASSERT_NEAR(x[2], -vd[2]+dt/3, 1e-15);
	ASSERT_NEAR(x[3], -vd[3]+dt/3, 1e-15);

	x[0] = 1.5;
	x[1] = 1.0;
	h->set(h, dt/2.0, x);
	ASSERT_NEAR( h->get_buf_lin(h, 35), 3.0, 1e-15);
	ASSERT_NEAR( h->get_buf_lin(h, 36 + 7), 2.0, 1e-15);

	h->free(h);
}

static uint32_t het_ndim(sd_sys *sys) { (void) sys; return 1; }
static uint32_t het_ndc(sd_sys *sys) { (void) sys; return 1; }
static uint32_t het_nobs(sd_sys *sys) { (void) sys; return 1; }
static uint32_t het_nrpar(sd_sys *sys) { (void) sys; return 0; }
static uint32_t het_nipar(sd_sys *sys) { (void) sys; return 0; }
static sd_stat het_apply(sd_sys *sys, sd_sys_in *in, sd_sys_out *out)
{
	(void) sys;
	out->f[0] = in->x[0] + in->i[0];
	out->g[0] = 0.0;
	out->o[0] = in->x[0];
	return 0;
}
static void het_free(sd_sys *sys) { sd_free(sys); }

static sd_sys *het_new()
{
	sd_sys val = { .ndim=&het_ndim, .ndc=&het_ndc, .nobs=&het_nobs,
			 .nrpar=&het_nrpar, .nipar=&het_nipar, .apply=&het_apply,
			 .free=&het_free, .ptr=NULL };
	sd_sys *sys = sd_malloc(sizeof(sd_sys));
	*sys = val;
	return sys;
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

static void heo_free(sd_out *o) { sd_free(o); }
static sd_stat heo_apply(sd_out *o, double t,
	uint32_t nx, double * restrict x,
	uint32_t nc, double * restrict c)
{
	uint32_t i;
	/* unused */ (void) nc; (void) c; (void) o;
	EXPECT_EQ(4,nx);
	for (i=0; i<4; i++)
		EXPECT_EQ(x[i], xexpect[(int) t][i]);
	return t < 11 ? SD_CONT : SD_STOP;
}

static sd_out *heo_new()
{
	sd_out *o = sd_malloc (sizeof(sd_out));
	o->ptr = NULL;
	o->free = &heo_free;
	o->apply = &heo_apply;
	return o;
}

TEST(hist, exact) {
	uint32_t i, n=4, nnz, *Or, *Ic;
	double w[16], d[16], *nzw, *nzd, x0[4];
	sd_net *net;
	sd_sol *sol;
	sd_sch *sch = sd_sch_new_id(n);
	sd_sys *sys = het_new();
	sd_out *out = heo_new();
	sd_hfill *hf = sd_hfill_new_val(1.0);
	sd_hist *hist;

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
	sd_sparse_from_dense(n, n, w, d, 0.0, &nnz, &Or, &Ic, &nzw, &nzd);
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

	net = sd_net_new_hom(n, sys, 1, 1, 1, nnz, Or, Ic, nzw, nzd);

	EXPECT_EQ(3, nnz);
	EXPECT_EQ(4, net->get_ne(net));

	/* setup scheme & driver */
	sol = sd_sol_new_default(net->sys(net), sch, out, hf, 
			42, n, x0, 4, nnz, Ic, nzd, 0.0, 1.0);

	EXPECT_EQ(3, sol->get_nca(sol));
	hist = sol->get_hist(sol);
	EXPECT_EQ(3, hist->get_nu(hist));

	/* run */
	sol->cont(sol);

	/* tests performed in out function.. */

	/* clean up */
	sol->free(sol);
	sch->free(sch);
	net->free(net);
	sys->free(sys);
	out->free(out);
	hf->free(hf);
	sd_free(Or);
	sd_free(Ic);
	sd_free(nzw);
	sd_free(nzd);
}
