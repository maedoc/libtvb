# MATLAB interface to SDDEKit

This is a MATLAB toolbox wrapping SDDEKit, a C library.

## Examples

_TODO_

## Development

While MATLAB has a nice libffi-like set of functions with working with
shared library via ABI but it does not support calling function pointers
in structs, which is used by SDDEKit extensively.

A MEX function gateway is therefore used in combination with a set of new-style
MATLAB handle classes, to automatically & safely handle memory alloc/free.
The C code implementing these is in the the private/ folder and most lines of
code are concerned with marshalling data between MATLAB and C.

A major goal for this wrapper was that a user could 1) use each of the components
of SDDEKit written in C individually and 2) define a component in a MATLAB
function / struct, and then use it in conjuction with other components of SDDEKit.

Because of the semantics of functions calls in MATLAB (specifically that modifications
to input arguments are not visible after function exits), some data copying is inevitable.
However, we hope (to be verified) that the MATLAB memory manager recognizes and
optimizes certain cases (identical pointer, etc.).
