/* copyright 2016 Apache 2 sddekit authors */

#include <string.h>
#include "sd_err.h"
#include "util.h"

mxArray *get_obj_meth_handle(mxArray *obj, char *meth)
{
	mxArray *plhs[1], *prhs[2];
	prhs[0] = obj;
	prhs[1] = mxCreateString(meth);
	mexCallMATLAB(1, plhs, 2, prhs, "sd_obj_meth");
	mxDestroyArray(prhs[1]);
	return plhs[0];
}

void call_obj_meth(mxArray *obj, char *meth, int nlhs, mxArray **plhs, int nrhs, mxArray **prhs)
{
	int nrhs_;
	mxArray *prhs_[50];
	nrhs_ = nrhs + 1;
	memcpy(prhs_ + 1, prhs, nrhs * sizeof(mxArray*));
	prhs_[0] = get_obj_meth_handle(obj, meth);
	mexCallMATLAB(nlhs, plhs, nrhs_, prhs_, "feval");
}

void *voidp_of_mx(mxArray *pm) {
	union { long long ll; void *f; } u;
	if (pm==NULL)
		sd_err("NULL pointer.");
	u.ll = *((long long*) mxGetData(pm));
	return u.f;
}

void voidp_into_mx(void *f, mxArray *pm) {
	union { long long ll; void *f; } u;
	if (f==NULL)
		sd_err("NULL pointer f.");
	if (pm==NULL)
		sd_err("NULL pointer pm.");
	u.f = f;
	*((long long *) mxGetData(pm)) = u.ll;
}

mxArray *mx_of_voidp(void *f) {
	mxArray *pm;
	if (f==NULL)
		sd_err("NULL pointer.");
	pm = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
	voidp_into_mx(f, pm);
	return pm;
}

mxArray *obj_of_voidp(void *f, char *typename)
{
	mxArray *plhs[1], *prhs[1];
	prhs[0] = mx_of_voidp(f);
	mexCallMATLAB(1, plhs, 1, prhs, typename);
	return plhs[0];
}

void *voidp_of_obj(mxArray *obj)
{
	mxArray *ptr;
	void *ret;
	call_obj_meth(obj, "get_ptr", 1, &ptr, 0, NULL);
	ret = voidp_of_mx(ptr);
	mxDestroyArray(ptr);
	return ret;
}
