# copyright 2016 Apache 2 sddekit authors

from sddekit_h cimport *
from sddekit cimport *
import numpy as np

cdef class Hist(object):
    cdef sd_hist *h

    def __init__(self, 
            np.ndarray[uint32_t, ndim=1, mode="c"] vi not None, 
            np.ndarray[double, ndim=1, mode="c"] vd not None, double t0, double dt):
        self.h = sd_hist_new_default(vi.size, 
                <uint32_t*> vi.data, 
                <double*> vd.data, 
                np.float64(t0), 
                np.float64(dt))

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
