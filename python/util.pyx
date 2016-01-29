# copyright 2016 Apache 2 sddekit authors

from util cimport *
import numpy as np

# TODO only need once per extension module, right?
np.import_array()

cdef class CArrayWrapper:
    "Python wrapper for C array."

    # https://gist.github.com/GaelVaroquaux/1249305 BSD-licensed.

    cdef void* ptr
    cdef int size
    cdef int typenum
    cdef int free_on_gc

    cdef init(self, int size, void *ptr, int typenum, int free_on_gc=0):
        "Initialize wrapper."
        self.ptr = ptr
        self.size = size
        self.typenum = typenum
        self.free_on_gc = free_on_gc

    def __array__(self):
        "Obtain NumPy array from self."
        cdef np.npy_intp shape[1]
        shape[0] = <np.npy_intp> self.size
        return np.PyArray_SimpleNewFromData(1, shape, self.typenum, self.ptr)

    def __dealloc__(self):
        "Deallocate C array on Python garbage collect."
        if self.free_on_gc:
            free(<void*> self.ptr)


cdef np.ndarray np_of_ptr(int size, void *ptr, int typenum, int free_on_gc):
    "Wrap a given C array, returning a NumPy array."
    cdef np.ndarray ndarray
    wrapper = CArrayWrapper()
    wrapper.init(size, ptr, typenum, free_on_gc=free_on_gc)
    ndarray = np.array(wrapper, copy=False)
    ndarray.base = <PyObject*> wrapper
    Py_INCREF(wrapper)
    return ndarray
