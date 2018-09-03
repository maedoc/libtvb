# SDDEKit 

SDDEKit is a C rewrite and generalization of numerical algorithms
backing the simulator of [The Virtual Brain](http://thevirtualbrain.org)
project, though it is intended to support any sort of modeling project
involving stochastic delay differential equations.

The current focus is nailing down 'software carpentry' aspects of building a
scientific library, and only preliminary sets of mathematical components are
implemented; as such, it is not for general use until the 
upcoming v0.1 release.

Build the library & benchmark with
```bash
python -m dev build
```
(if you work in Bash, you may want to `alias dev='python -m dev '`).

We're currently rewriting the test & benchmark suite using upcoming Python bindings.

See our [docs](doc/README.md) for more information.

Many thanks to our contributors

- Abheek Ghosh <abheekghosh.ag@gmail.com>

This work is partially funded by the French Medical Foundation.

[![Build Status](https://travis-ci.org/maedoc/libtvb.svg?branch=master)](https://travis-ci.org/maedoc/libtvb)
![Coverage Status](https://coveralls.io/repos/github/maedoc/libtvb/badge.svg?branch=master)

