/* copyright 2016 Apache 2 sddekit authors */

#include <stdlib.h>

#include "sddekit.h"

TEST(net, simple) {

	int n, ns, ne, nnz, *Ic, *Or, *vi;
	double *w, *d, *x, *f, *g, *c, *vd;
	sk_net_data *net;
	sk_sys_exc_dat *sysd;
	sk_hist *hist;

	n = 3;
	ns = 2;
	ne = 1;
	nnz = 2;
	Or = sk_malloc (sizeof(int)*(n+1));
	Ic = sk_malloc (sizeof(int)*nnz);
	w = sk_malloc (sizeof(double)*nnz);
	d = sk_malloc (sizeof(double)*nnz);
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
	sysd = sk_sys_exc_alloc();
	sk_sys_exc_set_a(sysd, 1.0);
	sk_sys_exc_set_k(sysd, 0.5);
	sk_sys_exc_set_tau(sysd, 3.0);
	vi = sk_malloc (sizeof(int)*n);
	vd = sk_malloc (sizeof(double)*n);
	vi[0] = 0;
	vi[1] = 1;
	vi[2] = 2;
	vd[0] = 0.0;
	vd[1] = 0.0;
	vd[2] = 0.0;
	hist = sk_hist_alloc();
	sk_hist_init(hist, n, vi, vd, 0, 1);

	net = sk_net_alloc();
	sk_net_init1(net, n, sk_sys_exc, sysd, ns, ne, nnz, Or, Ic, w, d);

	/* initn */
	EXPECT_EQ(n,sk_net_get_n(net));
	EXPECT_EQ(1,sk_net_get_m(net));
	EXPECT_EQ(nnz,sk_net_get_nnz(net));
	EXPECT_EQ(Or,sk_net_get_or(net));
	EXPECT_EQ(Ic,sk_net_get_ic(net));
	EXPECT_EQ(w,sk_net_get_w(net));
	EXPECT_EQ(d,sk_net_get_d(net));
	EXPECT_EQ(ns*n,sk_net_get_ns(net));
	EXPECT_EQ(ne*n,sk_net_get_ne(net));
	EXPECT_TRUE(!sk_net_cn_is_null(net));

	/* init1 */
	EXPECT_EQ(ns, sk_net_get_Ms_i(net, 0));
	EXPECT_EQ(ne, sk_net_get_Me_i(net, 0));
	EXPECT_EQ(0, sk_net_get_M_i(net, 0));
	EXPECT_EQ(0, sk_net_get_M_i(net, 1));
	EXPECT_EQ(0, sk_net_get_M_i(net, 1));
	EXPECT_EQ(&sk_sys_exc, sk_net_get_models_i(net, 0));
	EXPECT_EQ(sysd, sk_net_get_models_data_i(net, 0));
	EXPECT_EQ(1, sk_net_get__init1(net));

	/* evaluate */
	x = sk_malloc (sizeof(double) * n*ns);
	f = sk_malloc (sizeof(double) * n*ns);
	g = sk_malloc (sizeof(double) * n*ns);
	c = sk_malloc (sizeof(double) * n*ne);
	c[0] = x[0] = 1.0;
	c[1] = x[2] = 2.0;
	c[2] = x[4] = 3.0;
	sk_net_sys(net, hist, 0.0, 0, n*ns, x, f, g, NULL, NULL, n*ne, c, NULL, NULL);
	EXPECT_EQ((sk_sys_exc_get_a(sysd) - x[0] + sk_sys_exc_get_k(sysd)*w[0]*x[2])/sk_sys_exc_get_tau(sysd),f[1]);
	EXPECT_EQ((sk_sys_exc_get_a(sysd) - x[2] + sk_sys_exc_get_k(sysd)*w[1]*x[4])/sk_sys_exc_get_tau(sysd),f[3]);
	EXPECT_EQ((sk_sys_exc_get_a(sysd) - x[4])/sk_sys_exc_get_tau(sysd),f[5]);

	/* clean up */
	sk_sys_exc_free(sysd);
	sk_net_free(net);
	sk_hist_free(hist);
	sk_free(Or);
	sk_free(Ic);
	sk_free(w);
	sk_free(d);
	sk_free(x);
	sk_free(f);
	sk_free(g);
	sk_free(c);
	sk_free(vi);
	sk_free(vd);
}
