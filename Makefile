sources := $(wildcard lib/src/*.c lib/src/*/*.c)
objects := $(sources:%.c=%.o)

CFLAGS = -Ilib/include -fPIC

-include local.mk

all: libtvb.so

libtvb.so: $(objects)
	$(CC) $(objects) -shared -lm -o $@