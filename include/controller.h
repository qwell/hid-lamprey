/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_CONTROLLER_H
#define LAMPREY_CONTROLLER_H

#include "input.h"
#include "shortcut_cb.h"

void hl_controller_change(const char *device, int id, uint8_t type, uint16_t code, int16_t value);
struct button_code *hl_controller_get_code_by_name(char *type, char *name);

struct button_code {
	uint8_t type;
	uint16_t code;
};

struct button_trigger {
	uint8_t type;
	uint16_t code;
	int16_t triggervalue;
};

struct remap {
	struct button_trigger in;
	struct button_trigger out;
};

struct remapptr {
	struct button_trigger *in;
	struct button_trigger *out;
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
	void *args;
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

struct codelookup {
	const char *typestr;
	const char *codestr;
	const uint8_t type;
	const uint16_t code;
};

struct codelookupnew {
	const char *typestr;
	const uint8_t type;
	const struct codes {
		const char *codestr;
		const uint16_t code;
	} codes[1024];
};
extern struct codelookup codelookups[];
extern int codelookup_count;
extern struct codelookupnew codelookupnews[];
extern int codelookupnew_count;

#endif
