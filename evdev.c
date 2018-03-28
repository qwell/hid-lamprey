/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

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

pthread_t t_evdev;
pthread_mutex_t mutex_evdev = PTHREAD_MUTEX_INITIALIZER;
struct hl_evdev *hl_evdev = NULL;

struct controller_display controller_displays[] = {
	CONTROLLER_DISPLAYS
};

const struct codeswap {
	struct button_trigger in;
	struct button_trigger out;
} codeswaps[] = {
	CODESWAPS
};

const struct codelookup codelookup[] = {
	CODETABLE
};

const struct shortcut shortcuts[] = {
	SHORTCUTS
};

void key_press(int id, uint8_t type, uint16_t key, int16_t value);

int filter_event_files(const struct dirent *entry)
{
	return !strncmp(entry->d_name, "event", 5);
}

void hl_evdev_init() {
	const char *filepath = "/dev/input/";
	struct dirent **filelist;
	int filecount = 0;

	filecount = scandir(filepath, &filelist, filter_event_files, alphasort);
	if (filecount < 0) {
		printf("No input files found.  Cannot continue.\n");
		return;
	}

	pthread_mutex_lock(&mutex_evdev);
	if (hl_evdev) {
		pthread_mutex_unlock(&mutex_evdev);
		return;
	}
	hl_evdev = malloc(sizeof(struct hl_evdev));
	memset(hl_evdev->fds, 0, sizeof(hl_evdev->fds));
	memset(hl_evdev->devices, 0, sizeof(hl_evdev->devices));

	for (int i = 0; i < filecount; ++i) {
		char fullpath[256];
		char uniq[256];
		int rc = 1;

		struct libevdev *dev = hl_evdev->devices[i].dev;

		printf("Opening event file %s\n", filelist[i]->d_name);

		snprintf(fullpath, sizeof(fullpath), "%s%s", filepath, filelist[i]->d_name);
		hl_evdev->fds[i].fd = open(fullpath, O_RDWR|O_NONBLOCK);
		hl_evdev->fds[i].events = POLLIN;

		rc = libevdev_new_from_fd(hl_evdev->fds[i].fd, &dev);
		if (rc < 0) {
			fprintf(stderr, "Failed to init libevdev for %s (%s)\n", filelist[i]->d_name, strerror(-rc));
			continue;
		}

		snprintf(uniq, sizeof(uniq), "%x/%x-%x:%s",
			libevdev_get_id_bustype(dev),
			libevdev_get_id_vendor(dev),
			libevdev_get_id_product(dev),
			libevdev_get_name(dev));

		libevdev_set_uniq(dev, uniq);
		printf("Input device: \"%s\"\n", uniq);

		free(filelist[i]);

		hl_evdev->devices[i].ff_id = -1;

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

		if (libevdev_has_event_type(dev, EV_FF)) {
			if (libevdev_has_event_code(dev, EV_FF, FF_PERIODIC)) {
				struct ff_effect effect = {
					.id = -1,
					.type = FF_PERIODIC,
					.u.periodic.waveform = FF_SINE,
					.u.periodic.magnitude = 0x4000,
					.direction = 0x4000,
					.replay.length = 100,
				};
				printf("Device %d has FF: %s\n", i, libevdev_event_code_get_name(EV_FF, FF_PERIODIC));

				ioctl(hl_evdev->fds[i].fd, EVIOCSFF, &effect);
				hl_evdev->devices[i].ff_id = effect.id;
			}
		}
		printf("\n");

		hl_evdev->devices[i].dev = dev;
	}

	free(filelist);

	/* Create emulated uinput device. */
	hl_evdev->uinput.dev = libevdev_new();
	libevdev_set_name(hl_evdev->uinput.dev, "Lamprey Emulated Device");
	libevdev_enable_event_type(hl_evdev->uinput.dev, EV_KEY);
	libevdev_enable_event_type(hl_evdev->uinput.dev, EV_ABS);
	libevdev_enable_event_type(hl_evdev->uinput.dev, EV_REL);

	/* Emulate all keys in the code table. */
	for (int i = 0; i < sizeof(codelookup) / sizeof(*codelookup); i++) {
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

	/* Spawn off a thread to handle evdev polling. */
	pthread_create(&t_evdev, NULL, hl_evdev_poll, NULL);

	pthread_mutex_unlock(&mutex_evdev);

	return;
}

void *hl_evdev_poll() {
	int rc = 1;

	// Poll events
	do {
		//TODO Avoid locking around the poll.  This is gross.
		pthread_mutex_lock(&mutex_evdev);
		rc = poll(hl_evdev->fds, sizeof(hl_evdev->fds) / sizeof(struct pollfd), 1000);
		pthread_mutex_unlock(&mutex_evdev);
		if (rc < 0) {
			break;
		}
		if (rc == 0) {
			continue;
		}

		pthread_mutex_lock(&mutex_evdev);
		for (int i = 0; i < sizeof(hl_evdev->devices) / sizeof(*hl_evdev->devices); i++) {
			struct libevdev *dev = NULL;

			if (hl_evdev->fds[i].revents != POLLIN) {
				continue;
			}

			dev = hl_evdev->devices[i].dev;

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
						key_press(i, ev.type, ev.code, ev.value);
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
							key_press(i, ev.type, ev.code, value);
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
							key_press(i, ev.type, ev.code, value);
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
		pthread_mutex_unlock(&mutex_evdev);
	} while (rc == 1 || rc == 0 || rc == -EAGAIN);

	hl_evdev_destroy();

	return NULL;
}

void hl_evdev_destroy() {
	pthread_mutex_lock(&mutex_evdev);

	if (hl_evdev == NULL) {
		pthread_mutex_unlock(&mutex_evdev);
		return;
	}

	for (int i = 0; i < sizeof(hl_evdev->devices) / sizeof(*hl_evdev->devices); i++) {
		if (hl_evdev->devices[i].dev != NULL) {
			libevdev_free(hl_evdev->devices[i].dev);
		}
	}

	if (hl_evdev->uinput.uidev != NULL) {
		libevdev_uinput_destroy(hl_evdev->uinput.uidev);
	}

	if (hl_evdev->uinput.dev != NULL) {
		libevdev_free(hl_evdev->uinput.dev);
	}

	free(hl_evdev);
	hl_evdev = NULL;

	pthread_mutex_unlock(&mutex_evdev);

	pthread_exit(NULL);
}

void key_press(int id, uint8_t type, uint16_t key, int16_t value) {
	const char *device = libevdev_get_uniq(hl_evdev->devices[id].dev);

	for (int i = 0; i < sizeof(controller_displays) / sizeof(*controller_displays); i++) {
		struct controller_display *controller = &controller_displays[i];
		int usedevice = 0;

		char pressed[256] = {0};

		for (int j = 0; j < sizeof(controller->devices) / sizeof(*controller->devices); j++) {
			if (!controller->devices[j]) {
				if (j == 0) {
					usedevice = 1;
				}
				break;
			}
			if (!strcmp(device, controller->devices[j])) {
				usedevice = 1;
				break;
			}
		}
		if (!usedevice) {
			continue;
		}

		for (int j = 0; j < sizeof(controller->mapping) / sizeof(*controller->mapping); j++) {
			struct controller_display_mapping *mapping = &controller->mapping[j];

			for (int k = 0; k < sizeof(mapping->buttons) / sizeof(*mapping->buttons); k++) {
				const struct button_trigger *button = &mapping->buttons[k];

				if (key == button->code && type == button->type) {
					/* Things may not work properly if you have multiple buttons
					 * assigned to a mapping that are concurrently triggered.
					 */
					if (button->triggervalue < 0) {
						mapping->value = (value <= button->triggervalue);
					} else if (button->triggervalue > 0) {
						mapping->value = (value >= button->triggervalue);
					} else {
						mapping->value = value ? 1 : 0;
					}
				}

			}

			if (mapping->value && !strchr(pressed, mapping->display)) {
				strncat(pressed, &mapping->display, 1);
			}
		}

		printf("\n");
		for (int j = 0; j < sizeof(controller->layout); j++) {
			char layout_char = controller->layout[j];

			if (layout_char == '\0') {
				break;
			}

			if (strstr(pressed, &layout_char)) {
				printf("\e[31m%c\e[39m", layout_char);
			} else {
				printf("%c", layout_char);
			}
		}
		printf("\n");
	}

/* TODO Do something with the shortcuts.
	for (int i = 0; i < sizeof(shortcuts) / sizeof(*shortcuts); i++) {
		const struct shortcut *shortcut = &shortcuts[i];
		for (int j = 0; j < sizeof(shortcut->button_list) / sizeof(*shortcut->button_list); j++) {
			const struct button *button = &shortcut->button_list[j];
			for (int k = 0; k < sizeof(button->buttons) / sizeof(*button->buttons); k++) {
				const struct button_trigger *map = &button->buttons[k];
				if (map->type != 0) {
					printf("Button %d (%d) [%d]\n", map->code, map->type, map->triggervalue);
				}
			}
		}
	}
*/

	if (hl_evdev->uinput.uidev != NULL) {
		for (int i = 0; i < sizeof(codeswaps) / sizeof(*codeswaps); i++) {
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

				if (hl_evdev->devices[id].ff_id != -1) {
					struct input_event play = {
						.type = EV_FF,
						.value = 1,
						.code = hl_evdev->devices[id].ff_id,
					};

					write(hl_evdev->fds[id].fd, &play, sizeof(play));
				}
			}
		}
	}
	return;
}
