# copyright 2016 Apache 2 sddekit authors

from sddekit_h cimport *


cdef class Rng(object):
    cdef sd_rng *r

cdef object rng_of_ptr(sd_rng *r):
    rng = Rng()
    rng.r = r
    return rng
