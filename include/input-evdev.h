/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_INPUT_EVDEV_H
#define LAMPREY_INPUT_EVDEV_H

#include <sys/poll.h>

#include <libevdev/libevdev.h>

extern hl_thread_t t_input_evdev;
extern hl_mutex_t mutex_input_evdev;
extern struct hl_input_evdev *hl_input_evdev;

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

struct hl_input_evdev {
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

void hl_input_evdev_init();
void hl_input_evdev_destroy();
void *hl_input_evdev_poll();

#endif
