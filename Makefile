CC=gcc
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

CFLAGS=-Wall
CFLAGS+=$(shell pkg-config --cflags libevdev)

LIBS=
LIBS+=$(shell pkg-config --libs libevdev)
LIBS+=-lxdo

SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

lamprey: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

-include $(patsubst %.o,.%.o.d,$(OBJS))

%.o: %.c
	$(CC) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)

clean:
	@rm -rf lamprey
	@rm -rf *.o
	@rm -rf .*.o.d
