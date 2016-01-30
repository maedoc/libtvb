# copyright 2016 Apache 2 sddekit authors

CC=gcc
LDFLAGS = -lm
VALFLAGS = --error-exitcode=1 --track-origins=yes --leak-check=full 
CFLAGS = -fPIC -std=c99 -Isrc

# various build types {{{
ifeq ($(BUILD),fast)
	CFLAGS += -Ofast
else ifeq ($(BUILD),cov)
	CFLAGS += -pg -fprofile-arcs -ftest-coverage
else
	CFLAGS += -Wall -Wextra -O0 -g
endif
# }}}

# file lists {{{
c_lib=$(wildcard src/*.c)
c_test=$(wildcard test/test_*.c)
o_lib=$(patsubst src/%.c,%.o,$(c_lib))
o_test=$(patsubst test/%.c,%.o,$(c_test))
# }}}

# platform specific stuff (http://stackoverflow.com/q/19928965) {{{
ifeq ($(OS),Windows_NT)
	DLLEXT=dll
	RM=del /f
	EXE=.exe
else
	DLLEXT=so
	RM=rm -f
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
	echo "make tests$(EXE) | libSDDEKit.$(DLLEXT) | clean"

tests$(EXE): $(o_lib) $(o_test)
	$(CC) $(CFLAGS) test/main.c $^ -o tests$(BUILD)$(EXE) $(LDFLAGS)

libSDDEKit.$(DLLEXT): $(o_lib)
	$(CC) -shared $^ -o libSDDEKit.$(DLLEXT) $(LDFLAGS)

clean:
	$(RM) $(o_lib) $(o_test) tests* *.dat *.exe *.$(DLLEXT)

gh-pages:
	git branch -D gh-pages
	git init docs
	doxygen
	cd docs && git add html/* && git mv html/* ./ && git commit -m "add doxygen html"
	git fetch docs master:gh-pages
	rm -rf docs


# }}}

# generic rules {{{

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

%.o: test/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

%: bench/%.c $(o_lib)
	$(CC) $(CFLAGS) $< $(o_lib) $(LDFLAGS) -o $@

# }}}

# vim: foldmethod=marker
