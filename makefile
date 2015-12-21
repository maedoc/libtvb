CC=gcc
CFLAGS=-Iinclude -DSKDEBUG -g -O0
LDFLAGS=-lm
sk_ver_major = 0
sk_ver_minor = 0
sk_res_dir = $(shell pwd)

skobj=$(patsubst src/%.c,%.o,$(wildcard src/*.c))
testobj=$(patsubst test/%.c,%.o,$(wildcard test/test_*.c))
figs=$(patsubst fig/%.gpi,%.png,$(wildcard fig/*.gpi))

all: sktest test $(figs)
	cp *.png ../storage/

test: sktest
	./sktest

sktest: include/test_list.h $(skobj) $(testobj) alltests.o main.o
	$(CC) $(CFLAGS) $(skobj) $(testobj) alltests.o $(LDFLAGS) main.o -o sktest

%.o: src/%.c include/sk_config.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

%.o: test/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

include/sk_config.h: include/sk_config.h.in
	cp $< $@
	sed -i s,@sk_ver_major@,$(sk_ver_major), $@
	sed -i s,@sk_ver_minor@,$(sk_ver_minor), $@
	sed -i s,@sk_res_dir@,$(sk_res_dir), $@

include/test_list.h: $(testobj)
	rm -f include/test_list.h
	for t in $(shell nm *.o | grep sk_test__ | cut -f 3 -d ' '); do \
		echo "TEST_FOUND($$t)" >> include/test_list.h ; \
	done

clean:
	rm -f *.o *.so include/test_list.h include/sk_config.h *.dat sktest *.png

gdb: sktest
	gdb sktest -ex 'b sk_test_failed' -ex 'b src/sk_malloc.c:52'

%.png: fig/%.gpi
	gnuplot -e "set terminal png; set output '$@'" $<
