# Apache 2.0 INS-AMU 2015

CC=gcc
FC=gfortran
OPTFLAGS=-O0
WFLAGS=-Wpedantic 
CFLAGS=$(WFLAGS) -Wall -Wextra -fstrict-aliasing -Wstrict-aliasing
CFLAGS+=-ansi -fPIC $(OPTFLAGS) $(WFLAGS) -g -DSKDEBUG
CFLAGS+=-I./include
LFLAGS=-lm
FFLAGS=-Ofast -fPIC
VALGRINDFLAGS=--error-exitcode=1 --track-origins=yes --leak-check=full --show-leak-kinds=all

skmods=util test hist solv sys scheme net sparse
ekobjs=objs/lapack.o objs/blas.o objs/expokit.o
objects=$(patsubst %,objs/sk_%.o,$(skmods)) objs/randomkit.o
testfiles=$(wildcard test/*.c)
testobjects=$(patsubst test/%.c,objs/%.o,$(testfiles))
src=$(wildcard src/*.c) $(wildcard include/*.h) $(wildcard src/*.f)


all: $(objects) libsk.so

test: sk_tests
	valgrind $(VALGRINDFLAGS) ./sk_tests --all

gdb: sk_tests
	gdb sk_tests -ex "b sk_test_failed"

objs:
	mkdir -p objs

objs/%.o: src/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o objs/$*.o

objs/test_%.o: test/test_%.c
	$(CC) $(CFLAGS) -c $< -o objs/test_$*.o

objs/%.o: src/%.f
	$(FC) $(FFLAGS) -c $< -o objs/$*.o

libsk.so: $(objects)
	$(CC) -shared $(objects) -o libsk.so

sk_tests.c: $(testobjects)
	test/collect_tests.sh > sk_tests.c

sk_tests: $(objects) sk_tests.c
	$(CC) $(CFLAGS) $(objects) $(testobjects) sk_tests.c $(LFLAGS) -o $@

bench_%: bench/bench_%.c $(objects)
	$(CC) $(CFLAGS) $(objects) $< $(LFLAGS) -o $@

fig: test $(patsubst %.gpi,%.png,$(wildcard fig/*.gpi))

%.png: %.gpi
	gnuplot -e "set terminal png; set output '$@'" $<

dox: $(src) Doxyfile
	doxygen Doxyfile

clean:
	rm -rf objs sk_tests sk_tests.c *.so tags *.dat fig/*.png dox

license:
	head -n 1 *.c *.h *.f *.pyc
