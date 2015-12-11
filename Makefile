CC=gcc
FC=gfortran
OPTFLAGS=-O0
WFLAGS=-Wpedantic -Wall -Wextra
CFLAGS=-ansi $(OPTFLAGS) $(WFLAGS) -g -DSKDEBUG
LFLAGS=-lm
FFLAGS=-Ofast

skmods=util test hist
objects=$(patsubst %,sk_%.o,$(skmods))
testfiles=$(wildcard test_*.c)

# TODO handle expokit's blas vs user-provided

all: $(objects)

test: sk_tests
	./sk_tests

gdb: sk_tests
	gdb sk_tests -ex "b sk_test_failed"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o

sk_tests.c: $(objects) $(patsubst %.c,%.o,$(testfiles))
	./sk_tests_collect.sh > sk_tests.c

sk_tests: sk_tests.c
	$(CC) $(CFLAGS) $(objects) test_*.o sk_tests.c $(LFLAGS) -o $@

clean:
	rm -rf *.o sk_tests
