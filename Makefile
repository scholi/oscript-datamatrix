GCC=gcc
DEBUG=yes

repo=ioccc

HEADERS=
SOURCES=$(wildcard *.c)
OBJS=$(SOURCES:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS=-g -ansi -std=c99 -std=gnu99 -D DEBUG -Wall -D VERBOSE -D MACRO -D RAM -D STACK
else
	CFLAGS=-ansi -std=c99 -std=gnu99 -Wall
endif

all: datamatrix
	
datamatrix: $(OBJS)
	$(GCC) -o datamatrix $^

%.o: %.c headers.h
	$(GCC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS)

.PHONY:  mrproper clean push pull test

test:
	@bash test.sh

stack: stack.c
	$(GCC) -g -o stack -D STANDALONE -std=gnu99 $<

mrproper: clean
	rm -f datamatrix

oscript: oscript.man
	groff -man -Tascii $< | less
