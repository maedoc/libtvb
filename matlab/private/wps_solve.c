/* copyright 2016 Apache 2 sddekit authors */

#include "wps.h"

_(sd_solv, alloc, 
	sd_solv *solv = sd_solv_alloc();
	mexMakeMemoryPersistent(solv);
	pl[0] = mx_of_voidp(solv);
 )

_(sd_solv, init, 
	if (nr != 12)
		sd_err("requires 10 args (sys sch out hf seed x0 vi vd t0 dt)");
	/* TODO sys sch out hf: recognize if using C-implemented component
	 * and swap out callback and data. For now, consider exercise for binding. */
	sd_solv_init(voidp_of_mx(pr[1]), 
		sd_sys_matlab, pr[2], 
		sd_sch_matlab, pr[3], 
		sd_out_matlab, pr[4], 
		sd_hist_hfill_matlab, pr[5],
		mxGetScalar(pr[6]), mxGetM(pr[7]), mxGetPr(pr[7]),
		mxGetM(pr[8]), mxGetPr(pr[8]), mxGetPr(pr[9]),
		mxGetScalar(pr[10]), mxGetScalar(pr[11]));
 )

_(sd_solv, cont, sd_solv_cont(voidp_of_mx(pr[1]));)

_(sd_solv, get_nx, 
	pl[0] = mxCreateDoubleScalar(sd_solv_get_nx(voidp_of_mx(pr[1])));)

_(sd_solv, get_nc, 
	pl[0] = mxCreateDoubleScalar(sd_solv_get_nc(voidp_of_mx(pr[1])));)

_(sd_solv, get_t, 
	pl[0] = mxCreateDoubleScalar(sd_solv_get_t(voidp_of_mx(pr[1])));)

_(sd_solv, get_x, 
	sd_solv *sol = voidp_of_mx(pr[1]);
	pl[0] = mxCreateDoubleMatrix(sd_solv_get_nx(sol), 1, mxREAL);
	memcpy(mxGetPr(pl[0]), sd_solv_get_x(sol), sd_solv_get_nx(sol)*sizeof(double));
)

_(sd_solv, get_c, 
	sd_solv *sol = voidp_of_mx(pr[1]);
	pl[0] = mxCreateDoubleMatrix(sd_solv_get_nc(sol), 1, mxREAL);
	memcpy(mxGetPr(pl[0]), sd_solv_get_c(sol), sd_solv_get_nc(sol)*sizeof(double));
)

_(sd_solv, get_rng, 
	pl[0] = obj_of_voidp(sd_solv_get_rng(voidp_of_mx(pr[1])), "rk_state");)

_(sd_solv, get_hist, 
	pl[0] = obj_of_voidp(sd_solv_get_hist(voidp_of_mx(pr[1])), "sd_hist");)

_(sd_solv, free, sd_solv_free((sd_solv*) voidp_of_mx(pr[1]));)
