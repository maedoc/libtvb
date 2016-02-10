/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

TEST(net, simple) {

	uint32_t n, ns, na, ne, nnz, *Ic, *Or, *vi;
	double *w, *d, *vd;
	sd_net *net;
	sd_sys_exc *exc;
	sd_sys *sys;
	sd_hist *hist;

	n = 3;
	ns = 2;
	na = 1;
	ne = 1;
	nnz = 2;
	Or = sd_malloc (sizeof(uint32_t)*(n+1));
	Ic = sd_malloc (sizeof(uint32_t)*nnz);
	w = sd_malloc (sizeof(double)*nnz);
	d = sd_malloc (sizeof(double)*nnz);
	Or[0] = 0;
	Or[1] = 1;
	Or[2] = 2;
	Or[3] = 2;
	Ic[0] = 1;
	Ic[1] = 2;
	w[0] = 1.0;
	w[1] = 2.0;
	d[0] = 10.0;
	d[1] = 20.0;
	exc = sd_sys_exc_new();
	sys = exc->sys(exc);
	exc->set_a(exc, 1.0);
	exc->set_k(exc, 0.5);
	exc->set_tau(exc, 3.0);
	vi = sd_malloc (sizeof(uint32_t)*n);
	vd = sd_malloc (sizeof(double)*n);
	vi[0] = 0;
	vi[1] = 1;
	vi[2] = 2;
	vd[0] = 0.0;
	vd[1] = 0.0;
	vd[2] = 0.0;
	hist = sd_hist_new_default(n, vi, vd, 0.0, 1.0);

	net = sd_net_new_hom(n, sys, ns, na, ne, nnz, Or, Ic, w, d);

	/* initn */
	EXPECT_EQ(n,net->get_n(net));
	EXPECT_EQ(1,net->get_m(net));
	EXPECT_EQ(nnz,net->get_nnz(net));
	EXPECT_EQ(Or,net->get_or(net));
	EXPECT_EQ(Ic,net->get_ic(net));
	EXPECT_EQ(w,net->get_w(net));
	EXPECT_EQ(d,net->get_d(net));
	EXPECT_EQ(ns*n,net->get_ns(net));
	EXPECT_EQ(ne*n,net->get_ne(net));
	EXPECT_TRUE(!net->cn_is_null(net));

	/* init1 */
	EXPECT_EQ(ns, net->get_Ms_i(net, 0));
	EXPECT_EQ(ne, net->get_Me_i(net, 0));
	EXPECT_EQ(0, net->get_M_i(net, 0));
	EXPECT_EQ(0, net->get_M_i(net, 1));
	EXPECT_EQ(0, net->get_M_i(net, 1));
	EXPECT_EQ(sys, net->get_models_i(net, 0));
	EXPECT_EQ(1, net->get__init1(net));

	/* evaluate */
	sd_sys_in in;
	sd_sys_out out;
	in.nx = n*ns;
	in.nc = n*ne;
	in.id = 0;
	in.t = 0.0;
	in.x = sd_malloc (sizeof(double) * n*ns);
	in.hist = hist;
	in.rng = NULL;
	out.f = sd_malloc (sizeof(double) * n*ns);
	out.g = sd_malloc (sizeof(double) * n*ns);
	{
		uint32_t i;
		for (i=0; i<(n*ns); i++)
			out.f[i] = out.g[i] = 1.0/0.0;
	}
	in.i = out.o = sd_malloc (sizeof(double) * n*ne);
	in.i[0] = in.x[0] = 1.0;
	in.i[1] = in.x[2] = 2.0;
	in.i[2] = in.x[4] = 3.0;
	SD_CALL_AS(net, sys, apply, &in, &out);
	ASSERT_NEAR((exc->get_a(exc) - in.x[0] + exc->get_k(exc)*w[0]*in.x[2])/exc->get_tau(exc), out.f[1], 1e-15);
	ASSERT_NEAR((exc->get_a(exc) - in.x[2] + exc->get_k(exc)*w[1]*in.x[4])/exc->get_tau(exc), out.f[3], 1e-15);
	ASSERT_NEAR((exc->get_a(exc) - in.x[4])/exc->get_tau(exc), out.f[5], 1e-15);

	/* clean up */
	sys->free(sys);
	net->free(net);
	hist->free(hist);
	sd_free(Or);
	sd_free(Ic);
	sd_free(w);
	sd_free(d);
	sd_free(in.x);
	sd_free(out.f);
	sd_free(out.g);
	sd_free(out.o);
	sd_free(vi);
	sd_free(vd);
}
