# copyright 2016 Apache 2 sddekit authors

from sddekit_h cimport *
from system cimport Sys

cdef class Net(Sys):
    "Base class for networks."
    def __cinit__(self):
        self._net = NULL

# vim: sw=4 et foldmethod=marker
