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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/input.h"

hl_thread_t t_evdev;
hl_mutex_t mutex_evdev;
struct hl_evdev *hl_evdev = NULL;

int filter_event_files(const struct dirent *entry)
{
	return !strncmp(entry->d_name, "event", 5);
}

void hl_input_evdev_init() {
	const char *filepath = "/dev/input/";
	struct dirent **filelist;
	int filecount = 0;

	filecount = scandir(filepath, &filelist, filter_event_files, alphasort);
	if (filecount < 0) {
		printf("No input files found.  Cannot continue.\n");
		return;
	}

	hl_mutex_create(&mutex_evdev);
	hl_mutex_lock(&mutex_evdev);
	if (hl_evdev) {
		hl_mutex_unlock(&mutex_evdev);
		return;
	}
	hl_evdev = malloc(sizeof(struct hl_evdev));
	memset(hl_evdev->fds, 0, sizeof(hl_evdev->fds));
	memset(hl_evdev->devices, 0, sizeof(hl_evdev->devices));

	for (int i = 0; i < filecount; ++i) {
		char fullpath[512];
		char uniq[256];
		int rc = 1;

		struct libevdev *dev = hl_evdev->devices[i].dev;

		debug_print("Opening event file %s\n", filelist[i]->d_name);

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
		printf("Input device: %s\n", uniq);

		free(filelist[i]);

		hl_evdev->devices[i].ff_id = -1;

		if (libevdev_has_event_type(dev, EV_KEY)) {
			// Get info about keys
			for (int code = LOW_KEY; code <= HIGH_KEY; ++code) {
				if (libevdev_has_event_code(dev, EV_KEY, code)) {
					struct key_data key = {
					};
					debug_print("Device %d has key: %s\n",
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

					axis.min = absinfo->minimum;
					axis.max = absinfo->maximum;

					debug_print("Device %d has absolute axis: %s { %d > %d }\n",
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

					debug_print("Device %d has hat: %s { %d > %d }\n",
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
				debug_print("Device %d has FF: %s\n", i, libevdev_event_code_get_name(EV_FF, FF_PERIODIC));

				ioctl(hl_evdev->fds[i].fd, EVIOCSFF, &effect);
				hl_evdev->devices[i].ff_id = effect.id;
			}
		}
		debug_print("\n");

		hl_evdev->devices[i].dev = dev;
	}

	free(filelist);

	/* Create emulated uinput device. */
	hl_evdev->uinput.dev = libevdev_new();
	libevdev_set_name(hl_evdev->uinput.dev, "Lamprey Emulated Device");

	/* Emulate all keys in the code table. */
	for (int i = 0; i < codelookup_count / sizeof(*codelookups); i++) {
		struct codelookup emu = codelookups[i];
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

		libevdev_enable_event_type(hl_evdev->uinput.dev, emu.type);
		for (int j = 0; j < sizeof(emu.codes) / sizeof(*emu.codes); j++) {
			libevdev_enable_event_code(hl_evdev->uinput.dev, emu.type, emu.codes[j].code, codedata);
		}
	}

	if (libevdev_uinput_create_from_device(hl_evdev->uinput.dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &hl_evdev->uinput.uidev)) {
		libevdev_free(hl_evdev->uinput.dev);
		printf("Error creating uinput device.\n");
	}

	/* Spawn off a thread to handle evdev polling. */
	hl_thread_create(&t_evdev, hl_input_evdev_poll, NULL);

	hl_mutex_unlock(&mutex_evdev);

	return;
}

void *hl_input_evdev_poll() {
	int rc = 1;

	// Poll events
	do {
		//TODO Avoid locking around the poll.  This is gross.
		hl_mutex_lock(&mutex_evdev);
		rc = poll(hl_evdev->fds, sizeof(hl_evdev->fds) / sizeof(struct pollfd), 1000);
		hl_mutex_unlock(&mutex_evdev);
		if (rc < 0) {
			break;
		}
		if (rc == 0) {
			continue;
		}

		hl_mutex_lock(&mutex_evdev);
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
						hl_mutex_unlock(&mutex_evdev);
						debug_print("Key %s %s\n", libevdev_event_code_get_name(ev.type, ev.code), ev.value ? "pressed" : "released");
						hl_controller_change(libevdev_get_uniq(hl_evdev->devices[i].dev), i, ev.type, ev.code, ev.value);
						hl_mutex_lock(&mutex_evdev);
					}
					break;
				case EV_ABS:
					if (ev.code >= LOW_HAT && ev.code <= HIGH_HAT) {
						struct hat_data hat = hl_evdev->maps.hat_map[ev.code - LOW_HAT];
						int value = hl_controller_scale_range(ev.value, ev.min, ev.max);
						
						hl_mutex_unlock(&mutex_evdev);
						debug_print("Hat %s Value %d\n", libevdev_event_code_get_name(ev.type, ev.code), value);
						hl_controller_change(libevdev_get_uniq(hl_evdev->devices[i].dev), i, ev.type, ev.code, value);
						hl_mutex_lock(&mutex_evdev);
					} else if (ev.code >= LOW_AXIS && ev.code <= HIGH_AXIS) {
						struct axis_data axis = hl_evdev->maps.abs_map[ev.code - LOW_AXIS];
						int value = hl_controller_scale_range(ev.value, ev.min, ev.max);

						hl_mutex_unlock(&mutex_evdev);
						debug_print("Axis %s Value %d\n", libevdev_event_code_get_name(ev.type, ev.code), value);
						hl_controller_change(libevdev_get_uniq(hl_evdev->devices[i].dev), i, ev.type, ev.code, value);
						hl_mutex_lock(&mutex_evdev);
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
		hl_mutex_unlock(&mutex_evdev);
	} while (rc == 1 || rc == 0 || rc == -EAGAIN);

	hl_input_evdev_destroy();

	return NULL;
}

void hl_input_evdev_destroy() {
	hl_mutex_lock(&mutex_evdev);

	if (hl_evdev == NULL) {
		hl_mutex_unlock(&mutex_evdev);
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

	hl_mutex_unlock(&mutex_evdev);

	hl_thread_exit();
}

void hl_input_evdev_inject(int id, uint8_t type, uint16_t code, int16_t value) {
	hl_mutex_lock(&mutex_evdev);
	if (hl_evdev->uinput.uidev != NULL) {
		libevdev_uinput_write_event(hl_evdev->uinput.uidev, type, code, value);
		libevdev_uinput_write_event(hl_evdev->uinput.uidev, EV_SYN, SYN_REPORT, 0);

		if (hl_evdev->devices[id].ff_id != -1) {
			struct input_event play = {
				.type = EV_FF,
				.value = 1,
				.code = hl_evdev->devices[id].ff_id,
			};

			if (write(hl_evdev->fds[id].fd, &play, sizeof(play)) <= 0) {
			}
		}
	}
	hl_mutex_unlock(&mutex_evdev);
}
