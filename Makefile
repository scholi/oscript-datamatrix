GCC=gcc
DEBUG=yes

SOURCES=$(wildcard *.c)
OBJS=$(SOURCES:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS=-ansi -std=c99 -std=gnu99 -D DEBUG
else
	CFLAGS=-ansi -std=c99 -std=gnu99
endif

all: datamatrix

datamatrix: datamatrix.o
	$(GCC) -o $@ $^

debug: datamatrix.o

%.o: %.c
	$(GCC) -c $(CFLAGS) $<

clear:
	rm -f $(OBJS)

.PHONY:  mrproper clear

mrproper: clear
	rm -f datamatrix
