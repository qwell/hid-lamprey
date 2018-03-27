/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef _EVDEV_H
#define _EVDEV_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/poll.h>

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#include "evdev-codetable.h"

extern pthread_mutex_t mutex_evdev;

/* For list of codes, see
 * https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
 */

#define LOW_KEY KEY_ESC
#define HIGH_KEY KEY_MAX

#define LOW_AXIS ABS_X
#define HIGH_AXIS ABS_BRAKE

#define LOW_HAT ABS_HAT0X
#define HIGH_HAT ABS_HAT3Y

#define LOW_REL REL_X
#define HIGH_REL REL_MAX

struct button_mapping {
	uint8_t type;
	uint16_t code;
	int16_t triggervalue;
};

struct controller_mapping {
	char display;
	struct button_mapping buttons[8];
	bool value;
};

struct controller {
	char *name;
	char *device;
	struct controller_mapping mapping[64];
	char layout[256];
};

struct codelookup {
	char *name;
	uint8_t type;
	uint16_t code;
};

enum shortcut_type {
	simultaneous = 0,
	consecutive = 1
};

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

struct hl_evdev {
	struct uinput {
		struct libevdev *dev;
		struct libevdev_uinput *uidev;
	} uinput;
	struct devices {
		struct libevdev *dev;
		int16_t ff_id;
	} devices[256];
	struct pollfd fds[256];
	struct maps {
		struct key_data key_map[HIGH_KEY - LOW_KEY];
		struct axis_data abs_map[HIGH_AXIS - LOW_AXIS];
		struct hat_data hat_map[HIGH_HAT - LOW_HAT];
	} maps;
};

struct shortcut {
	const char *name;
	void (*function) ();
	enum shortcut_type type;
	const char *device;
	struct button {
		struct button_mapping buttons[8];
	} button_list[16];
};

void *hl_evdev_init();
void *hl_evdev_poll(void *hl_evdev);

#endif
