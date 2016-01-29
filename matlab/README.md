# MATLAB interface to SDDEKit

This is a MATLAB toolbox wrapping SDDEKit, a C library.

## Examples

_TODO_

## Development

A major goal for this wrapper was that a user could 1) use each of the components
of SDDEKit written in C individually and 2) define a component in a MATLAB
function / struct, and then use it in conjuction with other components of SDDEKit.

MATLAB has a nice libffi-like set of functions with working with
shared library via ABI. Still a few workarounds to keep in mind:

- Call function pointers in structs not possible, so libSDDEKit provides
  regular functions wrapping interface methods, which are called on
  opaque pointers.

- Redirecting error & log output requires initializing the DLL to use
  mexPrintf, so a small mex function provided to do that as well as
  use mexMalloc for memory allocations.

- user provided functions / function handles requires
  a small compiled callback support lib.
