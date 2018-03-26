#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>

#include "include/lamprey.h"

#include "include/evdev.h"

struct controller controllers[] = {
	CONTROLLERS
};

struct codeswap {
	struct button_mapping in;
	struct button_mapping out;
} codeswaps[] = {
	CODESWAPS
};

const struct codelookup codelookup[] = {
	CODETABLE
};

void key_press(struct hl_evdev *hl_evdev, const char *device, uint8_t type, uint16_t key, int16_t value);

int filter_event_files(const struct dirent *entry)
{
   return strstr(entry->d_name, "-event") != NULL;
}

void *hl_evdev_init() {
	const char *filepath = "/dev/input/by-path/";
	struct dirent **filelist;
	int filecount = 0;
	struct hl_evdev *hl_evdev = malloc(sizeof(struct hl_evdev));

	filecount = scandir(filepath, &filelist, filter_event_files, alphasort);
	if (filecount < 0) {
		printf("No input files found.  Cannot continue.\n");
		exit(1);
	}

	memset(hl_evdev->fds, 0, sizeof(hl_evdev->fds));

	for (int i = 0; i < filecount; ++i) {
		char fullpath[256];
		int rc = 1;

		struct libevdev *dev = hl_evdev->dev_list[i];

		printf("Opening event file %s\n", filelist[i]->d_name);

		snprintf(fullpath, sizeof(fullpath), "%s%s", filepath, filelist[i]->d_name);
		hl_evdev->fds[i].fd = open(fullpath, O_RDONLY|O_NONBLOCK);
		hl_evdev->fds[i].events = POLLIN;
		hl_evdev->nfds++;

		rc = libevdev_new_from_fd(hl_evdev->fds[i].fd, &dev);
		if (rc < 0) {
			fprintf(stderr, "Failed to init libevdev for %s (%s)\n", filelist[i]->d_name, strerror(-rc));
			continue;
		}
		libevdev_set_uniq(dev, filelist[i]->d_name);

		free(filelist[i]);

		printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
		printf("Input device ID: bus %#x vendor %#x product %#x\n",
			libevdev_get_id_bustype(dev),
			libevdev_get_id_vendor(dev),
			libevdev_get_id_product(dev));


		if (libevdev_has_event_type(dev, EV_KEY)) {
			// Get info about keys
			for (int code = LOW_KEY; code <= HIGH_KEY; ++code) {
				if (libevdev_has_event_code(dev, EV_KEY, code)) {
					struct key_data key = {
					};
					printf("Device %d has key: %s\n",
						i, libevdev_event_code_get_name(EV_KEY, code));
					hl_evdev->maps.key_map[code - LOW_KEY] = key;
				}
			}
		}

		if (libevdev_has_event_type(dev, EV_ABS)) {
			// Get info about axes
			for (int code = LOW_AXIS; code <= HIGH_AXIS; ++code) {
				if (libevdev_has_event_code(dev, EV_ABS, code)) {
					const struct input_absinfo *absinfo = libevdev_get_abs_info(dev, code);
					struct axis_data axis;

					if (absinfo == NULL) {
						continue;
					}

					axis.min = absinfo->minimum,
					axis.max = absinfo->maximum,

					printf("Device %d has absolute axis: %s { %d > %d }\n",
					       i, libevdev_event_code_get_name(EV_ABS, code),
					       absinfo->minimum, absinfo->maximum);
					hl_evdev->maps.abs_map[code - LOW_AXIS] = axis;
				}
			}

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
					hl_evdev->maps.hat_map[code - LOW_HAT] = hat;
				}
			}
		}
		printf("\n");

		hl_evdev->dev_list[i] = dev;
	}

	free(filelist);

	/* Create emulated uinput device. */
	hl_evdev->uinput.dev = libevdev_new();
	libevdev_set_name(hl_evdev->uinput.dev, "Lamprey Emulated Device");
	libevdev_enable_event_type(hl_evdev->uinput.dev, EV_KEY);
	libevdev_enable_event_type(hl_evdev->uinput.dev, EV_ABS);
	libevdev_enable_event_type(hl_evdev->uinput.dev, EV_REL);

	/* Emulate all keys in the code table. */
	for (int i = 0; i <= sizeof(codelookup) / sizeof(struct codelookup); i++) {
		struct codelookup emu = codelookup[i];
		void *codedata = NULL;
		switch (emu.type) {
		case EV_ABS:
			codedata = calloc(1, sizeof(struct input_absinfo));
			((struct input_absinfo *)codedata)->value = 0;
			((struct input_absinfo *)codedata)->minimum = -1;
			((struct input_absinfo *)codedata)->maximum = 1;
			((struct input_absinfo *)codedata)->fuzz = 0;
			((struct input_absinfo *)codedata)->flat = 0;
			((struct input_absinfo *)codedata)->resolution = 0;
			break;
		}
		libevdev_enable_event_code(hl_evdev->uinput.dev, emu.type, emu.code, codedata);
	}

	if (libevdev_uinput_create_from_device(hl_evdev->uinput.dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &hl_evdev->uinput.uidev)) {
		libevdev_free(hl_evdev->uinput.dev);
		printf("Error creating uinput device.\n");
	}

	return hl_evdev;
}

