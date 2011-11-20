GCC=gcc
DEBUG=no
NOSTD=yes

repo=ioccc

HEADERS=
SOURCES=$(wildcard *.c)
OBJS=$(SOURCES:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS=-g -ansi -std=c99 -std=gnu99 -D DEBUG -Wall
else
	CFLAGS=-ansi -std=c99 -std=gnu99 -Wall
  ifeq ($(NOSTD),yes)
	  CFLAGS+=-fno-builtin -nodefaultlibs -D NO_STD_ON_x32
  endif
endif

all: main.o
	$(GCC) -o datamatrix $^

%.o: %.c headers.h
	$(GCC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS)

.PHONY:  mrproper clean push pull test

test:
	@bash test.sh

stack: stack.c
	$(GCC) -o stack -D STANDALONE -std=gnu99 $<

mrproper: clean
	rm -f datamatrix
