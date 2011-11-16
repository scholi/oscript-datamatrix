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

%.o: %.c
	$(GCC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS)

.PHONY:  mrproper clean push pull test

test:
	@[ ! "$$(./datamatrix "abcde" | tail -n 12 | diff unit.test -)" ] || echo "Test Failed"

mrproper: clean
	rm -f datamatrix

push:
	git push ssh://kpax/~/$(repo).git

pull:
	git pull ssh://kpax/~/$(repo).git