void *hl_evdev_poll(void *ptr) {
	struct hl_evdev *hl_evdev = (struct hl_evdev *)ptr;
	int rc = 1;

	// Poll events
	do {
		rc = poll(hl_evdev->fds, hl_evdev->nfds, 1000);
		if (rc < 0) {
			break;
		}
		if (rc == 0) {
			continue;
		}
		for (int i = 0; i <= hl_evdev->nfds; i++) {
			struct libevdev *dev = NULL;

			if (hl_evdev->fds[i].revents != POLLIN) {
				continue;
			}

			dev = hl_evdev->dev_list[i];

			do {
				struct input_event ev;
				rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
				if (rc != 0) {
					break;
				}

				switch (ev.type) {
				case EV_KEY:
					if (ev.code >= LOW_KEY && ev.code <= HIGH_KEY) {
						__attribute__((__unused__)) struct key_data key = hl_evdev->maps.key_map[ev.code - LOW_KEY];
						debug_print("Key %s %s\n", libevdev_event_code_get_name(ev.type, ev.code), ev.value ? "pressed" : "released");
						key_press(hl_evdev, libevdev_get_uniq(dev), ev.type, ev.code, ev.value);
					}
					break;
				case EV_ABS:
					if (ev.code >= LOW_HAT && ev.code <= HIGH_HAT) {
						struct hat_data hat = hl_evdev->maps.hat_map[ev.code - LOW_HAT];
						/* Find midpoint of possible range.
						 * 0 -> 255 = 128
						 * -32768 -> 32767 = 0
						 */
						int zeroish = hat.min + hat.max;
						/* Make it even. */
						zeroish = zeroish % 2 ? zeroish : zeroish + 1;
						/* Div 2 to get the midpoint. */
						int relzero = zeroish ? round(zeroish / 2) : zeroish;

						int rangesize = (hat.max - hat.min);
						int deadsize = ((rangesize % 2 ? rangesize : rangesize + 1) / 2) * HAT_DEADZONE;

						if (ev.value >= relzero + deadsize || ev.value <= relzero - deadsize) {
							int value = 0;
							//Scale from min > relzero +/- deadsize > max.
							if (ev.value >= relzero + deadsize) {
								value = (hat.max - relzero) * (ev.value - (relzero + deadsize)) / (hat.max - (relzero + deadsize)) + relzero;
							} else if (ev.value <= relzero - deadsize) {
								value = (relzero - hat.min) * (ev.value - hat.min) / ((relzero - deadsize) - hat.min) + hat.min;
							}
							debug_print("Hat %s Value %d\n", libevdev_event_code_get_name(ev.type, ev.code), value);
							key_press(hl_evdev, libevdev_get_uniq(dev), ev.type, ev.code, value);
						} else {
							//TODO Do we just never send a zero event?
						}
					} else if (ev.code >= LOW_AXIS && ev.code <= HIGH_AXIS) {
						struct axis_data axis = hl_evdev->maps.abs_map[ev.code - LOW_AXIS];
						/* Find midpoint of possible range.
						 * 0 -> 255 = 128
						 * -32768 -> 32767 = 0
						 */
						int zeroish = axis.min + axis.max;
						/* Make it even. */
						zeroish = zeroish % 2 ? zeroish : zeroish + 1;
						/* Div 2 to get the midpoint. */
						int relzero = zeroish ? round(zeroish / 2) : zeroish;

						int rangesize = (axis.max - axis.min);
						int deadsize = ((rangesize % 2 ? rangesize : rangesize + 1) / 2) * AXIS_DEADZONE;

						if (ev.value >= relzero + deadsize || ev.value <= relzero - deadsize) {
							int value = 0;
							//Scale from min > relzero +/- deadsize > max.
							if (ev.value >= relzero + deadsize) {
								value = (axis.max - relzero) * (ev.value - (relzero + deadsize)) / (axis.max - (relzero + deadsize)) + relzero;
							} else if (ev.value <= relzero - deadsize) {
								value = (relzero - axis.min) * (ev.value - axis.min) / ((relzero - deadsize) - axis.min) + axis.min;
							}
							debug_print("Axis %s Value %d\n", libevdev_event_code_get_name(ev.type, ev.code), value);
							key_press(hl_evdev, libevdev_get_uniq(dev), ev.type, ev.code, value);
						} else {
							//TODO Do we just never send a zero event?
						}
					}
					break;
				case EV_REL:
					if (ev.code >= LOW_REL && ev.code <= HIGH_REL) {
						debug_print("Ball %s Value %d\n", libevdev_event_code_get_name(ev.type, ev.code), ev.value);
					}
					break;
				}
			} while (rc == 0);
		}
	} while (rc == 1 || rc == 0 || rc == -EAGAIN);

	if (hl_evdev->uinput.uidev != NULL) {
		libevdev_uinput_destroy(hl_evdev->uinput.uidev);
	}
	if (hl_evdev->uinput.dev != NULL) {
		libevdev_free(hl_evdev->uinput.dev);
	}

	pthread_exit(NULL);
}

