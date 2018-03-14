#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <libevdev/libevdev.h>

#include "include/defaults.h"
#include "include/settings.h"
#include "include/xdo.h"

#define LOW_BTN BTN_MISC
#define HIGH_BTN BTN_THUMBR

#define LOW_AXIS ABS_X
#define HIGH_AXIS ABS_BRAKE

#define LOW_HAT ABS_HAT0X
#define HIGH_HAT ABS_HAT3Y

#ifndef __linux__
#error "No.  Go get a real OS and try again."
#endif

int main () {
	xdo_init();

	int i;
	struct libevdev *dev = NULL;
	int fd;
	int rc = 1;

	char *path = "/dev/input/by-path/" DEVICE_PATH;
	printf("Opening event file %s\n", path);

	fd = open(path, O_RDONLY|O_NONBLOCK);
	rc = libevdev_new_from_fd(fd, &dev);
	if (rc < 0) {
		fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
		exit(1);
	}
	printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
	printf("Input device ID: bus %#x vendor %#x product %#x\n",
		libevdev_get_id_bustype(dev),
		libevdev_get_id_vendor(dev),
		libevdev_get_id_product(dev));

	printf("\n");

	// Get info about buttons
	int nbuttons = 0;
	uint key_map[HIGH_BTN - LOW_BTN];
	for (i = LOW_BTN; i <= HIGH_BTN; ++i) {
		if (libevdev_has_event_code(dev, EV_KEY, i)) {
			printf("Joystick has button: %2d - %s\n",
				nbuttons, libevdev_event_code_get_name(EV_KEY, i));
			key_map[i - LOW_BTN] = nbuttons;
			++nbuttons;
		}
	}

	printf("\n");

	// Get info about axes
	int naxes = 0;
	uint abs_map[HIGH_AXIS - LOW_AXIS];
	for (i = LOW_AXIS; i <= HIGH_AXIS; ++i) {
		if (libevdev_has_event_code(dev, EV_ABS, i)) {
			const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, i);
			printf("Joystick has absolute axis: %2d - %s { %d > %d }\n",
			       naxes, libevdev_event_code_get_name(EV_ABS, i),
			       absinfo->minimum, absinfo->maximum);
			abs_map[i - LOW_AXIS] = naxes;
			++naxes;
		}
	}

	printf("\n");

	// Get info about hats
	int nhats = 0;
	uint hat_map[HIGH_HAT - LOW_HAT];
	for (i = LOW_HAT; i <= HIGH_HAT; i++) {
		if (libevdev_has_event_code(dev, EV_ABS, i)) {
			const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, i);
			if (absinfo == NULL) {
				continue;
			}

			printf("Joystick has hat: %2d - %s { %d > %d }\n",
			       nhats, libevdev_event_code_get_name(EV_ABS, i),
			       absinfo->minimum, absinfo->maximum);
			hat_map[i - LOW_HAT] = nhats;
			++nhats;
		}
	}

	printf("\n");

	// Poll events
	do {
		struct input_event ev;
		rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
		if (rc == 0) {
			switch (ev.type) {
			case EV_KEY:
				if (ev.code >= LOW_BTN && ev.code <= HIGH_BTN) {
					printf("Button %d %s\n", key_map[ev.code - LOW_BTN], ev.value ? "pressed" : "released");
				}
				break;
			case EV_ABS:
				if (ev.code >= LOW_HAT && ev.code <= HIGH_HAT) {
					ev.code -= LOW_HAT;
					printf("Hat %d Value %d\n", hat_map[ev.code], ev.value);
				} else if (ev.code >= LOW_AXIS && ev.code <= HIGH_AXIS) {
					printf("Axis %d Value %d\n", abs_map[ev.code], ev.value);
				}
				break;
			case EV_REL:
				switch (ev.code) {
				case REL_X:
				case REL_Y:
					ev.code -= REL_X;
					printf("Ball %d Axis %d Value %d\n", ev.code / 2, ev.code % 2, ev.value);
					break;
				default:
					break;
				}
				break;
			}
		}
	} while (rc == 1 || rc == 0 || rc == -EAGAIN);
}

void button_press(uint button, uint value) {
	return;
}

void axis_move(uint axis, int value) {
	return;
}
