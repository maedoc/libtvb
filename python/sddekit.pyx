# copyright 2016 Apache 2 sddekit authors

from libc.stdlib cimport malloc, free
from libc.stdint cimport uint32_t
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

    ctypedef enum sd_stat:
        SD_OK
        SD_ERR
        SD_CONT
        SD_STOP

    ctypedef struct sd_hfill:
        void *ptr
        sd_stat (*apply)(sd_hfill*, uint32_t n, double * t, uint32_t *indices, double * buf)
        void (*free)(sd_hfill*)

    sd_hist * sd_hist_new_default(uint32_t nd, uint32_t *vi, double *vd, double t0, double dt)

    ctypedef struct sd_hist:
        uint32_t(*get_maxvi)(sd_hist*)
        uint32_t(*get_vi2i)(sd_hist*, uint32_t vi)
        uint32_t(*get_nu)(sd_hist *h)
        void (*free)(sd_hist *h)
        sd_stat (*fill)(sd_hist *h, sd_hfill *filler)
        void (*get)(sd_hist *h, double t, double *aff)
        void (*set)(sd_hist *h, double t, double *eff)
        uint32_t (*nbytes)(sd_hist *h)
        double (*get_buf_lin)(sd_hist *h, uint32_t index)
        uint32_t (*get_nd)(sd_hist *h)
        double (*get_t)(sd_hist *h)
        double (*get_dt)(sd_hist *h)
        uint32_t (*get_lim)(sd_hist *h, uint32_t i)
        uint32_t (*get_len)(sd_hist *h, uint32_t i)
        uint32_t (*get_pos)(sd_hist *h, uint32_t i)
        uint32_t (*get_uvi)(sd_hist *h, uint32_t i)
        double (*get_maxd)(sd_hist *h, uint32_t i)
        uint32_t (*get_vi)(sd_hist *h, uint32_t i)
        double (*get_vd)(sd_hist *h, uint32_t i)

ctypedef struct hfill_py:
    sd_hfill hf
    void *fn

cdef sd_stat hfill_py_apply(sd_hfill *hfill, uint32_t n, double * t, uint32_t *i, double * buf):
    cdef hfill_py *hp = <hfill_py*> hfill.ptr
    cdef np.ndarray[np.float64_t, ndim=1] np_buf
    t_ = np_of_ptr(n, t, np.NPY_DOUBLE, 0)
    i_ = np_of_ptr(n, t, np.NPY_UINT64, 0)
    try:
         np_buf = (<object> hp.fn)(t_, i_).astype(np.float64)
    except Exception as exc:
        print exc # TODO
        return SD_ERR
    for j in xrange(n):
        buf[j] = np_buf[j]
    return SD_OK

cdef void hfill_py_free(sd_hfill *h):
    free(h)

cdef sd_hfill * hfill_py_new(object fn):
    cdef hfill_py *h = <hfill_py *> malloc(sizeof(hfill_py))
    if h==NULL:
        raise Exception('alloc hfill_py failed.')
    h.fn = <void*> fn
    h.hf.ptr = h
    h.hf.apply = &hfill_py_apply
    h.hf.free = &hfill_py_free
    return &(h.hf)

cdef class Hist(object):
    cdef sd_hist *h
    def __init__(self, 
            np.ndarray[uint32_t, ndim=1, mode="c"] vi not None, 
            np.ndarray[double, ndim=1, mode="c"] vd not None, double t0, double dt):
        self.h = sd_hist_new_default(vi.size, <uint32_t*> vi.data, <double*> vd.data, np.float64(t0), np.float64(dt))
    def __del__(self):
        if self.h != NULL:
            self.h.free(self.h)
    def fill(self, filler):
        cdef sd_hfill *hf = hfill_py_new(filler)
        cdef sd_stat stat = self.h.fill(self.h, hf)
        hf.free(hf)
        if stat == SD_ERR:
            raise Exception('fill failed.')
    def get(self, double t):
        cdef np.ndarray[double, ndim=1] aff = np.empty((self.nd(),), np.float64)
        self.h.get(self.h, t, <double*> aff.data)
        return aff
    def set(self, double t, np.ndarray[double, ndim=1] eff):
        # void sd_hist_set(sd_hist *  h, double t, double *  eff)
        self.h.set(self.h, t, <double*> eff.data)
    def maxvi(self):
        return self.h.get_maxvi(self.h)
    def nu(self):
        return self.h.get_nu(self.h)
    def nd(self):
        return self.h.get_nd(self.h)
    def t(self):
        return self.h.get_t(self.h)
    def dt(self):
        return self.h.get_dt(self.h)
    def vi2i(self, i):
        return self.h.get_vi2i(self.h, i)
    def buf_lin(self, i):
        return self.h.get_buf_lin(self.h, i)
    def lim(self, i):
        return self.h.get_lim(self.h, i)
    def len(self, i):
        return self.h.get_len(self.h, i)
    def pos(self, i):
        return self.h.get_pos(self.h, i)
    def uvi(self, i):
        return self.h.get_uvi(self.h, i)
    def maxd(self, i):
        return self.h.get_maxd(self.h, i)
    def vi(self, i):
        return self.h.get_vi(self.h, i)
    def vd(self, i):
        return self.h.get_vd(self.h, i)
