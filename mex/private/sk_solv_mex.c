#include "matrix.h"
#include <stdlib.h>
#include "mex.h"
#include <string.h>

#include "sk_sys.h"

/* transfer functions */
void *voidp_of_mx(mxArray *pm) {
    union { long long ll; void *f; } u;
    u.ll = *((long long*) mxGetData(pm));
    return u.f;
}

void voidp_into_mx(void *f, mxArray *pm) {
    union { long long ll; void *f; } u;
    u.f = f;
    *((long long *) mxGetData(pm)) = u.ll;
}

mxArray *mx_of_voidp(void *f) {
    mxArray *pm;
    pm = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
    voidp_into_mx(f, pm);
    return pm;
}


typedef struct {
    char *function_name;
    void *user_data;
} sk_sys_mex_data;

mxArray *mx_from_vec(int n, double *x) {
	mxArray *pm;
	pm = mxCreateDoubleMatrix(0, 0, mxREAL);
	mxSetPr(pm, x);
	mxSetM(pm, n);
	mxSetN(pm, 1);
	return pm;
}

SK_DEFSYS(sk_sys_mex) {
	int nrhs, nlhs;
	sk_sys_mex_data *d;
	mxArray *prhs[7], *plhs[4];

	/* ftm, no hist or Jacobians */
	(void) hist; (void) Jf; (void) Jg; (void) Jce;

	nlhs = 4; /* user data, f, g, c */
	nrhs = 7; /* user data, t, i, x, f, g, c */
	d = data;

	prhs[0] = d->user_data;
	prhs[1] = mxCreateDoubleScalar(t);
	prhs[2] = mxCreateDoubleScalar(i);
	prhs[3] = mx_from_vec(nx, x);
	prhs[4] = mx_from_vec(nx, f);
	prhs[5] = mx_from_vec(nx, g);
	prhs[6] = mx_from_vec(nc, c);

	mexCallMATLAB(nlhs, plhs, nrhs, prhs, d->function_name);

	d->user_data = plhs[0];
	memcpy(x, mxGetPr(plhs[1]), sizeof(double) * nx);
	memcpy(f, mxGetPr(plhs[1]), sizeof(double) * nx);
	memcpy(g, mxGetPr(plhs[1]), sizeof(double) * nx);
	memcpy(c, mxGetPr(plhs[1]), sizeof(double) * nc);

	return 0;
}

void mexFunction() {
	/* TODO set mem allocators to mxCalloc mxFree etc. */
}