void key_press(struct hl_evdev *hl_evdev, const char *device, uint8_t type, uint16_t key, int16_t value) {
	for (int a = 0; a < sizeof(controllers) / sizeof(struct controller); a++) {
		if (strcmp(device, controllers[a].device)) {
			continue;
		}

		for (int j = 0; j < sizeof(controllers[a].layout); j++) {
			int on = 0;

			if (controllers[a].layout[j] == '\0') {
				break;
			}

			if (controllers[a].layout[j] == ' ') {
				printf(" ");
				continue;
			}

			for (int k = 0; k < sizeof(controllers[a].mapping) / sizeof(struct controller_mapping); k++) {
				if (controllers[a].layout[j] == controllers[a].mapping[k].display) {
					for (int l = 0; l < sizeof(controllers[a].mapping[k].buttons) / sizeof(struct button_mapping); l++) {
						if (key == controllers[a].mapping[k].buttons[l].code && type == controllers[a].mapping[k].buttons[l].type) {
							if (controllers[a].mapping[k].buttons[l].triggervalue < 0) {
								controllers[a].mapping[k].value = (value <= controllers[a].mapping[k].buttons[l].triggervalue);
							} else if (controllers[a].mapping[k].buttons[l].triggervalue > 0) {
								controllers[a].mapping[k].value = (value >= controllers[a].mapping[k].buttons[l].triggervalue);
							} else {
								controllers[a].mapping[k].value = value ? 1 : 0;
							}
						}
					}

					on = controllers[a].mapping[k].value;
				}
			}

			if (on) {
				printf("\e[31m%c\e[39m", controllers[a].layout[j]);
			} else {
				printf("%c", controllers[a].layout[j]);
			}
		}
		printf("\n");
	}

	if (hl_evdev->uinput.uidev != NULL) {
		for (int i = 0; i <= sizeof(codeswaps) / sizeof(struct codeswap); i++) {
			struct codeswap emu = codeswaps[i];
			if (type == emu.in.type && key == emu.in.code) {
				int emuvalue = 0;
				if (emu.in.triggervalue < 0) {
					emuvalue = (value <= emu.in.triggervalue);
				} else if (emu.in.triggervalue > 0) {
					emuvalue = (value >= emu.in.triggervalue);
				} else {
					emuvalue = value ? 1 : 0;
				}
				if (emuvalue && emu.out.triggervalue) {
					emuvalue = emu.out.triggervalue;
				}

				debug_print("Code %s (%d) converted to %s (%d)\n",
					libevdev_event_code_get_name(emu.in.type, emu.in.code), value,
					libevdev_event_code_get_name(emu.out.type, emu.out.code), emuvalue);
				libevdev_uinput_write_event(hl_evdev->uinput.uidev, emu.out.type, emu.out.code, emuvalue);
				libevdev_uinput_write_event(hl_evdev->uinput.uidev, EV_SYN, SYN_REPORT, 0);
			}
		}
	}
	return;
}
