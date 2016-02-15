/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include <time.h>

/* output graph {{{
 *
 * raw -> ignore c -> lfp tavg -> tee -> file
 * 			   	      \> tavg -> conv -> file
 * 				      \> until
 */
struct sd_out *o_ign, *o_tf;
struct sd_out_file *of_lfp, *of_bold;
struct sd_out_tavg *ot_lfp, *ot_bold;
struct sd_out_tee *o_tee;
struct sd_out_conv *oc_bold;

void out_done()
{
	uint32_t i;
	sd_out *outs[8] = {o_ign, o_tf, SD_AS(of_lfp, out),
		SD_AS(of_bold, out), SD_AS(ot_lfp, out),
		SD_AS(ot_bold, out), SD_AS(o_tee, out),
		SD_AS(oc_bold, out)};
	for (i=0; i<8; i++)
		outs[i]->free(outs[i]);
}

void out_init(double dt, double tf, char *lfp_fname, char *bold_fname)
{
	uint32_t hrf_len=60;
	double hrf_coef[60], hrf_dt = 500.0, lfp_dt=5.0;

	o_tee = sd_out_tee_new(3);

	/* stop on time limit */
	o_tee->set_out(o_tee, 0, o_tf = sd_out_new_until(tf));

	/* save lfp to file */
	of_lfp = sd_out_file_new_from_name(lfp_fname);
	o_tee->set_out(o_tee, 1, SD_AS(of_lfp, out));

	/* BOLD o_tee -> ot_bold -> oc_bold -> of_bold */
	of_bold = sd_out_file_new_from_name(bold_fname);
	sd_hrf_volt1(hrf_len, hrf_dt, hrf_coef);
	oc_bold = sd_out_conv_new(hrf_len, hrf_coef, SD_AS(of_bold, out));
	ot_bold = sd_out_tavg_new((uint32_t) (hrf_dt / lfp_dt), SD_AS(oc_bold, out));
	o_tee->set_out(o_tee, 2, SD_AS(ot_bold, out));

	/* feed tee with lfp tavg */
	ot_lfp = sd_out_tavg_new((uint32_t) (lfp_dt / dt), SD_AS(o_tee, out));

	o_ign = sd_out_new_ign(false, true, SD_AS(ot_lfp, out));
}

/* output graph }}} */

int main(int argc, char *argv[])
{
	(void) argc; (void) argv;

	/* defaults, can read from args if required */
	double dt=0.1, tf=1e3;
	char *lfp_fname="lfp.txt", *bold_fname="bold.txt",
	     *w_fname="weights.txt";

	/* setup output, use o_ign */
	out_init(dt, tf, lfp_fname, bold_fname);

	/* setup connectivity */
	uint32_t n_node, nz_conn_weights, *row_offsets, *col_indices;
	double *conn_weights, *conn_weights_sparse, *delays;
	sd_util_read_square_matrix(w_fname, &n_node, &conn_weights);
	sd_sparse_from_dense(n_node, n_node, conn_weights, NULL, 0.0,
		&nz_conn_weights, &row_offsets, &col_indices, &conn_weights_sparse, NULL);
	delays = sd_malloc(sizeof(double) * nz_conn_weights);
	for (uint32_t i=0; i<nz_conn_weights; i++)
		delays[i] = 0.0;


	/* setup model */
	struct sd_sys_rww *rww = sd_sys_rww_new();
	struct sd_net *net = sd_net_new_hom(n_node, SD_AS(rww, sys), 1, 1, 1,
		nz_conn_weights, row_offsets, col_indices, conn_weights_sparse, delays);


	/* setup soln */
	struct sd_rng *rng = sd_rng_new_default();
	double *r0 = sd_malloc(sizeof(double)*n_node);
	for (uint32_t i=0; i<n_node; i++)
		r0[i] = rng->uniform(rng);
	sd_sch *eul = sd_sch_new_em(n_node);
	sd_hfill *hf = sd_hfill_new_val(0.0);
	sd_sol *sol = sd_sol_new_default(SD_AS(net, sys), eul, o_ign, hf,
		42, n_node, r0, n_node, nz_conn_weights, col_indices,
	       	conn_weights_sparse, 0.0, dt);

	/* solve */
	sol->cont(sol);

	/* clean up TODO */

	out_done();
	return 0;
}

/* vim: foldmethod=marker
 */
