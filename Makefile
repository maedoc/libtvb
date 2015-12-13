# Apache 2.0 INS-AMU 2015

CC=gcc
FC=gfortran
OPTFLAGS=-O0
WFLAGS=-Wpedantic -Wall -Wextra
CFLAGS=-ansi -fPIC $(OPTFLAGS) $(WFLAGS) -g -DSKDEBUG
LFLAGS=-lm
FFLAGS=-Ofast -fPIC

skmods=util test hist solv sys scheme
ekobjs=lapack.o blas.o expokit.o
objects=$(patsubst %,sk_%.o,$(skmods)) randomkit.o
testfiles=$(wildcard test_*.c)


all: $(objects) libsk.so

check: sk_tests
	valgrind --error-exitcode=1 --track-origins=yes --leak-check=full ./sk_tests

gdb: sk_tests
	gdb sk_tests -ex "b sk_test_failed"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o

%.o: %.f
	$(FC) $(FFLAGS) -c $< -o $*.o

libsk.so: $(objects)
	$(CC) -shared $(objects) -o libsk.so

sk_tests.c: $(objects) $(patsubst %.c,%.o,$(testfiles))
	./sk_tests_collect.sh > sk_tests.c

sk_tests: sk_tests.c
	$(CC) $(CFLAGS) $(objects) test_*.o sk_tests.c $(LFLAGS) -o $@

clean:
	rm -rf *.o sk_tests *.so tags *.dat
