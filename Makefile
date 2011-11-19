GCC=gcc
DEBUG=yes
NOSTD=no

repo=ioccc

HEADERS=headers.h
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

all: $(OBJS)
	$(GCC) -o datamatrix $^

%.o: %.c headers.h
	$(GCC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS)

.PHONY:  mrproper clean push pull test

test:
	@bash test.sh

mrproper: clean
	rm -f datamatrix
