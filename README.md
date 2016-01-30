# SDDEKit 

![Build Status](https://travis-ci.org/maedoc/sddekit.svg?branch=master)
![Coverage Status](https://coveralls.io/repos/github/maedoc/sddekit/badge.svg?branch=master)

## What is SDDEKit?

A library for stochastic delay differential equations implementing published
numerical schemes, utilities for constructing network models and handling
simulation results, as well as bindings for MATLAB, Python.  Our intent is
to make it possible to use and benchmark available schemes on your favorite
model, not invent new numerical schemes, so we have attempted to follow
published results, documenting caveats, assumptions etc. Care will be taken to
handle calculation of partial erivatives, to enable higher order schemes,
optimization and inversion techniques.

*This is project is currently under heavy development; not for use pending v0.1 release*.

## Using

Currently the [documentation](https://maedoc.github.io/sddekit),
[tests](tests) and [benchmark](bench/bench_net_exc.c) are the best places 
to look to understand what you can do with SDDEKit.

You can build the tests and benchmark if you have GCC (or a C99 compiler) and Make:

```
make tests
make bench_net_exc 
```

Python, MATLAB bindings and C++ header are in the works, on separate 
(`ctype`/`cython`/`py-c-api`, `matlab`, `cpp` respectively) branches of
this repo.

## Contributing

Fork the code, try it out. See our documented [issues](issues) or
add your own.

## References

- Kloeden & Platen 1999 *Numerical Solution of Stochastic Differential Equations*.
- Fox et al 1998
- Mannella 200?
- Jimenez et al 2015
- Kuechler & Platen 2000
