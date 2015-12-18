/* Apache 2.0 INS-AMU 2015 */

#include <stdio.h>

#include "sk_test.h"
#include "sk_out.h"

void test_out_file() {
	double t, x[2], c[1];
	sk_out_file_data d;
	FILE *fd;
	char *fname;

	t = 2.3;
	x[0] = 2*t;
	x[1] = 3*t;
	c[0] = 4*t;
	fname = "test_out_file.dat";

	sk_out_file_from_std(&d, stderr);
	sk_test_true(d.fd==stderr);
	sk_test_true(d.isstd==1);

	sk_out_file_from_fname(&d, fname);
	sk_test_true(d.isstd==0);

	sk_out_file_free(&d);

	sk_out_file_from_fname(&d, fname);
	sk_out_file(&d, t, 2, x, 1, c);
	sk_out_file_free(&d);

	fd = fopen(fname, "r");
	{
		int nx, nc;
		double t_, x_[2], c_[1];
		fscanf(fd, "%lf %d %lf %lf %d %lf\n", &t_, &nx, x_, x_+1, &nc, c_);
		sk_test_tol(t_, t, 1e-10);
		sk_test_true(nx==2);
		sk_test_tol(x_[0], x[0], 1e-10);
		sk_test_tol(x_[1], x[1], 1e-10);
		sk_test_true(nc==1);
		sk_test_tol(c_[0], c[0], 1e-10);
	}
	fclose(fd);
}

void test_out_mem() {
	int i;
	double t, x[3][2], c[1];
	sk_out_mem_data d;

	t = 2.3;
	for (i=0; i<6; i++)
		x[i/2][i%2] = i*t;
	c[0] = 4*t;

	sk_out_mem_init(&d);
	sk_test_true(d.xs==NULL);
	sk_test_true(d.cs==NULL);
	sk_test_true(d.n_sample==0);
	sk_test_true(d.capacity==0);
	sk_out_mem_free(&d);

	sk_out_mem_init(&d);
	sk_out_mem(&d, t, 2, x[0], 1, c);
	sk_test_true(d.capacity==2);
	sk_test_true(d.n_sample==1);
	sk_test_true(d.xs!=NULL);
	sk_test_true(d.cs!=NULL);
	sk_test_true(d.xs[0]==x[0][0]);
	sk_test_true(d.xs[1]==x[0][1]);
	sk_test_true(d.cs[0]==c[0]);

	sk_out_mem(&d, t+0.1, 2, x[1], 1, c);
	sk_test_true(d.xs[0]==x[0][0]);
	sk_test_true(d.xs[1]==x[0][1]);
	sk_test_true(d.xs[2+0]==x[1][0]);
	sk_test_true(d.xs[2+1]==x[1][1]);
	sk_test_true(d.cs[1+0]==c[0]);
	sk_test_true(d.capacity==4);
	sk_test_true(d.n_sample==2);

	sk_out_mem(&d, t+0.2, 2, x[2], 1, c);
	sk_test_true(d.xs[0]==x[0][0]);
	sk_test_true(d.xs[1]==x[0][1]);
	sk_test_true(d.xs[2+0]==x[1][0]);
	sk_test_true(d.xs[2+1]==x[1][1]);
	sk_test_true(d.xs[4+0]==x[2][0]);
	sk_test_true(d.xs[4+1]==x[2][1]);
	sk_test_true(d.cs[2+0]==c[0]);
	sk_test_true(d.capacity==4);
	sk_test_true(d.n_sample==3);
	sk_out_mem_free(&d);
}

void test_out_tee() {
	double t, x[2], c[1];
	sk_out_tee_data d;
	sk_out_mem_data m1, m2, m3;

	t = 2.3;
	x[0] = 2*t;
	x[1] = 3*t;
	c[0] = 4*t;

	sk_out_tee_init(&d, 3);
	sk_test_true(d.nout==3);
	sk_test_true(d.outs!=NULL);
	sk_test_true(d.outd!=NULL);

	sk_out_tee_set_out(&d, 0, sk_out_mem, &m1);
	sk_test_true(d.outs[0]==sk_out_mem);
	sk_test_true(d.outd[0]==&m1);
	sk_out_tee_set_out(&d, 1, sk_out_mem, &m2);
	sk_test_true(d.outs[0]==sk_out_mem);
	sk_test_true(d.outd[0]==&m1);
	sk_out_tee_set_out(&d, 2, sk_out_mem, &m3);
	sk_test_true(d.outs[0]==sk_out_mem);
	sk_test_true(d.outd[0]==&m1);
	sk_test_true(sk_out_tee_set_out(&d, 3, sk_out_mem, &m1)==1);

	sk_out_mem_init(&m1);
	sk_out_mem_init(&m2);
	sk_out_mem_init(&m3);

	sk_out_tee(&d, t, 2, x, 1, c);

	sk_test_true(m1.xs[0]==x[0]);
	sk_test_true(m1.xs[1]==x[1]);
	sk_test_true(m1.cs[0]==c[0]);
	sk_test_true(m2.xs[0]==x[0]);
	sk_test_true(m2.xs[1]==x[1]);
	sk_test_true(m2.cs[0]==c[0]);
	sk_test_true(m3.xs[0]==x[0]);
	sk_test_true(m3.xs[1]==x[1]);
	sk_test_true(m3.cs[0]==c[0]);

	sk_out_mem_free(&m1);
	sk_out_mem_free(&m2);
	sk_out_mem_free(&m3);

	sk_out_tee_free(&d);
}

