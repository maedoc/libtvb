/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

static sd_stat test_net_apply(
		void *data, 
		struct sd_sys_in *in,
		struct sd_sys_out *out
		)
{
	(void) data;
	out->o[0] = in->i[0];
	return SD_OK;
}

TEST(net, matmult)
{
	struct sd_rng *rng = sd_rng_new_default();
	rng->seed(rng, 42);

	uint32_t n=10, Ic[100], Or[11];
	double w[100], i[100], x[10], f[10], g[10], o[100];

	for (int j=0; j<10; j++)
	{
		Or[j] = j*10;
		for (int k=0; k<10; k++)
		{
			w[j*10+k] = rng->norm(rng); 
			Ic[j*10+k] = k;
			if (j==0)
				i[k] = rng->norm(rng);
			else
				i[j*10+k] = i[k];
		}
	}
	Or[10] = 100;

	struct sd_sys *sys = sd_sys_new_cb(1, 1, 1, 0, 0, NULL, &test_net_apply);
	struct sd_net *net = sd_net_new_hom(n, sys, 1, 1, 1, 100, Or, Ic, w, NULL);
	struct sd_sys *net_sys = net->sys(net);

	struct sd_sys_in in = {.nx=10, .nc=10, .id=0, .t=0.0, .x=x, .i=i, .hist=NULL, .rng=NULL};
	struct sd_sys_out out = {.f=f, .g=g, .o=o};
	net_sys->apply(net_sys, &in, &out);

	for (int j=0; j<10; j++)
	{
		double sum=0.0;
		for (int k=0; k<10; k++)
			sum += w[j*10+k] * i[j*10 + k];
		ASSERT_NEAR(sum, o[j], 1e-15);
	}

	net->free(net);
	sys->free(sys);
	rng->free(rng);
}

TEST(net, simple) {

	sd_net *net;
	sd_sys_exc *exc;
	sd_sys *sys;

	/* three nodes with feedforward arch 0 -> 1 -> 2 */
	uint32_t n=3, ns=2, na=1, ne=1, nnz=2
	       , Or[] = { 0, 0, 1, 2 }
	       , Ic[] = { 0, 1 };
	double w[] = { 0.1, 0.2 };

	exc = sd_sys_exc_new();
	sys = exc->sys(exc);
	exc->set_a(exc, 1.0);
	exc->set_k(exc, 0.5);
	exc->set_tau(exc, 3.0);

	uint32_t vi[] = { 0, 1 };
	double vd[] = { 0.0, 0.0 };
	struct sd_hist *hist = sd_hist_new_default(2, vi, vd, 0.0, 1.0);

	net = sd_net_new_hom(n, sys, ns, na, ne, nnz, Or, Ic, w, vd);

	/* initn */
	EXPECT_EQ(n,net->get_n(net));
	EXPECT_EQ(1,net->get_m(net));
	EXPECT_EQ(nnz,net->get_nnz(net));
	EXPECT_EQ(Or,net->get_or(net));
	EXPECT_EQ(Ic,net->get_ic(net));
	EXPECT_EQ(w,net->get_w(net));
	EXPECT_EQ(vd,net->get_d(net));
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
	{
		double a=exc->get_a(exc), k=exc->get_k(exc),
		       tau=exc->get_tau(exc)
		     , f1 = (a - in.x[0])/tau
		     , f3 = (a - in.x[2] + k*w[0]*in.x[0])/tau
		     , f5 = (a - in.x[4] + k*w[1]*in.x[2])/tau
		     ;
		ASSERT_NEAR(f1, out.f[1], 1e-15);
		ASSERT_NEAR(f3, out.f[3], 1e-15);
		ASSERT_NEAR(f5, out.f[5], 1e-15);

	}

	/* clean up */
	sys->free(sys);
	net->free(net);
	hist->free(hist);
	sd_free(in.x);
	sd_free(out.f);
	sd_free(out.g);
	sd_free(out.o);
}
