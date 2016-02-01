# copyright 2016 Apache 2 sddekit authors

"""
This script uses the ctypesgen generated signatures to generate
a C header and implementation to access interface methods, i.e.
function pointers in SDDEKit structs, to ease bindings to high-
level languages.

"""


import ctypes
import _sddekit as sd

type_of_cfunc = type(ctypes.CFUNCTYPE(ctypes.c_void_p))

type_map = {
    # TODO see why ctypesgen makes c_uint of uint32_t?
    ctypes.c_uint: 'uint32_t',
    ctypes.c_ulong: 'uint32_t',
    ctypes.c_double: 'double',
    ctypes.c_bool: 'bool',
    ctypes.c_int: 'int',
    # ctypes doesn't distinguish void* and void
    ctypes.c_void_p: 'void *',
    ctypes.POINTER(ctypes.c_double): 'double *',
    ctypes.POINTER(ctypes.c_uint): 'uint32_t *',
    ctypes.POINTER(ctypes.c_ulong): 'uint32_t *',
    ctypes.POINTER(ctypes.POINTER(ctypes.c_ulong)): 'uint32_t **',
    ctypes.POINTER(ctypes.POINTER(ctypes.c_uint)): 'uint32_t **',
    ctypes.POINTER(ctypes.POINTER(ctypes.c_double)): 'uint32_t **',
}

thunks = []

for key in dir(sd):
    if key.startswith('struct_sd_'):
        name = key.split('struct_')[1]
        val = getattr(sd, key)
        for fname, sig in val._fields_:
            if not isinstance(sig, type_of_cfunc):
                continue
            rettype = type_map[sig().restype]
            fnname = '%s_%s' % (name, fname)
            argtypes = []
            for arg in sig().argtypes:
                aname = arg.__name__
                apart = aname.split('LP_struct_')
                if len(apart) == 2:
                    argtypes.append(apart[1] + ' *')
                else:
                    argtypes.append(type_map[arg])
            thunks.append((rettype, name, fname, argtypes))

with open('sddekit_if.h', 'w') as fd:
    for r, o, f, a in thunks:
        print >> fd, '%s %s_%s(%s);' % (r, o, f, ', '.join(map(str, a)))

with open('sddekit_if.c', 'w') as fd:
    for ret, obj, meth, args in thunks:
        print >> fd, '%s %s_%s(%s) { return a0->%s(%s); }' % (
            ret, obj, meth,
            ', '.join(['%s a%d' % (at, i) for i, at in enumerate(argtypes)]),
            meth,
            ', '.join(['a%d' % (i, ) for i, _ in enumerate(argtypes)]))

# vim: sts=4 sw=4 et ai rnu
