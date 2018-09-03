# libtvb

Welcome to the documentation of libtvb.

## What is libtvb?

A library for stochastic delay differential equations implementing published
numerical schemes, utilities for constructing network models and handling
simulation results, as well as bindings for MATLAB, Python.  Our intent is
to make it possible to use and benchmark available schemes on your favorite
model, not invent new numerical schemes, so we have attempted to follow
[published results](#references), documenting caveats, assumptions etc. Care will be taken to
handle calculation of partial erivatives, to enable higher order schemes,
optimization and inversion techniques.

## Using

Currently the [overview](https://github.com/maedoc/libtvb/wiki/High-level-overview),
[documentation](https://maedoc.github.io/libtvb),
[tests](tests) and [benchmark](bench/bench_net_exc.c) are the best places 
to look to understand what you can do with libtvb.

Python, MATLAB bindings and C++ header are in the works, on separate 
(`ctype`/`cython`/`py-c-api`, `matlab`, `cpp` respectively) branches of
this repo.

You can build the tests and benchmark if you have GCC (or a C99 compiler) and Make:

```bash
$ make tests
...
$ make bench_net_exc 
...
```

Running the tests will generate some data files from [one of the tests](test/test_exc.c), which
tests different integration schemes on the same system. These can be compared with
the gnuplot script `fig/exc_em_emcolor_heun.gpi`

```bash
$ gnuplot fig/exc_em_emcolor_heun.gpi
```

which produces 

![this](exc_em_emcolor_heun.png)

Running the benchmark will produce a trace `bench_net_exc.dat` which can be visualized
with `fig/bench_net_exc.py`, producing

![this](bench_net_exc.png)

As stated, these are in place to help build up the library at this point. In the
future extensive examples for different kinds of systems & networks will be provided.

## Features

Current implemented

- a generic solver driver
- Euler-Maruyama, Heun & colored noise variants
- network system
- simple excitable, generic 2d oscillator & reduced Wong-Wang systems
- temporal averaging, convolution, spatial filter, memory buffer and write to file
- linear interpolation history buffer

## Where to go from here?

- If you're a programmer, we'd be happy to have help! See [`DEVELOP.md`](DEVELOP.md).
- If you wish to use libtvb in a webpage, see [`JS.md`](JS.md).
- Numerical analysis references
  - Kloeden & Platen 1999 *Numerical Solution of Stochastic Differential Equations*.
  - Fox et al 1998
  - Mannella 200?
  - Jimenez et al 2015
  - Kuechler & Platen 2000
