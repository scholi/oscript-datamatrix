GCC=gcc
CFLAGS=-ansi -std=c99 -std=gnu99
SOURCES=$(wildcard *.c)
OBJS=$(SOURCES:.c=.o)

all: datamatrix

datamatrix: datamatrix.o
	$(GCC) -o $@ $^

%.o: %.c
	$(GCC) -c $(CFLAGS) $<

clear:
	rm -f $(OBJS)

.PHONY:  mrproper clear

mrproper: clear
	rm -f datamatrix
