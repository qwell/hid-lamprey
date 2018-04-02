CC=gcc
MAKE=make
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP
OS:=$(shell uname)

-include config.out

APPS:=lamprey
SOS:=liblamprey.so

CFLAGS=-Wall -g -pthread -fPIC
SO_LIBS=-lm
LIBS=-L. -llamprey -Wl,-rpath=.
FILTER_C:=main.c

SO_LIBS+=-lxml2

ifeq ($(DEBUG),1)
CFLAGS+=-DDEBUG
endif
ifeq ($(HAVE_EVDEV),1)
CFLAGS+=-DUSE_EVDEV
CFLAGS+=$(EVDEV_CFLAGS)
SO_LIBS+=$(EVDEV_LIBS)
else
FILTER_C+=input-evdev.c
endif
ifeq ($(HAVE_CLI),1)
CFLAGS+=-DUSE_CLI
else
FILTER_C+=display-cli.c
endif
ifeq ($(HAVE_GTK3),1)
CFLAGS+=-DUSE_GTK
CFLAGS+=$(GTK3_CFLAGS)
SO_LIBS+=$(GTK3_LIBS)
else
FILTER_C+=display-gtk.c
endif
ifeq ($(HAVE_XDO),1)
CFLAGS+=-DUSE_XDO
CFLAGS+=$(XDO_CFLAGS)
SO_LIBS+=$(XDO_LIBS)
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
