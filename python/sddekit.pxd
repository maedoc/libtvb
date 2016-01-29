# copyright 2016 Apache 2 sddekit authors

# This file provides the Cython declarations for the Cython implemented
# functions and classes wrapping the C library. This is probably what you
# what to use.

from sddekit_h cimport *
cimport numpy as np

cdef extern:
    np.ndarray np_of_ptr(int size, void *ptr, int typenum, int free_on_gc)
    sd_hfill * hfill_py_new(object fn)

# vim: sw=4 et
