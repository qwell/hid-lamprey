CC=gcc
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

CFLAGS=-Wall -g -pthread -fPIC
CFLAGS+=$(shell pkg-config --cflags libevdev)
CFLAGS+=$(shell pkg-config --cflags gtk+-3.0)

SO_LIBS=
SO_LIBS+=$(shell pkg-config --libs libevdev)
SO_LIBS+=$(shell pkg-config --libs gtk+-3.0) -export-dynamic
SO_LIBS+=-lxdo

LIBS=-L. -llamprey -Wl,-rpath=.

APPS=lamprey
SOS=liblamprey.so
SRCS=$(filter-out main.c,$(wildcard *.c))
OBJS=$(SRCS:.c=.o)

all: $(APPS)

$(APPS): $(SOS) main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

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
