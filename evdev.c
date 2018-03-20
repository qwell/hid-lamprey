#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>

#include <libevdev/libevdev.h>

#include "include/settings.h"

#include "include/evdev.h"

struct axis_data {
	int min;
	int max;
};

struct hat_data {
	int min;
	int max;
};

void gamepad_start() {
	struct libevdev *dev_list[8];// = NULL;
	struct libevdev *dev = NULL;
	struct pollfd fds[256];
	int nfds = 0;
	int rc = 1;

	uint key_map[HIGH_KEY - LOW_KEY];
	struct axis_data abs_map[HIGH_AXIS - LOW_AXIS];
	struct hat_data hat_map[HIGH_HAT - LOW_HAT];

	memset(fds, 0, sizeof(fds));

	for (int i = 0; i <= 1; ++i) {
		int code;
		dev = dev_list[i];

		char path[256];
		sprintf(path, "/dev/input/by-path/%s", DEVICE_PATH(i));
		printf("Opening event file %s\n", path);

		nfds++;
		fds[i].events = POLLIN;
		fds[i].fd = open(path, O_RDONLY|O_NONBLOCK);

		rc = libevdev_new_from_fd(fds[i].fd, &dev);
		if (rc < 0) {
			fprintf(stderr, "Failed to init libevdev for %s (%s)\n", path, strerror(-rc));
			continue;
		}

		printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
		printf("Input device ID: bus %#x vendor %#x product %#x\n",
			libevdev_get_id_bustype(dev),
			libevdev_get_id_vendor(dev),
			libevdev_get_id_product(dev));

		printf("\n");

		// Get info about keys
		int nkeys = 0;
		for (code = LOW_KEY; code <= HIGH_KEY; ++code) {
			if (libevdev_has_event_code(dev, EV_KEY, code)) {
				printf("Device has key: %2d - %s\n",
					nkeys, libevdev_event_code_get_name(EV_KEY, code));
				key_map[code - LOW_KEY] = nkeys;
				++nkeys;
			}
		}

		printf("\n");

		// Get info about axes
		for (code = LOW_AXIS; code <= HIGH_AXIS; ++code) {
			if (libevdev_has_event_code(dev, EV_ABS, code)) {
				const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, code);
				printf("Device has absolute axis: %s { %d > %d }\n",
				       libevdev_event_code_get_name(EV_ABS, code),
				       absinfo->minimum, absinfo->maximum);
				struct axis_data axis = {
					.min = absinfo->minimum,
					.max = absinfo->maximum,
				};
				abs_map[code - LOW_AXIS] = axis;
			}
		}

		printf("\n");

		// Get info about hats
		for (code = LOW_HAT; code <= HIGH_HAT; code++) {
			if (libevdev_has_event_code(dev, EV_ABS, code)) {
				const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, code);
				if (absinfo == NULL) {
					continue;
				}

				printf("Device has hat: %s { %d > %d }\n",
				       libevdev_event_code_get_name(EV_ABS, code),
				       absinfo->minimum, absinfo->maximum);
				struct hat_data hat = {
					.min = absinfo->minimum,
					.max = absinfo->maximum,
				};
				hat_map[code - LOW_HAT] = hat;
			}
		}

		printf("\n");

		dev_list[i] = dev;
	}

	// Poll events
	do {
		rc = poll(fds, nfds, 1000);
		if (rc < 0) {
			break;
		}
		if (rc == 0) {
			continue;
		}
		for (int i = 0; i <= nfds; i++) {
			if (fds[i].revents != POLLIN) {
				continue;
			}

			dev = dev_list[i];

			do {
				struct input_event ev;
				rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
				if (rc != 0) {
					break;
				}

				switch (ev.type) {
				case EV_KEY:
					if (ev.code >= LOW_KEY && ev.code <= HIGH_KEY) {
						printf("Key %d %s\n", ev.code, ev.value ? "pressed" : "released");
					}
					break;
				case EV_ABS:
					if (ev.code >= LOW_HAT && ev.code <= HIGH_HAT) {
						struct hat_data hat = hat_map[ev.code - LOW_HAT];
						// Only deal with values outside of the deadzone
						if (abs(ev.value) >= abs(hat.max) * HAT_DEADZONE) {
							// Smooth value with deadzone.
							int value = 0;
							if (ev.value > 0) {
								value = (ev.value - (hat.max * HAT_DEADZONE)) / (1 - HAT_DEADZONE);
							} else if (ev.value < 0) {
								value = (ev.value - (hat.min * HAT_DEADZONE)) / (1 - HAT_DEADZONE);
							}
							printf("Hat %d Value %d\n", ev.code, value);
						}
					} else if (ev.code >= LOW_AXIS && ev.code <= HIGH_AXIS) {
						struct axis_data axis = abs_map[ev.code - LOW_AXIS];
						// Only deal with values outside of the deadzone
						if (abs(ev.value) >= abs(axis.max) * AXIS_DEADZONE) {
							// Smooth value with deadzone.
							int value = 0;
							if (ev.value > 0) {
								value = (ev.value - (axis.max * AXIS_DEADZONE)) / (1 - AXIS_DEADZONE);
							} else if (ev.value < 0) {
								value = (ev.value - (axis.min * AXIS_DEADZONE)) / (1 - AXIS_DEADZONE);
							}
							printf("Axis %d Value %d\n", ev.code, value);
						}
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
			} while (rc == 0);
		}
	} while (rc == 1 || rc == 0 || rc == -EAGAIN);
}

void key_press(uint key, uint value) {
	return;
}

void axis_move(uint axis, int value) {
	return;
}
