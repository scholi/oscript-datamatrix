GCC=gcc
CFLAGS=-ansi -std=c99 -std=gnu99

all: datamatrix

datamatrix: datamatrix.o
	$(GCC) -o $@ $^

%.o: %.c
	$(GCC) -c $(CFLAGS) $<
