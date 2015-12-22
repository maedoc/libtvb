CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror
ifeq ($(BUILD),fast)
CFLAGS+=-Ofast
else
CFLAGS+=-DSKDEBUG -g -O0
endif
LDFLAGS=-lm
LIBCFLAGS=$(CFLAGS)
LIBLDFLAGS=$(LDFLAGS)
sk_ver_major = 0
sk_ver_minor = 0

ifeq ($(BUILD),prof)
LIBCFLAGS+=-pg -fprofile-arcs -ftest-coverage
LIBLDFLAGS+=-lgcov
LDFLAGS+=-lgcov -pg
else
endif

skobj=$(patsubst src/%.c,%.o,$(wildcard src/*.c)) sk_config.o
testobj=$(patsubst test/%.c,%.o,$(wildcard test/test_*.c))
figs=$(patsubst fig/%.gpi,%.png,$(wildcard fig/*.gpi))
benchs=$(patsubst bench/%.c,%,$(wildcard bench/bench_*.c))

all: sktest test $(figs)
	cp *.png ../storage/

test: sktest
	./sktest

rj: # rebuild and test quickly
	make -B -j include/test_list.h
	make -B -j sktest
	./sktest

sktest: include/test_list.h $(skobj) $(testobj) alltests.o main.o
	$(CC) $(CFLAGS) $(skobj) $(testobj) alltests.o $(LDFLAGS) main.o -o sktest

bench_%: bench/bench_%.c $(skobj)
	$(CC) $(CFLAGS) $(skobj) $< -o bench_$* $(LDFLAGS)

sk_config.o: sk_config.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

%.o: src/%.c sk_config.o
	$(CC) $(LIBCFLAGS) -c $< $(LIBLDFLAGS)

%.o: test/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

sk_config.c: src/sk_config.c.in
	cp $< $@
	sed -i s,@sk_ver_major@,$(sk_ver_major), $@
	sed -i s,@sk_ver_minor@,$(sk_ver_minor), $@
	sed -i s,@sk_res_dir@,$(shell pwd), $@
	sed -i s,@sk_git_rev@,$(shell git rev-parse HEAD), $@

include/test_list.h: $(testobj)
	rm -f include/test_list.h
	for t in $(shell nm *.o | grep sk_test__ | cut -f 3 -d ' '); do \
		echo "TEST_FOUND($$t)" >> include/test_list.h ; \
	done

clean:
	rm -f *.o *.so include/test_list.h *.dat sktest *.png bench_* sk_config.c

gdb: sktest
	gdb sktest -ex 'b sk_test_failed' -ex 'b src/sk_malloc.c:52'

%.png: fig/%.gpi
	gnuplot -e "set terminal png; set output '$@'" $<
