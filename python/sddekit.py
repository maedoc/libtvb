# copyright 2016 Apache 2 sddekit authors

import ctypes
import logging
import _sddekit

logger = logging.getLogger(__name__)

def make_nda2ptr(ct):
    def _(nda):
        return nda.ctypes.data_as(ctypes.POINTER(ct))
    return _

_pu = make_nda2ptr(ctypes.c_ulong)
_pd = make_nda2ptr(ctypes.c_double)

class NullPointerException(Exception):
    pass

class Base(object):
    
    def __init__(self, ptr):
        self._ptr = ptr

    def __getattr__(self, key):
        try:
            attr = object.__getattribute__(self, key)
            return attr
        except AttributeError as exc:
            f = getattr(self._ptr.contents, key, None)
            if f:
                def wrap(*args):
                    if self._ptr is None:
                        raise NullPointerException
                    return f(self._ptr, *args)
                return wrap
            else:
                raise exc

    def __del__(self):
        p = self._ptr
        if p is not None:
            try:
                free = p.contents.free
            except:
                logging.warning('no free method for %r' % (self,))
                free = None
            if free is not None:
                free(p)
            self._ptr = None

class Hist(Base):
    "Provides a history buffer for storing delayed state data."

    def __init__(self, vi, vd, t, dt):
        """
        Create a new history buffer.

        Parameters
        ----------
        vi : array of integers

        """

        new = _sddekit.sd_hist_new_default
        super(Hist, self).__init__(
            new(len(vi), _pu(vi), _pd(vd), t, dt))


# vim: sw=4 et foldmethod=marker
