CC=gcc
MAKE=make
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

USE_GTK=
USE_XDO=

CFLAGS=-Wall -g -pthread -fPIC
ifdef DEBUG
CFLAGS+=-DDEBUG
endif
CFLAGS+=$(shell pkg-config --cflags libevdev)
ifdef USE_GTK
CFLAGS+=$(shell pkg-config --cflags gtk+-3.0)
CFLAGS+=-DUSE_GTK
endif
ifdef USE_XDO
CFLAGS+=-DUSE_XDO
endif

SO_LIBS=
SO_LIBS+=$(shell pkg-config --libs libevdev)
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
