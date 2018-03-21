CC=gcc
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

CFLAGS=-Wall -g
CFLAGS+=$(shell pkg-config --cflags libevdev)

LIBS=
LIBS+=$(shell pkg-config --libs libevdev)
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
