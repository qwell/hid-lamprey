CC=gcc
CFLAGS=-Wall $(shell pkg-config --cflags libevdev)
LIBS=$(shell pkg-config --libs libevdev)
MAKE_DEPS=-MD -MT $@ -MF .$(subst /,_,$@).d -MP

SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

gamepad: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

-include $(patsubst %.o,.%.o.d,$(OBJS))

%.o: %.c
	$(CC) -o $@ -c $< $(MAKE_DEPS) $(CFLAGS)

clean:
	@rm -rf gamepad
	@rm -rf *.o
	@rm -rf .*.o.d
