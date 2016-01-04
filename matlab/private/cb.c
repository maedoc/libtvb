/* copyright 2016 Apache 2 sddekit authors */

#include <stdint.h>
#include <string.h>
#include "cb.h"
#include "util.h"

/* TODO each of these has to become their own standard objects with inits, frees etc */


SK_DEFSCH(sd_sch_matlab)
{
	/* data hist rng sys sysd t dt nx x nc c */
	/* [x c sys data] = sch(data, hist, rng, sys, t, dt, x, c) */
	mxArray *plhs[4], *prhs[9];
	sd_sch_matlab_data *schs;
	sd_sys_matlab_data *syss;
	schs = data;
	syss = sysd;
	prhs[1] = schs->data;
	prhs[0] = mxGetField(prhs[1], 0, "f");
	prhs[2] = obj_of_voidp(hist, "sd_hist");
	prhs[3] = obj_of_voidp(rng, "rk_state");
	prhs[4] = syss->data;
	prhs[5] = mxCreateDoubleScalar(t);
	prhs[6] = mxCreateDoubleScalar(dt);
	prhs[7] = mxCreateDoubleMatrix(0, 1, mxREAL);
	mxSetPr(prhs[7], x);
	mxSetM(prhs[7], nx);
	prhs[8] = mxCreateDoubleMatrix(0, 1, mxREAL);
	mxSetPr(prhs[8], c);
	mxSetM(prhs[8], nc);
	mexCallMATLAB(4, plhs, 9, prhs, "feval");
	if (mxGetM(plhs[0]) != (size_t) nx)
		sd_err("size(x) should equal size(x) in system definition");
	if (mxGetM(plhs[1]) != (size_t) sd_hist_get_nd(hist))
		sd_err("output arg c should have as many elements as number of delays in system definition");
	memcpy(x, mxGetPr(plhs[0]), sizeof(double) * nx);	
	memcpy(c, mxGetPr(plhs[1]), sizeof(double) * sd_hist_get_nd(hist));	
	syss->data = plhs[2];
	schs->data = plhs[3];
	mxDestroyArray(plhs[0]);
       	mxDestroyArray(plhs[1]);
	return 0;
}

SK_DEFOUT(sd_out_matlab)
{
	/* data t nx x nc c */
	/* [continue, data] = out(data, t, x, c) */
	int cont;
	mxArray *plhs[2], *prhs[5];
	sd_out_matlab_data *d;
	d = data;
	prhs[1] = d->data;
	prhs[0] = mxGetField(prhs[1], 0, "f");
	prhs[2] = mxCreateDoubleScalar(t);
	prhs[3] = mxCreateDoubleMatrix(0, 1, mxREAL);
	mxSetPr(prhs[3], x);
	mxSetM(prhs[3], nx);
	prhs[4] = mxCreateDoubleMatrix(0, 1, mxREAL);
	mxSetPr(prhs[4], c);
	mxSetM(prhs[4], nc);
	mexCallMATLAB(2, plhs, 5, prhs, "feval");
	cont = mxGetScalar(plhs[0]);
	mxDestroyArray(plhs[0]);
	d->data = plhs[1];
	return cont;
}

SK_DEFHFILL(sd_hist_hfill_matlab)
{
	/* data n t indices buf */
	/* buf = hfill(data, t, i) */
	mxArray *plhs[1], *prhs[4];
	prhs[1] = data;
	prhs[0] = mxGetField(data, 0, "f");
	prhs[2] = mxCreateDoubleMatrix(n, 1, mxREAL);
	memcpy(mxGetPr(prhs[2]), t, n * sizeof(double));
	prhs[3] = mxCreateNumericMatrix(n, 1, mxUINT64_CLASS, mxREAL);
	{
		size_t i;
		uint64_t *ind = mxGetData(prhs[3]);
		for (i=0; i < (size_t) n; i++)
			ind[i] = indices[i] + 1;
	}
	mexCallMATLAB(1, plhs, 4, prhs, "feval");
	if (mxGetM(plhs[0]) != (size_t) n)
		sd_err("output arg buf should have same size as input arg t");
	memcpy(buf, mxGetPr(plhs[0]), n * sizeof(double));
	mxDestroyArray(plhs[0]);
	return 0;
}
