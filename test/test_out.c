/* Apache 2.0 INS-AMU 2015 */

#include <stdio.h>

#include "sddekit.h"

TEST(out, file) {
	double t, x[2], c[1];
	sk_out_file_data *d;
	FILE *fd;
	char *fname;

	t = 2.3;
	x[0] = 2*t;
	x[1] = 3*t;
	c[0] = 4*t;
	fname = "test_out_file.dat";

	sk_out_file_from_std(d=sk_out_file_alloc(), stderr);
	EXPECT_EQ(stderr, sk_out_file_get_fd(d));
	EXPECT_EQ(1, sk_out_file_is_std(d));

	sk_out_file_from_fname(d, fname);
	EXPECT_EQ(0, sk_out_file_is_std(d));

	sk_out_file_free(d);

	sk_out_file_from_fname(d=sk_out_file_alloc(), fname);
	sk_out_file(d, t, 2, x, 1, c);
	sk_out_file_free(d);

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
	sk_out_mem_data *d;

	t = 2.3;
	for (i=0; i<6; i++)
		x[i/2][i%2] = i*t;
	c[0] = 4*t;

	sk_out_mem_init(d=sk_out_mem_alloc());
	EXPECT_EQ(NULL, sk_out_mem_get_xs(d));
	EXPECT_EQ(NULL, sk_out_mem_get_cs(d));
	EXPECT_EQ(0, sk_out_mem_get_n_sample(d));
	EXPECT_EQ(0, sk_out_mem_get_capacity(d));
	sk_out_mem_free(d);

	sk_out_mem_init(d=sk_out_mem_alloc());
	sk_out_mem(d, t, 2, x[0], 1, c);
	EXPECT_EQ(2,sk_out_mem_get_capacity(d));
	EXPECT_EQ(1,sk_out_mem_get_n_sample(d));
	EXPECT_TRUE(NULL!=sk_out_mem_get_xs(d));
	EXPECT_TRUE(NULL!=sk_out_mem_get_cs(d));
	EXPECT_EQ(x[0][0],sk_out_mem_get_xs(d)[0]);
	EXPECT_EQ(x[0][1],sk_out_mem_get_xs(d)[1]);
	EXPECT_EQ(c[0],sk_out_mem_get_cs(d)[0]);

	sk_out_mem(d, t+0.1, 2, x[1], 1, c);
	EXPECT_EQ(x[0][0],sk_out_mem_get_xs(d)[0]);
	EXPECT_EQ(x[0][1],sk_out_mem_get_xs(d)[1]);
	EXPECT_EQ(x[1][0],sk_out_mem_get_xs(d)[2+0]);
	EXPECT_EQ(x[1][1],sk_out_mem_get_xs(d)[2+1]);
	EXPECT_EQ(c[0],sk_out_mem_get_cs(d)[1+0]);
	EXPECT_EQ(4,sk_out_mem_get_capacity(d));
	EXPECT_EQ(2,sk_out_mem_get_n_sample(d));

	sk_out_mem(d, t+0.2, 2, x[2], 1, c);
	EXPECT_EQ(x[0][0],sk_out_mem_get_xs(d)[0]);
	EXPECT_EQ(x[0][1],sk_out_mem_get_xs(d)[1]);
	EXPECT_EQ(x[1][0],sk_out_mem_get_xs(d)[2+0]);
	EXPECT_EQ(x[1][1],sk_out_mem_get_xs(d)[2+1]);
	EXPECT_EQ(x[2][0],sk_out_mem_get_xs(d)[4+0]);
	EXPECT_EQ(x[2][1],sk_out_mem_get_xs(d)[4+1]);
	EXPECT_EQ(c[0],sk_out_mem_get_cs(d)[2+0]);
	EXPECT_EQ(4,sk_out_mem_get_capacity(d));
	EXPECT_EQ(3,sk_out_mem_get_n_sample(d));
	sk_out_mem_free(d);
}

