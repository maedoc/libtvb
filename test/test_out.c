/* Apache 2.0 INS-AMU 2015 */

#include <stdio.h>

#include "sddekit.h"

TEST(out, file) {
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
	EXPECT_EQ(stderr,d.fd);
	EXPECT_EQ(1,d.isstd);

	sk_out_file_from_fname(&d, fname);
	EXPECT_EQ(0,d.isstd);

	sk_out_file_free(&d);

	sk_out_file_from_fname(&d, fname);
	sk_out_file(&d, t, 2, x, 1, c);
	sk_out_file_free(&d);

	fd = fopen(fname, "r");
	{
		int nx, nc;
		double t_, x_[2], c_[1];
		fscanf(fd, "%lf %d %lf %lf %d %lf\n", &t_, &nx, x_, x_+1, &nc, c_);
		ASSERT_NEAR(t_, t, 1e-10);
		EXPECT_EQ(2,nx);
		ASSERT_NEAR(x_[0], x[0], 1e-10);
		ASSERT_NEAR(x_[1], x[1], 1e-10);
		EXPECT_EQ(1,nc);
		ASSERT_NEAR(c_[0], c[0], 1e-10);
	}
	fclose(fd);
}

TEST(out, mem) {
	int i;
	double t, x[3][2], c[1];
	sk_out_mem_data d;

	t = 2.3;
	for (i=0; i<6; i++)
		x[i/2][i%2] = i*t;
	c[0] = 4*t;

	sk_out_mem_init(&d);
	EXPECT_EQ(NULL,d.xs);
	EXPECT_EQ(NULL,d.cs);
	EXPECT_EQ(0,d.n_sample);
	EXPECT_EQ(0,d.capacity);
	sk_out_mem_free(&d);

	sk_out_mem_init(&d);
	sk_out_mem(&d, t, 2, x[0], 1, c);
	EXPECT_EQ(2,d.capacity);
	EXPECT_EQ(1,d.n_sample);
	EXPECT_TRUE(NULL!=d.xs);
	EXPECT_TRUE(NULL!=d.cs);
	EXPECT_EQ(x[0][0],d.xs[0]);
	EXPECT_EQ(x[0][1],d.xs[1]);
	EXPECT_EQ(c[0],d.cs[0]);

	sk_out_mem(&d, t+0.1, 2, x[1], 1, c);
	EXPECT_EQ(x[0][0],d.xs[0]);
	EXPECT_EQ(x[0][1],d.xs[1]);
	EXPECT_EQ(x[1][0],d.xs[2+0]);
	EXPECT_EQ(x[1][1],d.xs[2+1]);
	EXPECT_EQ(c[0],d.cs[1+0]);
	EXPECT_EQ(4,d.capacity);
	EXPECT_EQ(2,d.n_sample);

	sk_out_mem(&d, t+0.2, 2, x[2], 1, c);
	EXPECT_EQ(x[0][0],d.xs[0]);
	EXPECT_EQ(x[0][1],d.xs[1]);
	EXPECT_EQ(x[1][0],d.xs[2+0]);
	EXPECT_EQ(x[1][1],d.xs[2+1]);
	EXPECT_EQ(x[2][0],d.xs[4+0]);
	EXPECT_EQ(x[2][1],d.xs[4+1]);
	EXPECT_EQ(c[0],d.cs[2+0]);
	EXPECT_EQ(4,d.capacity);
	EXPECT_EQ(3,d.n_sample);
	sk_out_mem_free(&d);
}

