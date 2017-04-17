#include "matrix.h"
#include <stdlib.h>
#include "mex.h"
#include <string.h>

#include "foo_.h"

typedef struct {
    char *functionName;
    void *user_data;
} mex_foo_manip_iters_cb_data;

int mex_foo_manip_iters_cb(void *data, int iters) {
    int nrhs=2, nlhs=1, out;
    mxArray *prhs[2], *plhs[1];
    mex_foo_manip_iters_cb_data *d = data;
    prhs[0] = d->user_data;
    prhs[1] = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
    *((long long*) mxGetData(prhs[1])) = iters;
    mexCallMATLAB(nlhs, plhs, nrhs, prhs, d->functionName);
    out = mxGetScalar(plhs[0]);
    return out;
}

typedef struct {
    char *functionName;
    void *user_data;
} mex_foo_manip_array_cb_data;

void mex_foo_manip_array_cb(void *data, int n, double *x) {
    int nrhs=2, nlhs=1;
    mxArray *prhs[2], *plhs[1];
    mex_foo_manip_iters_cb_data *d = data;
    prhs[0] = d->user_data;
    prhs[1] = mxCreateDoubleMatrix(0, 0, mxREAL);
    mxSetPr(prhs[1], x);
    mxSetM(prhs[1], n);
    mxSetN(prhs[1], 1);
    mexCallMATLAB(nlhs, plhs, nrhs, prhs, d->functionName);
    memcpy(x, mxGetPr(plhs[0]), sizeof(double)*n);
}

/* probably these could be generic for void* */
foo *foo_of_mx(mxArray *pm) {
    union { long long ll; foo *f; } u;
    u.ll = *((long long*) mxGetData(pm));
    return u.f;
}

void foo_into_mx(foo *f, mxArray *pm) {
    union { long long ll; foo *f; } u;
    u.f = f;
    *((long long *) mxGetData(pm)) = u.ll;
}
    

mxArray *mx_of_foo(foo *f) {
    mxArray *pm;
    pm = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
    foo_into_mx(f, pm);
    return pm;
}
    

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char msg[20];
    if (nrhs<1 || (!mxIsChar(prhs[0]))) {
        mexErrMsgTxt("at least one string argument required");
    }
    mxGetString(prhs[0], msg, 20);
    
    /* to avoid so many string comparisons, we could pass msg as a two
     * char, first for the type, second for method?
     */
    if (!strcmp(msg, "new"))  {
        if (nlhs!=1)
            mexErrMsgTxt("cannot return new instance if no output arguments!");
        plhs[0] = mx_of_foo(foo_new());
        
    } else if (!strcmp(msg, "del")) {
        if (nrhs<2)
            mexErrMsgTxt("require at least one argument to del msg");
        foo_del(foo_of_mx(prhs[1]));
        
    } else if (!strcmp(msg, "get_iters")) {
        double iters;
        if (nrhs<2)
            mexErrMsgTxt("require one input and one output");
        plhs[0] = mxCreateDoubleScalar(foo_get_iters(foo_of_mx(prhs[1])));
        
    } else if (!strcmp(msg, "set_iters")) {
        if (nrhs<3)
            mexErrMsgTxt("require two inputs");
        foo_set_iters(foo_of_mx(prhs[1]), mxGetScalar(prhs[2]));
        
    } else if (!strcmp(msg, "manip_iters")) {
        char fname[255];
        mex_foo_manip_iters_cb_data cbd;
        if (nrhs<4)
            mexErrMsgTxt("requires three inputs");
        mxGetString(prhs[2], fname, 255);
        cbd.functionName = fname;
        cbd.user_data = prhs[3];
        foo_manip_iters(foo_of_mx(prhs[1]), &mex_foo_manip_iters_cb, &cbd);

    } else if (!strcmp(msg, "manip_array")) {
        char fname[255];
        mex_foo_manip_array_cb_data cbd;
        if (nrhs<4)
            mexErrMsgTxt("requires three inputs");
        mxGetString(prhs[2], fname, 255);
        cbd.functionName = fname;
        cbd.user_data = prhs[3];
        foo_manip_array(foo_of_mx(prhs[1]), &mex_foo_manip_array_cb, &cbd);
    } else {
        mexErrMsgTxt("unknown msg");
    }
}
