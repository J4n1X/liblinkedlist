CC=gcc
CFLAGS=-O2 -fpic
ROOTDIR:=$(shell pwd)
OBJDIR=$(ROOTDIR)/obj
LIBDIR=$(ROOTDIR)/lib

CFILES:=$(wildcard $(ROOTDIR)/*.c)
OFILES:=$(pathsubst $(ROOTDIR)/%.c,$(OBJDIR)/%.o,$(CFILES))
HFILES=liblist.h

ifeq ($(PREFIX),)
    PREFIX := /usr
endif

all: static shared

install: shared
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(LIBDIR)/liblist.so $(DESTDIR)$(PREFIX)/lib/

shared: $(OBJDIR)/liblist.o prepare
	$(CC) -shared $(OBJDIR)/liblist.o -o lib/liblist.so

static: $(OBJDIR)/liblist.o prepare
	ar rcs $(LIBDIR)/liblist.a 

$(OBJDIR)/%.o: $(ROOTDIR)/%.c prepare
	$(CC) $(CFLAGS) -c $< -o $@

prepare:
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	@if [ ! -d $(LIBDIR) ]; then mkdir $(LIBDIR); fi

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIBDIR)


