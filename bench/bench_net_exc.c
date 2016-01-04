/* copyright 2016 Apache 2 sddekit authors */
#include <stdlib.h>
#include <stdio.h>

#include "sddekit.h"

typedef struct { sd_out *out; } outd;

static sd_stat out_igc(void *data, double t, 
			     uint32_t nx, double * restrict x,
			     uint32_t nc, double * restrict c)
{
	(void) nc; (void) c;
	outd *d = data;
	return (d->out)->apply(d->out, t, nx, x, 0, NULL);
}

int main() {
	uint32_t i, n, nnz, *Or, *Ic;
	double *w, *d, *sw, *sd, *x0;

	/* set up outputs
	 *
	 * sol -> igc -> tee -> tavg -> out file
	 *                   \> until t = 1e3
	 */
	sd_out_file *of = sd_out_file_new_from_name("bench_net_exc.dat");
	sd_out_tavg *tavg = sd_out_tavg_new(20, SD_AS(of, out));
	sd_out *until = sd_out_new_until(1e3);
	sd_out_tee *tee = sd_out_tee_new(2);
	tee->set_out(tee, 0, until);
	tee->set_out(tee, 1, SD_AS(tavg, out));
	outd igcd = { .out = SD_AS(tee, out) };
	sd_out *out = sd_out_new_cb(&igcd, &out_igc);

	/* connectivity, assuming conduction velocity of 1.0 */
	sd_util_read_square_matrix("res/conn76/weights.txt", &n, &w);
	sd_util_read_square_matrix("res/conn76/tract_lengths.txt", &n, &d);
	sd_sparse_from_dense(n, n, w, d, 0.0, &nnz, &Or, &Ic, &sw, &sd);
	fprintf(stdout, "[bench_net_exc] nnz=%d\n", nnz);

	/* setup model */
	sd_sys_exc *exc = sd_sys_exc_new();
	exc->set_a(exc, 1.01);
	exc->set_tau(exc, 3.0);
	exc->set_D(exc, 0.01);
	exc->set_k(exc, 0.001);
	sd_net *net = sd_net_new_hom(n, SD_AS(exc, sys), 2, 1, 1, nnz, Or, Ic, w, d);

	/* setup scheme & solver */
	x0 = sd_malloc(sizeof(double)*2*n);
	for (i=0; i<(2*n); i++)
		x0[i] = 0.0;
	sd_sch *heun = sd_sch_new_heun(2*n);
	sd_hfill *hf = sd_hfill_new_val(0.0);
	sd_sol *sol = sd_sol_new_default(SD_AS(net, sys), heun, out, hf,
			42, 2*n, x0, n, nnz, Ic, sd, 0.0, 0.01);

	/* solve */
	sol->cont(sol);

	/* clean up */
	sd_free(w);
	sd_free(x0);
	sd_free(d);
	sd_free(Or);
	sd_free(Ic);
	sd_free(sw);
	sd_free(sd);

	return 0;
}
