CC=gcc
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

CFLAGS=-Wall -g -pthread
CFLAGS+=$(shell pkg-config --cflags libevdev)
CFLAGS+=$(shell pkg-config --cflags gtk+-3.0)

LIBS=
LIBS+=$(shell pkg-config --libs libevdev)
LIBS+=$(shell pkg-config --libs gtk+-3.0) -export-dynamic
LIBS+=-lxdo

APPS=lamprey
SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

all: $(APPS)

$(APPS): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

-include $(patsubst %.o,.%.o.d,$(OBJS))

%.o: %.c
	$(CC) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)

clean:
	@rm -rf $(APPS)
	@rm -rf *.o
	@rm -rf .*.o.d