TEST(out, tee) {
	double t, x[2], c[1];
	sk_out_tee_data *d;
	sk_out_mem_data *m1, *m2, *m3;

	t = 2.3;
	x[0] = 2*t;
	x[1] = 3*t;
	c[0] = 4*t;

	sk_out_tee_init(d=sk_out_tee_alloc(), 3);
	EXPECT_EQ(3,sk_out_tee_get_nout(d));
	EXPECT_TRUE(!sk_out_tee_outs_is_null(d));
	EXPECT_TRUE(!sk_out_tee_outd_is_null(d));

	sk_out_mem_init(m1=sk_out_mem_alloc());
	sk_out_mem_init(m2=sk_out_mem_alloc());
	sk_out_mem_init(m3=sk_out_mem_alloc());

	sk_out_tee_set_out(d, 0, sk_out_mem, m1);
	EXPECT_EQ(&sk_out_mem,sk_out_tee_get_out_i(d, 0));
	EXPECT_EQ(m1,sk_out_tee_get_outd_i(d, 0));
	sk_out_tee_set_out(d, 1, sk_out_mem, m2);
	EXPECT_EQ(&sk_out_mem,sk_out_tee_get_out_i(d, 0));
	EXPECT_EQ(m1,sk_out_tee_get_outd_i(d, 0));
	sk_out_tee_set_out(d, 2, sk_out_mem, m3);
	EXPECT_EQ(&sk_out_mem,sk_out_tee_get_out_i(d, 0));
	EXPECT_EQ(m1,sk_out_tee_get_outd_i(d, 0));
	EXPECT_EQ(1,sk_out_tee_set_out(d, 3, sk_out_mem, m1));

	sk_out_tee(d, t, 2, x, 1, c);

	EXPECT_EQ(x[0], sk_out_mem_get_xs(m1)[0]);
	EXPECT_EQ(x[1], sk_out_mem_get_xs(m1)[1]);
	EXPECT_EQ(c[0], sk_out_mem_get_cs(m1)[0]);
	EXPECT_EQ(x[0], sk_out_mem_get_xs(m2)[0]);
	EXPECT_EQ(x[1], sk_out_mem_get_xs(m2)[1]);
	EXPECT_EQ(c[0], sk_out_mem_get_cs(m2)[0]);
	EXPECT_EQ(x[0], sk_out_mem_get_xs(m3)[0]);
	EXPECT_EQ(x[1], sk_out_mem_get_xs(m3)[1]);
	EXPECT_EQ(c[0], sk_out_mem_get_cs(m3)[0]);

	sk_out_mem_free(m1);
	sk_out_mem_free(m2);
	sk_out_mem_free(m3);

	sk_out_tee_free(d);
}

