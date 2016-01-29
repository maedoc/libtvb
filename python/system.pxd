from sddekit_h cimport sd_sys

cdef class Sys(object):
    cdef sd_sys *_sys