void test_out_tavg() {
	int i;
	double t, x[2], c[1];
	sk_out_tavg_data d;
	sk_out_mem_data m;

	t = 0.0;
	x[0] = 0.0;
	c[0] = 1.0;

	sk_out_mem_init(&m);
	sk_out_tavg_init(&d, 10, sk_out_mem, &m);
	sk_out_tavg_free(&d); /* check incorrect free()s */
	sk_out_tavg_init(&d, 10, sk_out_mem, &m);
	sk_test_true(d.len==10);
	sk_test_true(d.pos==0);
	sk_test_true(d.t==0.0);
	sk_test_true(d.out==sk_out_mem);
	sk_test_true(d.outd==&m);
	sk_test_true(d.x==NULL);
	sk_test_true(d.c==NULL);

	sk_out_tavg(&d, t, 1, x, 1, c);
	sk_test_true(d.x!=NULL);
	sk_test_true(d.c!=NULL);
	sk_test_true(d.t==t);
	sk_test_true(d.pos==1);
	for (i=0; i<8; i++) {
		x[0] += 1;
		c[0] += 1;
		sk_out_tavg(&d, 1.0, 1, x, 1, c);
		sk_test_tol(d.t, i+1.0, 1e-10);
		sk_test_true(d.pos==(i+2));
	}
	x[0] += 1;
	c[0] += 1;
	sk_out_tavg(&d, 1.0, 1, x, 1, c);
	sk_test_true(d.pos==0);
	sk_test_true(d.x[0]==0.0);
	sk_test_true(d.c[0]==0.0);
	sk_test_true(d.t==0.0);

	sk_test_tol(m.xs[0], 4.5, 1e-10);
	sk_test_tol(m.cs[0], 5.5, 1e-10);

	sk_out_tavg_free(&d);
	sk_out_mem_free(&m);
}

void test_out_sfilt() {
	int i;
	double t, x[2], c[2], xf[4], cf[4];
	sk_out_sfilt_data d;
	sk_out_mem_data m;

	xf[0] = cf[2] = 1.0;
	xf[1] = cf[3] = 1.0;
	xf[2] = cf[0] = 1.0;
	xf[3] = cf[1] = -1.0;

	sk_out_mem_init(&m);
	sk_out_sfilt_init(&d, 2, 2, xf, cf, sk_out_mem, &m);
	sk_test_true(d.nfilt==2);
	sk_test_true(d.filtlen==2);
	sk_test_true(d.xfilts!=NULL);
	sk_test_true(d.cfilts!=NULL);
	sk_test_true(d.x!=NULL);
	sk_test_true(d.c!=NULL);
	sk_test_true(d.out==sk_out_mem);
	sk_test_true(d.outd==&m);
	for (i=0; i<4; i++) {
		sk_test_true(d.xfilts[i]==xf[i]);
		sk_test_true(d.cfilts[i]==cf[i]);
	}

	sk_out_sfilt_free(&d);

	sk_out_sfilt_init(&d, 2, 2, xf, cf, sk_out_mem, &m);

	t = 0.0;
	x[0] = 1.0;
	x[1] = 2.0;
	c[0] = 0.5;
	c[1] = 1.0;

	sk_out_sfilt(&d, t, 2, x, 2, c);

	sk_test_tol(m.xs[0], 3.0, 1e-10);
	sk_test_tol(m.xs[1], -1.0, 1e-10);
	sk_test_tol(m.cs[0], -0.5, 1e-10);
	sk_test_tol(m.cs[1], 1.5, 1e-10);

	sk_out_sfilt_free(&d);
	sk_out_mem_free(&m);
}


int main() {
	test_out_file();
	test_out_mem();
	test_out_tee();
	test_out_tavg();
	test_out_sfilt();
	return sk_test_report();
}

