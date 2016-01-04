/* copyright 2016 Apache 2 sddekit authors */

#include <stdint.h>
#include <string.h>
#include "cb.h"
#include "util.h"

struct sd_sys_matlab_data { 
	uint64_t nc_out;
	mxArray *data; 
};

sd_sys_matlab_data *sd_sys_matlab_alloc()
{
	sd_sys_matlab_data *new, zero = {0};
	new = sd_malloc(sizeof(sd_sys_matlab_data));
	*new = zero;
	return new;
}

int sd_sys_matlab_init(sd_sys_matlab_data *d, int nc_out)
{
	d->nc_out = nc_out;
	return 0;
}

SK_DEFSYS(sd_sys_matlab)
{
	/* data hist t i nx x f g F G nc c Cf Cg */
	/* [f g c F G Cf Cg data] = sys(data, hist, t, i, x, c) */
	/* [f g c data] = sys(data, hist, t, i, x, c) */
	int nlhs;
	mxArray *plhs[8], *prhs[7];
	sd_sys_matlab_data *d;
	(void) G; (void) Cf; (void) Cg;
	d = data;
	nlhs = F==NULL ? 4 : 8;
	prhs[1] = d->data;
	prhs[0] = mxGetField(prhs[1], 0, "f");
	prhs[2] = obj_of_voidp(hist, "sd_hist");
	prhs[3] = mxCreateDoubleScalar(t);
	prhs[4] = mxCreateDoubleScalar(i);
	prhs[5] = mxCreateDoubleMatrix(nx, 1, mxREAL);
	memcpy(mxGetPr(prhs[5]), x, sizeof(double)*nx);
	prhs[6] = mxCreateDoubleMatrix(nc, 1, mxREAL);
	memcpy(mxGetPr(prhs[6]), c, sizeof(double)*nc);
	if (nlhs==8)
		sd_err("not implemented.");
	mexCallMATLAB(nlhs, plhs, 7, prhs, "feval");
	/* handle f & g */
	if (mxGetM(plhs[0]) != (size_t) nx)
		sd_err("size(f) must equal size(x) in system definition");
	if (mxGetM(plhs[1]) != (size_t) nx)
		sd_err("size(g) must equal size(x) in system definition");
	memcpy(f, mxGetPr(plhs[0]), sizeof(double) * nx);
	memcpy(g, mxGetPr(plhs[1]), sizeof(double) * nx);
	mxDestroyArray(plhs[0]);
	mxDestroyArray(plhs[1]);
	/* handle c. on entry, nc==nd, but on exit, it's whatever the
	 * system defines it to be, >= maxvi.
	 */
	if (mxGetM(plhs[2]) < (size_t) sd_hist_get_maxvi(hist))
		sd_err("out size(c) must be >= hist.maxvi.");
	memcpy(c, mxGetPr(plhs[2]), sizeof(double) * nc);
	d->data = plhs[3];
	mxDestroyArray(plhs[2]);
	return 0;
}

