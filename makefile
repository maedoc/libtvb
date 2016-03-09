# copyright 2016 Apache 2 sddekit authors

CC=gcc
LDFLAGS = -lm -lOpenCL
VALFLAGS = --error-exitcode=1 --track-origins=yes --leak-check=full 
CFLAGS = -fPIC -std=c99 -Isrc
OBJEXT=o

cc_asan:=$(shell expr `gcc -dumpversion` \>= 4.8)
cc_ubsan:=$(shell expr `gcc -dumpversion` \>= 4.9)

ifeq ($(cc_asan),1)
    SANFLAGS += -fsanitize=address
endif

ifeq ($(cc_ubsan),1)
    SANFLAGS += -fsanitize=undefined
endif

# various build types {{{
ifeq ($(BUILD),fast)
	CFLAGS += -Ofast -flto -march=native
else ifeq ($(BUILD),cov)
	CFLAGS += -pg -fprofile-arcs -ftest-coverage
else ifeq ($(BUILD),js)
	CFLAGS += -s ALLOW_MEMORY_GROWTH=1 -O2
else
	CFLAGS += -Wall -Wextra $(SANFLAGS) -O0 -g
endif

ifeq ($(FDO),gen)
	CFLAGS += -fprofile-generate
else ifeq ($(FDO),use)
	CFLAGS += -fprofile-use
else ifeq ($(FDO),prof)
	CFLAGS += -pg -fprofile-arcs
else ifeq ($(FDO),callgrind)
	CFLAGS += -g
endif
# }}}

# file lists {{{
c_lib=$(wildcard src/*.c)
c_plib+=$(wildcard src/parallel/*.c)
c_test=$(wildcard test/test_*.c)
o_lib=$(patsubst src/%.c,%.$(OBJEXT),$(c_lib))
o_plib=$(patsubst src/parallel/%.c,%.$(OBJEXT),$(c_plib))
o_test=$(patsubst test/%.c,%.$(OBJEXT),$(c_test))
# }}}

# platform specific stuff (http://stackoverflow.com/q/19928965) {{{
ifeq ($(OS),Windows_NT)
	DLLEXT=dll
	RM=del /f
	EXE=.exe
else
	DLLEXT=so
	RM=rm -fr
	EXE=
endif
# except mac
ifeq ($(OS),Darwin)
	DLLEXT=dylib
endif
ifdef COMSPEC
	SHELL := $(COMSPEC)
endif

# }}}

# artifacts {{{

help:
	echo "make tests$(EXE) | bench_net_exc$(EXE) | libSDDEKit.$(DLLEXT) | clean"

tests$(EXE): $(o_lib) $(o_plib) $(o_test)
	$(CC) $(CFLAGS) test/main.c $^ -o tests$(BUILD)$(EXE) $(LDFLAGS)

libSDDEKit.$(DLLEXT): $(o_lib) $(o_plib)
	$(CC) -shared $^ -o libSDDEKit.$(DLLEXT) $(LDFLAGS)

clean:
	$(RM) $(o_lib) $(o_plib) $(o_test) bench_* tests* *.dat *.exe *.$(DLLEXT) *.ilk *.pdb *.gcda callgrind.out.* junit.xml

gh-pages:
	git branch -D gh-pages
	git init docs
	doxygen
	cd docs && git add html/* && git mv html/* ./ && git commit -m "add doxygen html"
	git fetch docs master:gh-pages
	rm -rf docs

# }}}

# generic rules {{{

%.$(OBJEXT): src/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@

%.$(OBJEXT): src/parallel/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@

%.$(OBJEXT): test/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@

%$(EXE): bench/%.c $(o_lib)
	$(CC) $(CFLAGS) $< $(o_lib) $(LDFLAGS) -o $@

# }}}

# vim: foldmethod=marker
