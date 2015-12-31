/* copyright 2016 Apache 2 sddekit authors */

#include <stdio.h>

#include "sddekit.h"

typedef struct {
	int crossed;
	double tf;
	FILE *fd;
} out_data;

static SK_DEFOUT(test_out)
{
	out_data *d = (out_data*) data;
	(void) nx; (void) nc; (void) c; /* unused */
	fprintf(d->fd, "%f\t%f\t%f\n", t, x[0], x[1]);
	if (x[0] < 0.0)
		d->crossed = 1;
	return t < d->tf;
}

static double x0[2] = {1.010403, 0.030870};

static int for_scheme(sk_sch sch, void *schd, char *name)
{
	sk_sys_exc_dat *sysd;
	out_data outd;
	sk_solv *solv;
	char dat_name[100];
	int vi[1];
	double vd[1];

	/* init solver */
	vi[0] = 0;
	vd[0] = 25.0;
	sysd = sk_sys_exc_alloc();
	solv = sk_solv_alloc();
	sk_solv_init(solv, &sk_sys_exc, sysd,
		sch, schd, &test_out, &outd,
		&sk_hist_zero_filler, NULL,
		42, 2, x0, 1, vi, vd,
		0.0, 0.05);

	/* fill in data */
	outd.tf = 20.0;
	sprintf(dat_name, "test_exc_%s.dat", name);
	outd.fd = fopen(dat_name, "w");
	sk_sys_exc_set_a(sysd, 1.01);
	sk_sys_exc_set_tau(sysd, 3.0);
	sk_sys_exc_set_k(sysd, -1e-3);

	/* deterministic sub-thresh, no crossing */
	outd.crossed = 0;
	sk_sys_exc_set_D(sysd, 0.0);
	sk_solv_cont(solv);
	EXPECT_TRUE(!outd.crossed);

	/* stochastic sub-thresh, crossing */
	outd.crossed = 0;
	outd.tf = 40.0;
	sk_sys_exc_set_D(sysd, 0.05);
	sk_solv_cont(solv);
	EXPECT_TRUE(outd.crossed);

	/* clean up */
	fclose(outd.fd);
	sk_sys_exc_free(sysd);
	sk_solv_free(solv);

	return 0;
}


TEST(exc, em) {
	sk_sch_em_data *emd;
	emd = sk_sch_em_alloc();
	sk_sch_em_init(emd, 2);
	for_scheme(sk_sch_em, emd, "em");
	sk_sch_em_free(emd);
}
	
TEST(exc, heun){
	sk_sch_heun_data *heund;
	heund = sk_sch_heun_alloc();
	sk_sch_heun_init(heund, 2);
	for_scheme(sk_sch_heun, heund, "heun");
	sk_sch_heun_free(heund);
}

TEST(exc, emcolor){
	sk_sch_emcolor_data *emcolord;
	emcolord = sk_sch_emcolor_alloc();
	sk_sch_emcolor_init(emcolord, 2, 1.0);
	for_scheme(sk_sch_emcolor, emcolord, "emcolor");
	sk_sch_emcolor_free(emcolord);
}
