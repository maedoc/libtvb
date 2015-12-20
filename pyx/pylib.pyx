cimport numpy as np
import numpy as np

cdef extern from "lib.h":
	ctypedef double(*cb)(void*, double)
	ctypedef void(*cb2)(void*, int, double*)
	double func(cb c, void* data, double x);
	void func2(cb2 c, void* data)

cdef double _cb(void *data, double x):
	return (<object> data)(x)

cdef void _cb2(void *data, int n, double *x):
	cdef np.float64_t[:] view = <np.float64_t[:n]> x
	(<object> data)(np.asarray(view))

def pyfunc(f, x):
	return func(_cb, <void*>f, x)

def pyfunc2(f):
	func2(_cb2, <void*> f)
