CC=gcc
MAKE=make
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP
OS:=$(shell uname)

ifeq ($(OS),Linux)
USE_EVDEV=1
else
USE_EVDEV=
endif
USE_GTK=
USE_XDO=

CFLAGS=-Wall -g -pthread -fPIC
ifdef DEBUG
CFLAGS+=-DDEBUG
endif
ifdef USE_EVDEV
CFLAGS+=$(shell pkg-config --cflags libevdev)
CFLAGS+=-DUSE_EVDEV
endif
ifdef USE_GTK
CFLAGS+=$(shell pkg-config --cflags gtk+-3.0)
CFLAGS+=-DUSE_GTK
endif
ifdef USE_XDO
CFLAGS+=-DUSE_XDO
endif

SO_LIBS=
ifdef USE_EVDEV
SO_LIBS+=$(shell pkg-config --libs libevdev)
endif
ifdef USE_GTK
SO_LIBS+=$(shell pkg-config --libs gtk+-3.0) -export-dynamic
endif
ifdef USE_XDO
SO_LIBS+=-lxdo
endif
SO_LIBS+=-lxml2

LIBS=-L. -llamprey -Wl,-rpath=.

APPS=lamprey
SOS=liblamprey.so
FILTER_C=main.c

ifndef USE_EVDEV
FILTER_C+=input-evdev.c
endif
ifndef USE_GTK
FILTER_C+=display-gtk.c
endif
ifndef USE_XDO
FILTER_C+=xdo.c
endif

SRCS=$(filter-out $(FILTER_C),$(wildcard *.c))
OBJS=$(SRCS:.c=.o)

all: $(APPS)

$(APPS): main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(SO_LIBS)

$(APPS): $(SOS)

-include $(patsubst %.o,.%.o.d,$(OBJS))

$(SOS): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(SO_LIBS) -shared

%.o: %.c
	$(CC) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)

clean:
	@rm -rf $(APPS)
	@rm -rf *.so
	@rm -rf *.o
	@rm -rf .*.o.d
