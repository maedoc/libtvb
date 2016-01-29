# copyright 2016 Apache 2 sddekit authors

from sddekit_h cimport *
from sddekit cimport *

ctypedef struct hfill_py:
    sd_hfill hf
    void *fn

cdef sd_stat hfill_py_apply(sd_hfill *hfill, uint32_t n, double * t, uint32_t *i, double * buf):
    cdef hfill_py *hp = <hfill_py*> hfill.ptr
    cdef np.ndarray[np.float64_t, ndim=1] np_buf
    t_ = np_of_ptr(n, t, np.NPY_DOUBLE, 0)
    i_ = np_of_ptr(n, t, np.NPY_UINT64, 0)
    try:
         np_buf = (<object> hp.fn)(t_, i_).astype(np.float64)
    except Exception as exc:
        print exc # TODO
        return SD_ERR
    for j in xrange(n):
        buf[j] = np_buf[j]
    return SD_OK

cdef void hfill_py_free(sd_hfill *h):
    free(h)

cdef sd_hfill * hfill_py_new(object fn):
    cdef hfill_py *h = <hfill_py *> malloc(sizeof(hfill_py))
    if not hasattr(fn, '__call__'):
        raise TypeError('arg fn must be callable')
    if h==NULL:
        raise Exception('alloc hfill_py failed.')
    h.fn = <void*> fn
    h.hf.ptr = h
    h.hf.apply = &hfill_py_apply
    h.hf.free = &hfill_py_free
    return &(h.hf)

# vim: sw=4 et
