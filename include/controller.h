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
#include "skin.h"

void hl_controller_raw(const char *device, const char *rawname, int value);
void hl_controller_change(const char *device, int id, uint8_t type, uint16_t code, int16_t value);
struct button_code *hl_controller_get_code_by_name(char *type, char *name);
int hl_controller_scale_range(int curvalue, int curmin, int curmax);

struct button_code {
	uint8_t type;
	uint16_t code;
};

struct button_state {
	uint8_t type;
	uint16_t code;
	int16_t value;
};

struct controller {
	struct button_state **buttons;
	int button_count;
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

struct input_mapping {
	char *device;
	char *rawname;
	bool builtin;
	int maptype;
	int mapcode;
	int mapvalue;
};

struct emulation {
	struct button_trigger *in;
	struct button_trigger_out *out;
};


struct shortcut_button {
	uint8_t type;
	uint16_t code;
	int16_t trigger_low;
	int16_t trigger_high;
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
	enum code_category category;
	char *description;
};

struct codelookup {
	char *typestr;
	uint8_t type;
	char *description;
	struct codelookup_code codes[1024];
};
extern struct codelookup codelookups[];
extern int codelookup_count;

extern struct input_mapping **input_mappings;
extern int input_mapping_count;

extern struct emulation **emulations;
extern int emulation_count;

extern struct shortcut **shortcuts;
extern int shortcut_count;

extern struct device **devices;
extern int device_count;

#endif
