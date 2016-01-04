/* copyright 2016 Apache 2 sddekit authors */

#include "wps.h"

_(sd_sch_em, alloc,
	sd_sch_em_data *sch = sd_sch_em_alloc();
	mexMakeMemoryPersistent(sch);
	pl[0] = mx_of_voidp(sch);
)

_(sd_sch_em, init, sd_sch_em_init(voidp_of_mx(pr[0]),mxGetScalar(pr[1])); )

_(sd_sch_em, get_nx, 
        pl[0] = mxCreateDoubleScalar(sd_sch_em_get_nx(voidp_of_mx(pr[0])));)

/* [x c sys data] = sch(data, hist, rng, sys, t, dt, x) */
_(sd_sch_em, apply,
	int nx, nc;
	double *x, *c;
	sd_sys_matlab_data sysd;
	sd_sch_em_data *sch = voidp_of_mx(pr[0]);
	sd_hist *hist = voidp_of_obj(pr[1]);
	rk_state *rng = voidp_of_obj(pr[2]);
	sysd.data = pr[3];
	nx = mxGetM(pr[6]);
	nc = mxGetM(pr[7]);
	x = sd_malloc(sizeof(double) * nx);
	c = sd_malloc(sizeof(double) * sd_hist_get_nd(hist));
	memcpy(x, mxGetPr(pr[6]), nx * sizeof(double));
	sd_sch_em(sch, hist, rng, sd_sys_matlab, &sysd, 
		mxGetScalar(pr[4]), mxGetScalar(pr[5]),
		nx, x, nc, c);
	pl[0] = mxCreateDoubleMatrix(0, 1, mxREAL);
	mxSetM(pl[0], nx);
	mxSetPr(pl[0], x);
	pl[1] = mxCreateDoubleMatrix(0, 1, mxREAL);
	mxSetM(pl[1], sd_hist_get_nd(hist));
	mxSetPr(pl[1], c);
	pl[2] = sysd.data;
)

_(sd_sch_em, free, sd_sch_em_free(voidp_of_mx(pr[0])); )