TEST(out, tee) {
	double t, x[2], c[1];
	sk_out_tee_data d;
	sk_out_mem_data m1, m2, m3;

	t = 2.3;
	x[0] = 2*t;
	x[1] = 3*t;
	c[0] = 4*t;

	sk_out_tee_init(&d, 3);
	EXPECT_EQ(3,d.nout);
	EXPECT_TRUE(d.outs!=NULL);
	EXPECT_TRUE(d.outd!=NULL);

	sk_out_tee_set_out(&d, 0, sk_out_mem, &m1);
	EXPECT_EQ(&sk_out_mem,d.outs[0]);
	EXPECT_EQ(&m1,d.outd[0]);
	sk_out_tee_set_out(&d, 1, sk_out_mem, &m2);
	EXPECT_EQ(&sk_out_mem,d.outs[0]);
	EXPECT_EQ(&m1,d.outd[0]);
	sk_out_tee_set_out(&d, 2, sk_out_mem, &m3);
	EXPECT_EQ(&sk_out_mem,d.outs[0]);
	EXPECT_EQ(&m1,d.outd[0]);
	EXPECT_EQ(1,sk_out_tee_set_out(&d, 3, sk_out_mem, &m1));

	sk_out_mem_init(&m1);
	sk_out_mem_init(&m2);
	sk_out_mem_init(&m3);

	sk_out_tee(&d, t, 2, x, 1, c);

	EXPECT_EQ(x[0],m1.xs[0]);
	EXPECT_EQ(x[1],m1.xs[1]);
	EXPECT_EQ(c[0],m1.cs[0]);
	EXPECT_EQ(x[0],m2.xs[0]);
	EXPECT_EQ(x[1],m2.xs[1]);
	EXPECT_EQ(c[0],m2.cs[0]);
	EXPECT_EQ(x[0],m3.xs[0]);
	EXPECT_EQ(x[1],m3.xs[1]);
	EXPECT_EQ(c[0],m3.cs[0]);

	sk_out_mem_free(&m1);
	sk_out_mem_free(&m2);
	sk_out_mem_free(&m3);

	sk_out_tee_free(&d);
}

TEST(out, tavg) {
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
	EXPECT_EQ(10,d.len);
	EXPECT_EQ(0,d.pos);
	EXPECT_EQ(0.0,d.t);
	EXPECT_EQ(&sk_out_mem,d.out);
	EXPECT_EQ(&m,d.outd);
	EXPECT_EQ(NULL,d.x);
	EXPECT_EQ(NULL,d.c);

	sk_out_tavg(&d, t, 1, x, 1, c);
	EXPECT_TRUE(NULL!=d.x);
	EXPECT_TRUE(NULL!=d.c);
	EXPECT_EQ(t,d.t);
	EXPECT_EQ(1,d.pos);
	for (i=0; i<8; i++) {
		x[0] += 1;
		c[0] += 1;
		sk_out_tavg(&d, 1.0, 1, x, 1, c);
		ASSERT_NEAR(d.t, i+1.0, 1e-10);
		EXPECT_EQ((i+2),d.pos);
	}
	x[0] += 1;
	c[0] += 1;
	sk_out_tavg(&d, 1.0, 1, x, 1, c);
	EXPECT_EQ(0,d.pos);
	EXPECT_EQ(0.0,d.x[0]);
	EXPECT_EQ(0.0,d.c[0]);
	EXPECT_EQ(0.0,d.t);

	ASSERT_NEAR(m.xs[0], 4.5, 1e-10);
	ASSERT_NEAR(m.cs[0], 5.5, 1e-10);

	sk_out_tavg_free(&d);
	sk_out_mem_free(&m);
}

TEST(out, sfilt) {
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
	EXPECT_EQ(2,d.nfilt);
	EXPECT_EQ(2,d.filtlen);
	EXPECT_TRUE(NULL!=d.xfilts);
	EXPECT_TRUE(NULL!=d.cfilts);
	EXPECT_TRUE(NULL!=d.x);
	EXPECT_TRUE(NULL!=d.c);
	EXPECT_EQ(&sk_out_mem,d.out);
	EXPECT_EQ(&m,d.outd);
	for (i=0; i<4; i++) {
		EXPECT_EQ(xf[i],d.xfilts[i]);
		EXPECT_EQ(cf[i],d.cfilts[i]);
	}

	sk_out_sfilt_free(&d);

	sk_out_sfilt_init(&d, 2, 2, xf, cf, sk_out_mem, &m);

	t = 0.0;
	x[0] = 1.0;
	x[1] = 2.0;
	c[0] = 0.5;
	c[1] = 1.0;

	sk_out_sfilt(&d, t, 2, x, 2, c);

	ASSERT_NEAR(m.xs[0], 3.0, 1e-10);
	ASSERT_NEAR(m.xs[1], -1.0, 1e-10);
	ASSERT_NEAR(m.cs[0], -0.5, 1e-10);
	ASSERT_NEAR(m.cs[1], 1.5, 1e-10);

	sk_out_sfilt_free(&d);
	sk_out_mem_free(&m);
}
