/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>

#include "sk_test.h"
#include "sk_net.h"
#include "sk_sys.h"
#include "sk_hist.h"

int test_net1()
{

	int n, ns, ne, nnz, *Ic, *Or;
	double *w, *d, *x, *f, *g, *c;
	sk_net_data net;
	sk_sys_exc_dat sysd;
	sk_hist hist;

	n = 3;
	ns = 2;
	ne = 1;
	nnz = 2;
	Or = malloc (sizeof(int)*(n+1));
	Ic = malloc (sizeof(int)*nnz);
	w = malloc (sizeof(double)*nnz);
	d = malloc (sizeof(double)*nnz);
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
	sysd.a = 1.0;
	sysd.k = 0.5;
	sysd.tau = 3.0;
	hist.vi2i = malloc (sizeof(int)*n);
	hist.vi2i[0] = 0;
	hist.vi2i[1] = 1;
	hist.vi2i[2] = 2;

	sk_net_init1(&net, n, sk_sys_exc, &sysd, ns, ne, nnz, Or, Ic, w, d);

	/* initn */
	sk_test_true(net.n==n);
	sk_test_true(net.m==1);
	sk_test_true(net.nnz==nnz);
	sk_test_true(net.Or==Or);
	sk_test_true(net.Ic==Ic);
	sk_test_true(net.w==w);
	sk_test_true(net.d==d);
	sk_test_true(net.ns==ns*n);
	sk_test_true(net.ne==ne*n);
	sk_test_true(net.cn!=NULL);

	/* init1 */
	sk_test_true(net.Ms[0]==ns);
	sk_test_true(net.Me[0]==ne);
	sk_test_true(net.M[0]==0);
	sk_test_true(net.M[1]==0);
	sk_test_true(net.M[1]==0);
	sk_test_true(net.models[0]==sk_sys_exc);
	sk_test_true(net.models_data[0]==&sysd);
	sk_test_true(net._init1==1);

	/* evaluate */
	x = malloc (sizeof(double) * n*ns);
	f = malloc (sizeof(double) * n*ns);
	g = malloc (sizeof(double) * n*ns);
	c = malloc (sizeof(double) * n*ne);
	c[0] = x[0] = 1.0;
	c[1] = x[2] = 2.0;
	c[2] = x[4] = 3.0;
	sk_net_sys(&net, &hist, 0.0, n*ns, x, f, g, NULL, NULL, n*ne, c, NULL);
	sk_test_true(f[1]==(sysd.a - x[0] + sysd.k*w[0]*x[2])/sysd.tau);
	sk_test_true(f[3]==(sysd.a - x[2] + sysd.k*w[1]*x[4])/sysd.tau);
	sk_test_true(f[5]==(sysd.a - x[4])/sysd.tau);

	/* clean up */
	sk_net_free(&net);
	free(hist.vi2i);
	free(Or);
	free(Ic);
	free(w);
	free(d);
	free(x);
	free(f);
	free(g);
	free(c);

	return 0;
}


int test_netn()
{
	return 0;
}
