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

skmods=util test hist solv sys scheme
ekobjs=objs/lapack.o objs/blas.o objs/expokit.o
figs=exc_em_heun
pngs=$(patsubst %,fig_%.png,$(figs))
objects=$(patsubst %,objs/sk_%.o,$(skmods)) objs/randomkit.o
testfiles=$(wildcard test/*.c)
src=$(wildcard src/*.c) $(wildcard include/*.h) $(wildcard src/*.f)


all: $(objects) libsk.so

test: sk_tests
	valgrind $(VALGRINDFLAGS) ./sk_tests

gdb: sk_tests
	gdb sk_tests -ex "b sk_test_failed"

objs:
	mkdir -p objs

objs/%.o: src/%.c objs
	$(CC) $(CFLAGS) -c $< -o objs/$*.o

objs/test_%.o: test/test_%.c
	$(CC) $(CFLAGS) -c $< -o objs/test_$*.o

objs/%.o: src/%.f
	$(FC) $(FFLAGS) -c $< -o objs/$*.o

libsk.so: $(objects)
	$(CC) -shared $(objects) -o libsk.so

sk_tests: $(objects) $(patsubst test/%.c,objs/%.o,$(testfiles))
	./collect_tests.sh > sk_tests.c
	$(CC) $(CFLAGS) $(objects) objs/test_*.o sk_tests.c $(LFLAGS) -o $@

fig: test $(pngs)

fig_%.png: fig_%.gpi
	gnuplot -e "set terminal png; set output '$@'" $<

dox: $(src) Doxyfile
	doxygen Doxyfile

clean:
	rm -rf objs sk_tests sk_tests.c *.so tags *.dat *.png dox

license:
	head -n 1 *.c *.h *.f *.pyc
