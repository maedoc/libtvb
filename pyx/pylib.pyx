# https://gist.github.com/GaelVaroquaux/1249305
from libc.stdlib cimport free
from cpython cimport PyObject, Py_INCREF
cimport numpy as np
import numpy as np
np.import_array()

cdef class cdvec:
	cdef void* ptr
	cdef int size
	cdef int dealloc
	cdef init(self, int size, void *ptr, int dealloc=0):
		self.ptr = ptr
		self.size = size
		self.dealloc = dealloc
	def __array__(self):
		# used by numpy to obtain array from this object
		cdef np.npy_intp shape[1]
		shape[0] = <np.npy_intp> self.size
		return np.PyArray_SimpleNewFromData(1, shape, np.NPY_DOUBLE, self.ptr)
	def __dealloc__(self):
		if self.dealloc:
			free(<void*>self.ptr)
			print 'memory dealloced'
		else:
			print 'not deallocating memory'

cdef extern from "lib.h":
	ctypedef double(*cb)(void*, double)
	ctypedef void(*cb2)(void*, int, double*)
	double func(cb c, void* data, double x)
	void func2(cb2 c, void* data)

cdef double _cb(void *data, double x):
	return (<object> data)(x)

cdef void _cb2(void *data, int n, double *x):
	cdef np.ndarray nda
	vec = cdvec()
	vec.init(n, <void*> x)
	nda = np.array(vec, copy=False)
	nda.base = <PyObject*> vec
	Py_INCREF(vec)
	(<object> data)(nda)

def pyfunc(f, x):
	return func(_cb, <void*>f, x)

def pyfunc2(f):
	func2(_cb2, <void*> f)
