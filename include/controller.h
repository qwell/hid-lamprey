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
int hl_controller_scale_range(int curvalue, int curmin, int curmax);

struct button_code {
	uint8_t type;
	uint16_t code;
};

struct button_trigger {
	uint8_t type;
	uint16_t code;
	int16_t trigger_low;
	int16_t trigger_high;
};

struct button_trigger_out {
	uint8_t type;
	uint16_t code;
	int16_t trigger;
};

struct remap {
	struct button_trigger *in;
	struct button_trigger_out *out;
};

struct controller_display_mapping {
	const char *display;
	struct button_trigger buttons[8];
	bool value;
	int16_t realvalue;
};

struct controller_display {
	const char *name;
	char *devices[18];
	struct controller_display_mapping mapping[64];
	const char layout[256];
};


struct shortcut_button {
	struct button_trigger **triggers;
	int trigger_count;
	int state;
};

enum shortcut_type {
	simultaneous = 0,
	consecutive = 1
};

struct shortcut {
	const char *name;
	void (*function) (void *);
	void *args;
	enum shortcut_type type;
	char **devices;
	int device_count;
	struct shortcut_button **buttons;
	int button_count;
};

struct device {
	char *name;
	char *uniqueid;
};

struct codelookup_code {
	char *codestr;
	uint16_t code;
};

struct codelookup {
	char *typestr;
	uint8_t type;
	struct codelookup_code codes[1024];
};
extern struct codelookup codelookups[];
extern int codelookup_count;
extern struct remap **remaps;
extern int remap_count;
extern struct shortcut **shortcuts;
extern int shortcut_count;
extern struct device **devices;
extern int device_count;

#endif
