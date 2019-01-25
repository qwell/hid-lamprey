/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/output.h"

void hl_output_evdev_init() {
	hl_output_evdev = malloc(sizeof(struct hl_output_evdev));

	/* Create emulated uinput device. */
	hl_output_evdev->uinput.dev = libevdev_new();
	libevdev_set_name(hl_output_evdev->uinput.dev, "Lamprey Emulated Device");

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

		libevdev_enable_event_type(hl_output_evdev->uinput.dev, emu.type);
		for (int j = 0; j < sizeof(emu.codes) / sizeof(*emu.codes); j++) {
			libevdev_enable_event_code(hl_output_evdev->uinput.dev, emu.type, emu.codes[j].code, codedata);
		}
	}

	if (libevdev_uinput_create_from_device(hl_output_evdev->uinput.dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &hl_output_evdev->uinput.uidev)) {
		libevdev_free(hl_output_evdev->uinput.dev);
		printf("Error creating uinput device.\n");
	}

}

void hl_output_evdev_destroy() {
	if (hl_input_evdev->uinput.uidev != NULL) {
		libevdev_uinput_destroy(hl_input_evdev->uinput.uidev);
	}

	if (hl_input_evdev->uinput.dev != NULL) {
		libevdev_free(hl_input_evdev->uinput.dev);
	}


	free(hl_output_evdev);
	hl_output_evdev = NULL;
}

void hl_output_evdev_inject(uint8_t type, uint16_t code, int16_t value) {
	if (hl_output_evdev->uinput.uidev != NULL) {
		libevdev_uinput_write_event(hl_output_evdev->uinput.uidev, type, code, value);
		libevdev_uinput_write_event(hl_output_evdev->uinput.uidev, EV_SYN, SYN_REPORT, 0);
	}
}

void hl_output_evdev_test() {
/*
	if (hl_output_evdev->devices[id].ff_id != -1) {
		struct input_event play = {
			.type = EV_FF,
		.value = 1,
			.code = hl_output_evdev->devices[id].ff_id,
		};


		if (write(hl_output_evdev->fds[id].fd, &play, sizeof(play)) <= 0) {
		}
	}
*/
}
