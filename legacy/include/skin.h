/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_SKIN_H
#define LAMPREY_SKIN_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlschemas.h>
#include <libxml/xpath.h>

#include "input.h"

struct hl_skin_background {
	char name[64];
	char filename[64];
};

struct hl_skin_button {
	char filename[64];
	char cli_char[2];
	uint8_t type;
	uint16_t code;
	int x;
	int y;
};

struct hl_skin_axis {
	char filename[64];
	char cli_char[2];
	uint8_t type_x;
	uint16_t code_x;
	int x;
	int offset_x;
	int trigger_x;
	uint8_t type_y;
	uint16_t code_y;
	int y;
	int offset_y;
	int trigger_y;
};

struct hl_skin {
	char path[64];
	char name[64];
	char cli_layout[256];
	struct hl_skin_background **backgrounds;
	struct hl_skin_button **buttons;
	struct hl_skin_axis **axes;
	int background_count;
	int button_count;
	int axis_count;
};

extern struct hl_skin **hl_skins;
extern int hl_skin_count;

void hl_skin_load(char *name, char *background);

#endif
