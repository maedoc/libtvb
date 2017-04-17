#include "matrix.h"
#include <stdlib.h>
#include "mex.h"

#include "foo_.h"

typedef struct foo {
    int iters;
} foo;

foo *foo_new() {
    mexPrintf("allocating a new foo..\n");
    foo *f = mxMalloc(sizeof(foo));
    if (f==NULL) {
        mexPrintf("[foo_new] failed to mxAlloc!\n");
        return NULL;
    }
    mexMakeMemoryPersistent(f);
    f->iters = 0;
    return f;
}

void foo_del(foo *f) {
    mexPrintf("deleting a foo..\n");
    mxFree(f);
}    

int foo_get_iters(foo *f) {
    /*mexPrintf("get iters on a foo..\n");*/
    return f->iters;
}

void foo_set_iters(foo *f, int iters) {
    /*mexPrintf("set iters on a foo..\n");*/
    f->iters = iters;
}

void foo_manip_iters(foo *f, foo_iters_manip cb, void *data) {
    f->iters = (*cb)(data, f->iters);
}

void foo_manip_array(foo *f, foo_array_manip cb, void *data) {
	int i;
	double *x = mxMalloc(sizeof(double)*5);
	for (i=0; i<5; i++) {
		x[i] = (i+1.2) * 2.1;
	}
	(*cb)(data, 5, x);
	f->iters++;
}

