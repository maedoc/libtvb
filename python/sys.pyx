# copyright 2016 Apache 2 sddekit authors

from sddekit_h cimport *


cdef uint32_t sys_py_ndim(sd_sys*s):
    cdef object sys = <object> s.ptr
    cdef uint32_t i = sys.ndim
    return i

cdef uint32_t sys_py_ndc(sd_sys*s):
    cdef object sys = <object> s.ptr
    cdef uint32_t i = sys.ndc
    return i

cdef uint32_t sys_py_nobs(sd_sys*s):
    cdef object sys = <object> s.ptr
    cdef uint32_t i = sys.nobs
    return i

cdef uint32_t sys_py_nrpar(sd_sys*s):
    cdef object sys = <object> s.ptr
    cdef uint32_t i = sys.nrpar
    return i

cdef uint32_t sys_py_nipar(sd_sys*s):
    cdef object sys = <object> s.ptr
    cdef uint32_t i = sys.nipar
    return i

cdef sd_stat sys_py_apply(sd_sys *s, sd_sys_in *i, sd_sys_out *o):
    cdef object sys = <object> s.ptr
    # TODO conversions
    #f, g, o = sys.apply(i.hist, i.rng, i.id, i.t, i.x, i.i)
    # TODO conversions
    """
    o.f = f
    o.g = g
    o.o = o
    """
    return SD_OK

cdef void sys_py_free(sd_sys *s):
    Py_DECREF(<object> s.ptr)
    free(s)


cdef class Sys(object):
    "Base class for system defintions, may be defined in C."
    cdef sd_sys *sys

    @property
    def ndim(self):
        return self.sys.ndim(self.sys)

    @property
    def ndc(self):
        return self.sys.ndc(self.sys)

    @property
    def nobs(self):
        return self.sys.nobs(self.sys)

    @property
    def nrpar(self):
        return self.sys.nrpar(self.sys)

    @property
    def nipar(self):
        return self.sys.nipar(self.sys)

    def apply(self, hist, rng, id, t, x, i):
        cdef:
            sd_sys_in in_
            sd_sys_out out_
        raise NotImplementedError

    def __del__(self):
        self.sys.free(self.sys)


cdef object sys_of_ptr(sd_sys *s):
    sys = Sys()
    sys.s = s
    return sys


cdef class PySys(Sys):
    "Base class for systems defined in Python."

    def __init__(self):
        "Construct system defined by Python subclass."
        if self.__class__.__name__ == 'PySys':
            raise TypeError('PySys must be subclassed.')
        self.s = <sd_sys *> malloc(sizeof(sd_sys))
        Py_INCREF(self)
        self.s.ptr = <void*> self
        self.s.ndim = &sys_py_ndim
        self.s.ndc = &sys_py_ndc
        self.s.nobs = &sys_py_nobs
        self.s.nrpar = &sys_py_nrpar
        self.s.nipar = &sys_py_nipar
        self.s.apply = &sys_py_apply
        self.s.free = &sys_py_free
