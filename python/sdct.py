from ctypes import *

# handle windows/mac case
lib = CDLL('./libSDDEKit.so')

__version__ = '%d.%d' % (
    lib.sd_ver_major(),
    lib.sd_ver_minor()
)

class Stat(c_int):
    OK, ERR, CONT, STOP = map(c_int, range(4))

class Freeable(object):
    "Free on del, assume _free method"
    _ptr = None
    def __init__(self, ptr):
        self._ptr = ptr
    def __del__(self):
        if self._ptr is not None:
            self._free(self._ptr)
            self._ptr = None

class Rng(Freeable):

    class _Rng(Structure): pass

    _new = lib.sd_rng_new_default
    _seed = lib.sd_rng_seed
    _norm = lib.sd_rng_norm
    _free = lib.sd_rng_free

    _new.restype = POINTER(_Rng)
    _seed.restype = None
    _seed.argtypes = (POINTER(_Rng), )
    _norm.restype = c_double
    _norm.argtypes = (POINTER(_Rng), )
    _free.restype = None
    _free.argtypes = (POINTER(_Rng), )

    def __init__(self):
        super(Rng, self).__init__(self._new())

    def seed(self, uint):
        self._seed(self._ptr, uint)

    def norm(self):
        return self._norm(self._ptr)


class Hfill(object):

    class _hfill(Structure): pass
    _phf = POINTER(_hfill)

    _new_val = lib.sd_hfill_new_val
    _new_val.restype = _phf
    _new_val.argtypes = (c_double,)

    _apply = lib.sd_hfill_apply
    _apply.restype = Stat
    _apply.argtypes = (_phf, c_ulong, POINTER(c_double), 
        POINTER(c_ulong), POINTER(c_double))

    _free = lib.sd_hfill_free
    _free.restype = None
    _free.argtypes = (_phf, )

    def __init__(self, val=0.0):
        if hasattr(val, '__call__'):
            raise NotImplementedError
        super(Hfill, self).__init__(self._new_val(val))

# vim: sw=4 et		