TEST(out, tavg) {
	int i;
	double t, x[2], c[1];
	sk_out_tavg_data *d;
	sk_out_mem_data *m;

	t = 0.0;
	x[0] = 0.0;
	c[0] = 1.0;

	sk_out_mem_init(m=sk_out_mem_alloc());
	sk_out_tavg_init(d=sk_out_tavg_alloc(), 10, sk_out_mem, m);
	sk_out_tavg_free(d); /* check incorrect free()s */
	sk_out_tavg_init(d=sk_out_tavg_alloc(), 10, sk_out_mem, m);
	EXPECT_EQ(10, sk_out_tavg_get_len(d));
	EXPECT_EQ(0, sk_out_tavg_get_pos(d));
	EXPECT_EQ(0.0, sk_out_tavg_get_t(d));
	EXPECT_EQ(&sk_out_mem, sk_out_tavg_get_out(d));
	EXPECT_EQ(m, sk_out_tavg_get_outd(d));
	EXPECT_EQ(NULL, sk_out_tavg_get_x(d));
	EXPECT_EQ(NULL, sk_out_tavg_get_c(d));

	sk_out_tavg(d, t, 1, x, 1, c);
	EXPECT_TRUE(NULL!= sk_out_tavg_get_x(d));
	EXPECT_TRUE(NULL!= sk_out_tavg_get_c(d));
	EXPECT_EQ(t, sk_out_tavg_get_t(d));
	EXPECT_EQ(1, sk_out_tavg_get_pos(d));
	for (i=0; i<8; i++) {
		x[0] += 1;
		c[0] += 1;
		sk_out_tavg(d, 1.0, 1, x, 1, c);
		ASSERT_NEAR( sk_out_tavg_get_t(d), i+1.0, 1e-10);
		EXPECT_EQ((i+2), sk_out_tavg_get_pos(d));
	}
	x[0] += 1;
	c[0] += 1;
	sk_out_tavg(d, 1.0, 1, x, 1, c);
	EXPECT_EQ(0, sk_out_tavg_get_pos(d));
	EXPECT_EQ(0.0, sk_out_tavg_get_x(d)[0]);
	EXPECT_EQ(0.0, sk_out_tavg_get_c(d)[0]);
	EXPECT_EQ(0.0, sk_out_tavg_get_t(d));

	ASSERT_NEAR( sk_out_mem_get_xs(m)[0], 4.5, 1e-10);
	ASSERT_NEAR( sk_out_mem_get_cs(m)[0], 5.5, 1e-10);

	sk_out_tavg_free(d);
	sk_out_mem_free(m);
}

TEST(out, sfilt) {
	int i;
	double t, x[2], c[2], xf[4], cf[4];
	sk_out_sfilt_data *d;
	sk_out_mem_data *m;

	xf[0] = cf[2] = 1.0;
	xf[1] = cf[3] = 1.0;
	xf[2] = cf[0] = 1.0;
	xf[3] = cf[1] = -1.0;

	sk_out_mem_init(m=sk_out_mem_alloc());
	sk_out_sfilt_init(d=sk_out_sfilt_alloc(), 2, 2, xf, cf, sk_out_mem, m);
	EXPECT_EQ(2, sk_out_sfilt_get_nfilt(d));
	EXPECT_EQ(2, sk_out_sfilt_get_filtlen(d));
	EXPECT_TRUE(NULL!= sk_out_sfilt_get_xfilts(d));
	EXPECT_TRUE(NULL!= sk_out_sfilt_get_cfilts(d));
	EXPECT_TRUE(NULL!= sk_out_sfilt_get_x(d));
	EXPECT_TRUE(NULL!= sk_out_sfilt_get_c(d));
	EXPECT_EQ(&sk_out_mem, sk_out_sfilt_get_out(d));
	EXPECT_EQ(m, sk_out_sfilt_get_outd(d));
	for (i=0; i<4; i++) {
		EXPECT_EQ(xf[i], sk_out_sfilt_get_xfilts(d)[i]);
		EXPECT_EQ(cf[i], sk_out_sfilt_get_cfilts(d)[i]);
	}

	sk_out_sfilt_free(d);

	sk_out_sfilt_init(d=sk_out_sfilt_alloc(), 2, 2, xf, cf, sk_out_mem, m);

	t = 0.0;
	x[0] = 1.0;
	x[1] = 2.0;
	c[0] = 0.5;
	c[1] = 1.0;

	sk_out_sfilt(d, t, 2, x, 2, c);

	ASSERT_NEAR( sk_out_mem_get_xs(m)[0], 3.0, 1e-10);
	ASSERT_NEAR( sk_out_mem_get_xs(m)[1], -1.0, 1e-10);
	ASSERT_NEAR( sk_out_mem_get_cs(m)[0], -0.5, 1e-10);
	ASSERT_NEAR( sk_out_mem_get_cs(m)[1], 1.5, 1e-10);

	sk_out_sfilt_free(d);
	sk_out_mem_free(m);
}
