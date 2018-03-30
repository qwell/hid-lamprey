/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

#include "shortcut_cb.h"

void hl_controller_change(const char *device, int id, uint8_t type, uint16_t code, int16_t value);

struct button_trigger {
	uint8_t type;
	uint16_t code;
	int16_t triggervalue;
};

struct controller_display_mapping {
	const char *display;
	struct button_trigger buttons[8];
	bool value;
};

struct controller_display {
	const char *name;
	const char *devices[18];
	struct controller_display_mapping mapping[64];
	const char layout[256];
};

struct shortcut {
	const char *name;
	void (*function) ();
	enum shortcut_type {
		simultaneous = 0,
		consecutive = 1
	} type;
	const char *devices[8];
	// I really, really hate this.
	struct button {
		const struct button_trigger *buttons[8];
		int state;
	} *button_list[16];
};

#endif
