# Developing

Fork the code, try it out. See our documented [issues](issues) or
add your own.

## Contributing

Please follow the generic GitHub workflow:

- fork the repo
- create a topic branch, e.g add-foo-implementation
- make modifications
- git commit -m 'useful comments'
- push branch to your fork on GitHub
- open pull request

[Here's way more detail w/ pictures](https://guides.github.com/introduction/flow/index.html)

## Python wrapper

The current work on Python wrapper in the `ctype` branch follows the naming conventions
of the C library for the moment, drastically reducing the code required to use it. Though
if time permits, the API could be Python-ized.

## C lib architecture

To keep things general, most high-level components are exposed as interfaces through
structs whose fields are just function pointers.

Contributing an implementation of a particular interface therefore implies

- writing implementations for each of the members of the interface struct
- writing a constructor function which
  - alloc with tvb_malloc
  - fill out interface struct
  - return it
- document & test

Keep in mind that if you 'subclass' an existing interface, some methods like
`free` should be available (and correctly implemented) in both

## Profiling

Profiling the code means compiling it with specific flags and running benchmarks
or test code to generate information on how much time each part of the code takes.

Valgrind's callgrind tool provides good detail (line-by-line profiling) at some
runtime cost
```bash
python make.py build -g
valgrind --tool=cachegrind build/bench_net_gen2d
kcachegrind  cachegrind.out.*
```

## What is TVB_API?

It is defined in [libtvb.h](https://github.com/maedoc/libtvb/blob/master/src/libtvb.h#L22)

When you are compiling with Microsoft Visual Studio, the visibility of an API function depends on a non-standard declaration in front of the function declaration:

- when compiling the library itself, it has to be dllexport
- when compiling a code using the library it has to be dllimport

To support these cases, all libtvb public functions are declared with TVB_API,
which is defined according to whether the code in which the header is included
is part of the library or just using the library.

On Linux or Mac, TVB_API is ignored for the moment.
