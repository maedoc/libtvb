from sddekit_h cimport sd_net
from system cimport Sys

cdef class Net(Sys):
    cdef sd_net *_net

