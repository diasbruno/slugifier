CC?=clang

DEBUG?=0

PROJECT=slugifier

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:%.c=%.o)

CFLAGS=-Wall -Werror -I. -I/usr/include
LDFLAGS=-lunac -lpcre2-8

ifneq ("$(DEBUG)", "0")
CFLAGS:=-g $(CFLAGS)
endif

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

ifneq ("$(DEBUG)", "0")
.PHONY: $(PROJECT)
endif
$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

all: $(PROJECT)

clean:
	rm -rf $(OBJECTS) $(PROJECT)

install:
	cp $(PROJECT) $(DEST)/$(PROJECT)
