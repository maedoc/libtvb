/* Apache 2.0 INS-AMU 2015 */
#include <stdlib.h>
#include <stdio.h>

#include "sk_solv.h"
#include "sk_sys.h"
#include "sk_scheme.h"
#include "sk_dat.h"
#include "sk_out.h"
#include "sk_sparse.h"
#include "sk_net.h"

typedef struct { sk_out out; void *outd; } bench_out_ignore_c_data;

SK_DEFOUT(bench_out_ignore_c) {
	bench_out_ignore_c_data *d = data;
	(void) nx; (void) nc; (void) c; /* unused */
	return (*(d->out))(d->outd, t, nx, x, 0, NULL);
}

typedef struct { double tf; } bench_out_stop_data;

SK_DEFOUT(bench_out_stop)
{
	bench_out_stop_data *d = data;
	(void) x; (void) nx; (void) nc; (void) c; /* unused */
	return t < d->tf;
}

int main() {
	int i, n, nnz, *Or, *Ic;
	double *w, *d, *sw, *sd, *x0;
	sk_out_tavg_data tavgd;
	sk_out_file_data filed;
	bench_out_stop_data stopd;
	sk_out_tee_data teed;
	sk_sys_exc_dat excd;
	sk_solv solv;
	sk_sch_heun_data heund;
	bench_out_ignore_c_data igncd;
	sk_net_data netd;


	/* connectivity, assuming conduction velocity of 1.0 */
	sk_dat_read_square_matrix("../../res/conn76/weights.txt", &n, &w);
	sk_dat_read_square_matrix("../../res/conn76/tract_lengths.txt", &n, &d);
	sk_sparse_from_dense(n, n, w, d, 0.0, &nnz, &Or, &Ic, &sw, &sd);
	fprintf(stdout, "[bench_net_exc] nnz=%d\n", nnz);


	/* monitor to file */
	stopd.tf = 1e3;
	sk_out_file_from_fname(&filed, "bench_net_exc.dat");
	sk_out_tavg_init(&tavgd, 20, sk_out_file, &filed);
	sk_out_tee_init(&teed, 2);
	sk_out_tee_set_out(&teed, 0, bench_out_stop, &stopd);
	sk_out_tee_set_out(&teed, 1, sk_out_tavg, &tavgd);
	igncd.out = sk_out_tee;
	igncd.outd = &teed;

	/* setup model */
	excd.a = 1.01;
	excd.tau = 3.0;
	excd.D = 0.01;
	excd.k = 0.001;
	sk_net_init1(&netd, n, sk_sys_exc, &excd, 2, 1, nnz, Or, Ic, w, d);

	/* setup scheme & solver */
	x0 = malloc (sizeof(double)*2*n);
	for (i=0; i<(2*n); i++)
		x0[i] = 0.0;
	sk_sch_heun_init(&heund, 2*n);
	sk_solv_init(&solv, &sk_net_sys, &netd, sk_sch_heun, &heund,
			bench_out_ignore_c, &igncd, sk_hist_zero_filler, NULL,
			42, 2*n, x0, nnz, Ic, sd, 0.0, 0.01);

	/* solve */
	sk_solv_cont(&solv);

	/* clean up */
	free(w);
	free(x0);
	free(d);
	free(Or);
	free(Ic);
	free(sw);
	free(sd);
	sk_out_file_free(&filed);
	sk_out_tavg_free(&tavgd);
	sk_out_tee_free(&teed);
	sk_solv_free(&solv);

	return 0.0;
}
