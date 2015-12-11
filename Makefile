CC=gcc
FC=gfortran
OPTFLAGS=-O0
WFLAGS=-Wpedantic -Wall -Wextra
CFLAGS=-ansi $(OPTFLAGS) $(WFLAGS) -g
FFLAGS=-Ofast

skmods=util test
objects=$(patsubst %,sk_%.o,$(skmods))
testfiles=$(wildcard test_*.c)

# TODO handle expokit's blas vs user-provided

all: $(objects)

test: sk_tests
	./sk_tests

debug: sk_tests
	gdb sk_tests -ex "b sk_test_failed"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o

sk_tests.c: $(objects) $(patsubst %.c,%.o,$(testfiles))
	./gentest.sh > sk_tests.c

sk_tests: sk_tests.c
	$(CC) $(CFLAGS) $(objects) test_*.o sk_tests.c -o $@

clean:
	rm -rf *.o sk_test
