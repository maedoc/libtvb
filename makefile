CC=gcc
CFLAGS=-std=c99 -Isrc -Wall -Wextra -Ofast
LDFLAGS=-lm
#
# e.g. -pg -fprofile-arcs -ftest-coverage
CFLAGS += $(EXTRA_CFLAGS)

# TODO provide alternatives for Windows
test_list_maker=./make_test_list.sh

test: libobjects run_tests
	./run_tests

memtest: libobjects run_tests
	valgrind --error-exitcode=1 --track-origins=yes --leak-check=full ./run_tests

bench: libobjects $(patsubst bench/%.c,%,$(wildcard bench/*.c))

libobjects: $(patsubst src/%.c,%.o,$(wildcard src/*.c))

run_tests: libobjects $(patsubst test/%.c,%.o,$(wildcard test/test_*.c))
	$(CC) $(CFLAGS) -I./ test/main.c *.o -o run_tests $(LDFLAGS)

valgrind: run_tests
	valgrind --leak-check=full --track-origins=yes ./run_tests &> val.out ; vim val.out

gdb: run_tests
	gdb run_tests

gdbtest: run_tests
	gdb run_tests -ex 'b sd_test_failed' -ex 'r'

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

%.o: test/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

%: bench/%.c
	$(CC) $(CFLAGS) $< *.o $(LDFLAGS)

bench_%: bench/bench_%.c
	$(CC) $(CFLAGS) $< *.o -o bench_$* $(LDFLAGS)

clean:
	rm -f *.o test_list.h sddekit.h.gch *.gcda *.gcno gmon.out *.c.gcov val.out run_tests *.dat
