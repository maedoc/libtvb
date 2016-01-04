# copyright 2016 Apache 2 sddekit authors

from libc.stdlib cimport free
from cpython cimport PyObject, Py_INCREF
cimport numpy as np
import numpy as np
np.import_array()

# based on https://gist.github.com/GaelVaroquaux/1249305 BSD-licensed.
cdef class CArrayWrapper:
    "Python wrapper for C array."

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

cdef extern from "sddekit.h":
    ctypedef struct sd_hist:
        pass
    ctypedef int(*sd_hist_filler)(void*, int, double*, int*, double*)
    sd_hist *sd_hist_alloc()
    void sd_hist_free(sd_hist *h)
    int sd_hist_init(sd_hist *  h, int nd, int *  vi, double *  vd, double t0, double dt)
    int sd_hist_fill(sd_hist *  h, sd_hist_filler filler, void *  fill_data)
    void sd_hist_get(sd_hist *  h, double t, double *  aff)
    void sd_hist_set(sd_hist *  h, double t, double *  eff)
    int sd_hist_get_maxvi(sd_hist *h)
    int sd_hist_get_nu(sd_hist *h)
    int sd_hist_get_nd(sd_hist *h)
    double sd_hist_get_t(sd_hist *h)
    double sd_hist_get_dt(sd_hist *h)
    int sd_hist_get_vi2i(sd_hist *h, int vi)
    double sd_hist_get_buf_lin(sd_hist *h, int index)
    int sd_hist_get_lim(sd_hist *h, int i)
    int sd_hist_get_len(sd_hist *h, int i)
    int sd_hist_get_pos(sd_hist *h, int i)
    int sd_hist_get_uvi(sd_hist *h, int i)
    double sd_hist_get_maxd(sd_hist *h, int i)
    int sd_hist_get_vi(sd_hist *h, int i)
    double sd_hist_get_vd(sd_hist *h, int i)

cdef int sd_hist_hfill_py(void *data, int n, double *t, int *i, double *buf):
    cdef np.ndarray[np.float64_t, ndim=1] np_buf
    t_ = np_of_ptr(n, t, np.NPY_DOUBLE, 0)
    i_ = np_of_ptr(n, t, np.NPY_INT, 0)
    try:
         np_buf = (<object> data)(t_, i_).astype(np.float64)
    except Exception as exc:
        print exc # TODO
        return 1
    for j in xrange(n):
        buf[j] = np_buf[j]
    return 0

cdef class Hist(object):
    cdef sd_hist *ptr
    def __init__(self, 
            np.ndarray[int, ndim=1, mode="c"] vi not None, 
            np.ndarray[double, ndim=1, mode="c"] vd not None, double t0, double dt):
        self.ptr = sd_hist_alloc()
        sd_hist_init(self.ptr, vi.size, <int*> vi.data, <double*> vd.data, np.float64(t0), np.float64(dt))
    def __del__(self):
        if self.ptr != NULL:
            sd_hist_free(self.ptr)
    def fill(self, filler):
        sd_hist_fill(self.ptr, sd_hist_hfill_py, <void*> filler)
    def get(self, double t):
        cdef np.ndarray[double, ndim=1] aff = np.empty((self.nd(),), np.float64)
        sd_hist_get(self.ptr, t, <double*> aff.data)
        return aff
    def set(self, double t, np.ndarray[double, ndim=1] eff):
        # void sd_hist_set(sd_hist *  h, double t, double *  eff)
        sd_hist_set(self.ptr, t, <double*> eff.data)
    def maxvi(self):
        return sd_hist_get_maxvi(self.ptr)
    def nu(self):
        return sd_hist_get_nu(self.ptr)
    def nd(self):
        return sd_hist_get_nd(self.ptr)
    def t(self):
        return sd_hist_get_t(self.ptr)
    def dt(self):
        return sd_hist_get_dt(self.ptr)
    def vi2i(self, i):
        return sd_hist_get_vi2i(self.ptr, i)
    def buf_lin(self, i):
        return sd_hist_get_buf_lin(self.ptr, i)
    def lim(self, i):
        return sd_hist_get_lim(self.ptr, i)
    def len(self, i):
        return sd_hist_get_len(self.ptr, i)
    def pos(self, i):
        return sd_hist_get_pos(self.ptr, i)
    def uvi(self, i):
        return sd_hist_get_uvi(self.ptr, i)
    def maxd(self, i):
        return sd_hist_get_maxd(self.ptr, i)
    def vi(self, i):
        return sd_hist_get_vi(self.ptr, i)
    def vd(self, i):
        return sd_hist_get_vd(self.ptr, i)
