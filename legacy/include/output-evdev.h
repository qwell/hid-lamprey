/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_OUTPUT_EVDEV_H
#define LAMPREY_OUTPUT_EVDEV_H

#include <sys/poll.h>

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

struct hl_output_evdev {
	struct uinput {
		struct libevdev *dev;
		struct libevdev_uinput *uidev;
	} uinput;
};

void hl_output_evdev_init();
void hl_output_evdev_destroy();
void hl_output_evdev_inject(uint8_t type, uint16_t code, int16_t value);

#endif
