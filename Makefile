# Apache 2.0 INS-AMU 2015

CC=gcc
FC=gfortran
OPTFLAGS=-O0
WFLAGS=-Wpedantic -Wall -Wextra
CFLAGS=-ansi -fPIC $(OPTFLAGS) $(WFLAGS) -g -DSKDEBUG
LFLAGS=-lm
FFLAGS=-Ofast -fPIC
VALGRINDFLAGS=--error-exitcode=1 --track-origins=yes --leak-check=full --show-leak-kinds=all

skmods=util test hist solv sys scheme
ekobjs=lapack.o blas.o expokit.o
figs=exc_em_heun
pngs=$(patsubst %,fig_%.png,$(figs))
objects=$(patsubst %,sk_%.o,$(skmods)) randomkit.o
testfiles=$(wildcard test_*.c)


all: $(objects) libsk.so

test: sk_tests
	valgrind $(VALGRINDFLAGS) ./sk_tests

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

fig: check $(pngs)

fig_%.png: fig_%.gpi
	gnuplot -e "set terminal png; set output '$@'" $<

clean:
	rm -rf *.o sk_tests *.so tags *.dat *.png

license:
	head -n 1 *.c *.h *.f *.pyc
