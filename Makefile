CC=gcc
MAKE=make
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP
OS:=$(shell uname)

ifeq ($(OS),Linux)
USE_EVDEV=1
endif

USE_CLI=1

APPS:=lamprey
SOS:=liblamprey.so

CFLAGS=-Wall -g -pthread -fPIC
SO_LIBS=
LIBS=-L. -llamprey -Wl,-rpath=.
FILTER_C:=main.c

SO_LIBS+=-lxml2

ifeq ($(DEBUG),1)
CFLAGS+=-DDEBUG
endif
ifeq ($(USE_EVDEV),1)
CFLAGS+=-DUSE_EVDEV
CFLAGS+=$(shell pkg-config --cflags libevdev)
SO_LIBS+=$(shell pkg-config --libs libevdev)
else
FILTER_C+=input-evdev.c
endif
ifeq ($(USE_CLI),1)
CFLAGS+=-DUSE_CLI
else
FILTER_C+=display-cli.c
endif
ifeq ($(USE_GTK),1)
CFLAGS+=-DUSE_GTK
CFLAGS+=$(shell pkg-config --cflags gtk+-3.0)
SO_LIBS+=$(shell pkg-config --libs gtk+-3.0) -export-dynamic
else
FILTER_C+=display-gtk.c
endif
ifeq ($(USE_XDO),1)
CFLAGS+=-DUSE_XDO
SO_LIBS+=-lxdo
else
FILTER_C+=xdo.c
endif

SRCS:=$(filter-out $(FILTER_C),$(wildcard *.c))
OBJS:=$(SRCS:.c=.o)

ALLFLAGS:=$(CFLAGS) $(LIBS) $(SO_LIBS) $(SRCS)

ifeq ($(shell echo '$(ALLFLAGS)' | cmp -s - Makefile.deps; echo $$?),1)
REBUILD:=rebuild
.PHONY: $(REBUILD)
endif

all: $(APPS)

$(APPS): main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(SO_LIBS)

$(APPS): $(SOS)

-include $(patsubst %.o,.%.o.d,$(OBJS))

$(SOS): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(SO_LIBS) -shared

%.o: %.c Makefile.deps
	$(CC) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)

Makefile.deps: $(REBUILD)
	@echo '$(ALLFLAGS)' > $@

clean:
	@rm -rf $(APPS)
	@rm -rf *.so
	@rm -rf *.o
	@rm -rf .*.o.d
	@rm -rf Makefile.deps
