/* Apache 2.0 INS-AMU 2015 */

#include <stdio.h>

#include "sk_test.h"
#include "sk_solv.h"
#include "sk_sys.h"
#include "sk_scheme.h"

typedef struct {
	int crossed;
	double tf;
	FILE *fd;
} out_data;

static SK_DEFOUT(test_out)
{
	out_data *d = data;
	fprintf(d->fd, "%f\t%f\t%f\n", t, x[0], x[1]);
	if (x[0] < 0.0)
		d->crossed = 1;
	return t < d->tf;
}

static void test_hist_filler()
{
}

int test_em_exc()
{
	double x[2];
	sk_sch_em_data schd;
	sk_sys_exc_dat sysd;
	out_data outd;
	struct sk_solv solv;

	x[0] = 1.010403;
	x[1] = 0.030870;

	/* init scheme & solver */
	sk_sch_em_init(&schd, 2);
	sk_solv_init(&solv, &sk_sys_exc, &sysd,
		&sk_sch_em, &schd, &test_out, &outd,
		&test_hist_filler, 42, 2, x, 0, NULL, NULL,
		0.0, 0.05);

	/* fill in data */
	outd.tf = 20.0;
	outd.fd = fopen("test_em_exc.dat", "w");
	sysd.a = 1.01;
	sysd.tau = 3.0;

	/* deterministic sub-thresh, no crossing */
	outd.crossed = 0;
	sysd.D = 0.0;
	sk_solv_cont(&solv);
	sk_test_true(!outd.crossed);

	/* stochastic sub-thresh, crossing */
	outd.crossed = 0;
	outd.tf = 40.0;
	sysd.D = 0.05;
	sk_solv_cont(&solv);
	sk_test_true(outd.crossed);

	sk_solv_free(&solv);
	sk_sch_em_free(&schd);
	fclose(outd.fd);

	return 0;
}
