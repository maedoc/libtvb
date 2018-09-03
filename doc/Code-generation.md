Some code generation is used, to avoid writing repetitive code by hand.

Currently, src/api.py reads src/libtvb_simple.h using pycparser and generates wrappers for struct field function pointers.

This is still a simple application of pycparser, but we will add

- generate ctypes signatures for function & struct
- generate MEX gateway to call any function or struct->fn_ptr

