GCC=gcc
DEBUG=yes

repo=ioccc

HEADERS=headers.h
SOURCES=$(wildcard *.c)
OBJS=$(SOURCES:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS=-ansi -std=c99 -std=gnu99 -D DEBUG
else
	CFLAGS=-ansi -std=c99 -std=gnu99
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
