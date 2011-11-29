GCC=gcc
DEBUG=yes
SDEBUG=no

repo=ioccc

HEADERS=
SOURCES=main.c stack.c
OBJS=$(SOURCES:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS=-g -ansi -std=c99 -std=gnu99 -D DEBUG -Wall -DVERBOSE -DSTACK
else
	CFLAGS=-ansi -std=c99 -std=gnu99 -Wall
endif

ifeq ($(SDEBUG),yes)
	CFLAGS+= -DMEM -DSTACK
endif

all: datamatrix
	./datamatrix "Hello"
	
datamatrix: $(OBJS)
	$(GCC) -o datamatrix $^

%.o: %.c headers.h
	$(GCC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS)

.PHONY:  mrproper clean push pull test

test: datamatrix
	@bash test.sh

stack: stack.c
	$(GCC) $(CFLAGS) -D STANDALONE -o stack $<

mrproper: clean
	rm -f datamatrix

oscript: oscript.man
	groff -man -Tascii $< | less
