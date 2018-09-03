/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

int main()
{
	struct tvb_sys_hmje *ep = tvb_sys_hmje_new();
	ep->set_x0(ep, -1.6);

	/* these couple state variables in network, so single node set to 0.0 */
	ep->set_Kf(ep, 0.0);
	ep->set_Ks(ep, 0.0);
	ep->set_Kvf(ep, 0.0);

	/* no noise this time */
	ep->set_D1(ep, 0.0);
	ep->set_D2(ep, 0.0);

	/* integration scheme */
	struct tvb_sch *heun = tvb_sch_new_heun(6);

	/* outputs */
	struct tvb_out_tee *tee = tvb_out_tee_new(2);
	struct tvb_out *tf = tvb_out_new_until(2e3);
	tee->set_out(tee, 0, tf);
	struct tvb_out_file *of = tvb_out_file_new_from_name("hmje-raw.txt");
	tee->set_out(tee, 1, TVB_AS(of, out));

	/* rng seed */
	uint32_t seed = 42;


	/* initial conditions and history t<0 */
	double init_cond[] = {0.005, 0.005, 4.005, 0.005, 0.005, 0.015}; 
	struct tvb_hfill *hf = tvb_hfill_new_val(0.0);

	/* number of delays should match model even if not used */
	uint32_t vi[] = {0, 0, 3};
	double vd[] = {0.0, 0.0, 0.0};

	/* solver */
	struct tvb_sol *sol = tvb_sol_new_default(TVB_AS(ep, sys), heun, TVB_AS(tee, out), hf, seed, 
			6, init_cond, 2, 3, vi, vd, 0.0, 0.05);

	/* run it */
	sol->cont(sol);

	/* clean up */
	ep->free(ep);
	heun->free(heun);
	TVB_CALL_AS_(tee, out, free);
	tf->free(tf);
	TVB_CALL_AS_(of, out, free);
	hf->free(hf);
	sol->free(sol);

	return 0;
}
