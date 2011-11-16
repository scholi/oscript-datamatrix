GCC=gcc
DEBUG=yes

repo=ioccc

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

.PHONY:  mrproper clear push pull

mrproper: clear
	rm -f datamatrix

push:
	git push ssh://kpax/~/$(repo).git

pull:
	git pull ssh://kpax/~/$(repo).git
