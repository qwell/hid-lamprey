CC=gcc
MAKE=make
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

CFLAGS=-Wall -g -pthread -fPIC
CFLAGS+=$(shell pkg-config --cflags libevdev)
CFLAGS+=$(shell pkg-config --cflags gtk+-3.0)
#CFLAGS+=-DUSE_GTK

SO_LIBS=
SO_LIBS+=$(shell pkg-config --libs libevdev)
SO_LIBS+=$(shell pkg-config --libs gtk+-3.0) -export-dynamic
SO_LIBS+=-lxdo
SO_LIBS+=-lxml2

LIBS=-L. -llamprey -Wl,-rpath=.

APPS=lamprey
SOS=liblamprey.so
SRCS=$(filter-out main.c,$(wildcard *.c))
OBJS=$(SRCS:.c=.o)

all: $(APPS)

$(APPS): main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

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
