# Testing

When making changes to the C library, please make sure
to test your changes before doing anything else.

On an up-to-date Linux, Mac or MinGW on Windows with
GCC or Clang and Make installed, this can be as simple as

```bash
$ make -j tests && ./tests
```

You may need to adjust compile flags for your platform. The
(currently) most common problem is due to sanitizers, as
addressed in the next section.

## Sanitizers

By default, the undefined behavior and other various sanitizers
are used to instrument the test code to identify potential bugs.

However, if you run into a compile-time error such

```
gcc: error: unrecognized command line option ‘-fsanitize=undefined’
```

your compiler is a little older, so you should invoke
`make` as `make SANFLAGS= -j tests`, to avoid using the
sanitizer instrumentation. 

Sanitizers require small runtime libraries that may require
installation, so if you run into link-time error such as missing
`ubsan`, install this library with your package manager.

## Failures

Running the tests will print any failed tests in the following
format
```
[tvb_test] FAILURE 36/320 test/test_solv.c:114 `(2.34)==(sysd.t)`
```
identifying the responsible file, line number and condition.

Sometimes it is useful to jump into the debugger to inspect
state at the failure point. Every failure results in a call to
`tvb_test_failed`, so breaking on this function and jumping up
two stack frames:

```
~/libtvb gdb tests
GNU gdb (Ubuntu 7.7.1-0ubuntu5~14.04.2) 7.7.1
...
Reading symbols from tests...done.
(gdb) b tvb_test_failed
Breakpoint 1 at 0x804e659: file src/tvb_test.c, line 85.
(gdb) r
Starting program: /home/sophie/libtvb/tests 
...
Breakpoint 1, tvb_test_failed (scond=0x8059a94 "(sol->get_x(sol))==(sysd.x+1)", fname=0x8059950 "test/test_solv.c", lineno=116)
    at src/tvb_test.c:85
85		nfail++;
(gdb) up 2
#2  0x0805607e in tvb_test__solv_simple () at test/test_solv.c:116
116		EXPECT_EQ(sol->get_x(sol),sysd.x+1);
(gdb) p sysd.x
$1 = (double *) 0x8064418
(gdb) p *sysd.x
$2 = 2.9077991554787804e-312
```

## Valgrind

Valgrind is an effective tool for checking invalid memory accesses,
invalid `free`s and memory leaks.

In particular, whenever debugging does not reveal an obvious bug in
the code around the failure, it is worth running `tests` in 

```
valgrind --error-exitcode=1 --track-origins=yes --leak-check=full ./tests
```

to see if there are any invalid memory reads or writes. An invalid write
can, for example, corrupt an index causing a out of bounds error.

## junit.xml

As a convenience, test results are written to a `junit.xml` file
in the working directory, sufficiently compatible to be used
with the Hudson continuous integration system.

## Travis

All commits to `maedoc/libtvb` as well as pull requests are checked
via the Travis continuous integration server, which runs tests through
Valgrind as well as checking coverage. See `.travis.yml` for details.

## Visual Studio

The tests are not yet set up as a project in the Visual Studio solution,
as they are run extensively on other compilers and platforms, but this is
something that would be nice to have.
