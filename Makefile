CC=gcc
CFLAGS=`pkg-config --cflags libevdev`
LIBS=`pkg-config --libs libevdev`

%.o: %.c
	echo $(CFLAGS)
	$(CC) -c -o $@ $< $(CFLAGS)

gamepad: gamepad.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
