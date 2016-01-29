# copyright 2016 Apache 2 sddekit authors

from sddekit_h cimport *


cdef class Net(Sys):
    "Base class for networks."
    cdef sd_net *net
    def __init__(self):
        pass

# vim: sw=4 et foldmethod=marker
