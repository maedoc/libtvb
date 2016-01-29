from libc.stdlib cimport malloc, free
from libc.stdint cimport uint32_t
from cpython cimport PyObject, Py_INCREF, Py_DECREF
cimport numpy as np

cdef extern np.ndarray np_of_ptr(int size, void *ptr, int typenum, int free_on_gc)
