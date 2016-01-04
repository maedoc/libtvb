/* copyright 2016 Apache 2 sddekit authors */

#include "matrix.h"
#include "mex.h"

mxArray *get_obj_meth_handle(mxArray *obj, char *meth);
void call_obj_meth(mxArray *obj, char *meth, int nlhs, mxArray **plhs, int nrhs, mxArray **prhs);
void *voidp_of_mx(mxArray *pm);
void voidp_into_mx(void *f, mxArray *pm);
mxArray *mx_of_voidp(void *f);
mxArray *obj_of_voidp(void *f, char *typename);
void *voidp_of_obj(mxArray *obj);
