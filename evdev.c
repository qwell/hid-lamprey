#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>

#include <libevdev/libevdev.h>

#include "include/settings.h"

#include "include/evdev.h"

struct key_data {
};

struct axis_data {
	int min;
	int max;
};

struct hat_data {
	int min;
	int max;
};

struct controller_mapping {
	char button;
	int code;
	int triggervalue;
	int value;
};

struct controller {
	char *device;
	struct controller_mapping mapping[64];
	char layout[5][11];
};

struct controller controllers[] = {
	{
		.device = "",
		.mapping = {
			{'^', BTN_DPAD_UP},
			{'^', ABS_HAT0Y, -1},
			{'L', BTN_TL},
			{'R', BTN_TR},
			{'X', BTN_WEST},
			{'<', BTN_DPAD_LEFT},
			{'<', ABS_HAT0X, -1},
			{'>', BTN_DPAD_RIGHT},
			{'>', ABS_HAT0X, 1},
			{'Y', BTN_NORTH},
			{'A', BTN_EAST},
			{'v', BTN_DPAD_DOWN},
			{'v', ABS_HAT0Y, 1},
			{'s', BTN_SELECT},
			{'S', BTN_START},
			{'B', BTN_SOUTH},
		},
		.layout = {
			{" ^  LR  X "},
			{"< >    Y A"},
			{" v  sS  B "},
		},
	}
};

int filter_event_files(const struct dirent *entry)
{
   return strstr(entry->d_name, "-event") != NULL;
}

void hl_evdev_start() {
	const char *filepath = "/dev/input/by-path/";
	struct dirent **filelist;
	int filecount = 0;
	struct libevdev *dev_list[8];
	struct pollfd fds[256];
	int nfds = 0;
	int rc = 1;

	struct key_data key_map[HIGH_KEY - LOW_KEY];
	struct axis_data abs_map[HIGH_AXIS - LOW_AXIS];
	struct hat_data hat_map[HIGH_HAT - LOW_HAT];

	filecount = scandir(filepath, &filelist, filter_event_files, alphasort);
	if (filecount < 0) {
		printf("No input files found.  Cannot continue.\n");
		exit(1);
	}

	memset(fds, 0, sizeof(fds));

	for (int i = 0; i < filecount; ++i) {
		char fullpath[256];

		struct libevdev *dev = dev_list[i];

		printf("Opening event file %s\n", filelist[i]->d_name);

		snprintf(fullpath, sizeof(fullpath), "%s%s", filepath, filelist[i]->d_name);
		fds[i].fd = open(fullpath, O_RDONLY|O_NONBLOCK);
		fds[i].events = POLLIN;
		nfds++;

		rc = libevdev_new_from_fd(fds[i].fd, &dev);
		if (rc < 0) {
			fprintf(stderr, "Failed to init libevdev for %s (%s)\n", filelist[i]->d_name, strerror(-rc));
			continue;
		}
		free(filelist[i]);

		printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
		printf("Input device ID: bus %#x vendor %#x product %#x\n",
			libevdev_get_id_bustype(dev),
			libevdev_get_id_vendor(dev),
			libevdev_get_id_product(dev));

		printf("\n");

		// Get info about keys
		for (int code = LOW_KEY; code <= HIGH_KEY; ++code) {
			if (libevdev_has_event_code(dev, EV_KEY, code)) {
				struct key_data key = {
				};
				printf("Device %d has key: %s\n",
					i, libevdev_event_code_get_name(EV_KEY, code));
				key_map[code - LOW_KEY] = key;
			}
		}

		printf("\n");

		// Get info about axes
		for (int code = LOW_AXIS; code <= HIGH_AXIS; ++code) {
			if (libevdev_has_event_code(dev, EV_ABS, code)) {
				const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, code);
				struct axis_data axis = {
					.min = absinfo->minimum,
					.max = absinfo->maximum,
				};
				printf("Device %d has absolute axis: %s { %d > %d }\n",
				       i, libevdev_event_code_get_name(EV_ABS, code),
				       absinfo->minimum, absinfo->maximum);
				abs_map[code - LOW_AXIS] = axis;
			}
		}

		printf("\n");

		// Get info about hats
		for (int code = LOW_HAT; code <= HIGH_HAT; code++) {
			if (libevdev_has_event_code(dev, EV_ABS, code)) {
				const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, code);
				struct hat_data hat;

				if (absinfo == NULL) {
					continue;
				}

				hat.min = absinfo->minimum;
				hat.max = absinfo->maximum;

				printf("Device %d has hat: %s { %d > %d }\n",
				       i, libevdev_event_code_get_name(EV_ABS, code),
				       absinfo->minimum, absinfo->maximum);
				hat_map[code - LOW_HAT] = hat;
			}
		}

		printf("\n");

		dev_list[i] = dev;
	}

	free(filelist);

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
			struct libevdev *dev = NULL;

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
						__attribute__((__unused__)) struct key_data key = key_map[ev.code - LOW_KEY];
						printf("Key %s %s\n", libevdev_event_code_get_name(EV_KEY, ev.code), ev.value ? "pressed" : "released");
						key_press(ev.code, ev.value);
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
							printf("Hat %s Value %d\n", libevdev_event_code_get_name(EV_ABS, ev.code), value);
							key_press(ev.code, ev.value);
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
							printf("Axis %s Value %d\n", libevdev_event_code_get_name(EV_ABS, ev.code), value);
						}
					}
					break;
				case EV_REL:
					if (ev.code >= LOW_REL && ev.code <= HIGH_REL) {
						printf("Ball %s Value %d\n", libevdev_event_code_get_name(EV_REL, ev.code), ev.value);
					}
					break;
				}
			} while (rc == 0);
		}
	} while (rc == 1 || rc == 0 || rc == -EAGAIN);
}

void key_press(uint key, int value) {
	for (int a = 0; a < sizeof(controllers) / sizeof(struct controller); a++) {
		for (int i = 0; i < sizeof(controllers[a].layout) / (sizeof(controllers[a].layout[0])); i++) {
			if (!strlen(controllers[a].layout[i])) {
				continue;
			}

			for (int j = 0; j < sizeof(controllers[a].layout[i]); j++) {
				int on = 0;

				if (controllers[a].layout[i][j] == ' ' || controllers[a].layout[i][j] == '\0') {
					printf(" ");
					continue;
				}

				for (int k = 0; k < sizeof(controllers[a].mapping) / sizeof(struct controller_mapping); k++) {
					if (controllers[a].layout[i][j] == controllers[a].mapping[k].button) {
						if (key == controllers[a].mapping[k].code) {
							if (controllers[a].mapping[k].triggervalue) {
								controllers[a].mapping[k].value = (value == controllers[a].mapping[k].triggervalue);
							} else {
								controllers[a].mapping[k].value = value;
							}
						}

						on = controllers[a].mapping[k].value;
					}
				}

				if (on) {
					printf("\x1b[31m");
					printf("%c", controllers[a].layout[i][j]);
					printf("\x1b[0m");
				} else {
					printf("%c", controllers[a].layout[i][j]);
				}
			}
			printf("\n");
		}
	}
	return;
}

void axis_move(uint axis, int value) {
	return;
}
