/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "evdev.h"

// #define AXIS_DEADZONE .2
// #define HAT_DEADZONE 0

#define CONTROLLERS \
	{\
		.name = "SNES",\
		/*.device = "pci-0000:00:06.0-usb-0:2:1.0-event-joystick",*/\
		.device = "pci-0000:03:00.0-usb-0:3:1.0-event-joystick",\
		.mapping = {\
			{'^', {\
				{EV_KEY, BTN_DPAD_UP},\
				{EV_ABS, ABS_HAT0Y, -1},\
				{EV_ABS, ABS_Y, -16834},\
			}},\
			{'v', {\
				{EV_KEY, BTN_DPAD_DOWN},\
				{EV_ABS, ABS_HAT0Y, 1},\
				{EV_ABS, ABS_Y, 16834},\
			}},\
			{'<', {\
				{EV_KEY, BTN_DPAD_LEFT},\
				{EV_ABS, ABS_HAT0X, -1},\
				{EV_ABS, ABS_X, -16834},\
			}},\
			{'>', {\
				{EV_KEY, BTN_DPAD_RIGHT},\
				{EV_ABS, ABS_HAT0X, 1},\
				{EV_ABS, ABS_X, 16834},\
			}},\
			{'L', {{EV_KEY, BTN_TL}}},\
			{'R', {{EV_KEY, BTN_TR}}},\
			{'Y', {{EV_KEY, BTN_NORTH}}},\
			{'B', {{EV_KEY, BTN_SOUTH}}},\
			{'X', {{EV_KEY, BTN_WEST}}},\
			{'A', {{EV_KEY, BTN_EAST}}},\
			{'s', {{EV_KEY, BTN_SELECT}}},\
			{'S', {{EV_KEY, BTN_START}}},\
		},\
		.layout = {\
			" _|^|_  [L][R]   (X)  \n"\
			"|<   >|        (Y) (A)\n"\
			" ‾|v|‾  /s//S/   (B)  "\
		},\
	},

#define CODESWAPS \
	{{EV_KEY, BTN_THUMBL}, {EV_KEY, KEY_1, 1}},\
	{{EV_KEY, BTN_THUMBR}, {EV_KEY, KEY_3, 1}},\
	{{EV_KEY, BTN_SELECT}, {EV_ABS, ABS_X, -1}},\
	{{EV_KEY, BTN_START}, {EV_ABS, ABS_X, 1}},\
	{{EV_KEY, BTN_MODE}, {EV_KEY, KEY_Y}},\
	/*\
	{{EV_ABS, ABS_X, -16834}, {EV_KEY, KEY_A}},\
	{{EV_ABS, ABS_X, 16834}, {EV_KEY, KEY_D}},\
	{{EV_ABS, ABS_Y, -16834}, {EV_KEY, KEY_W}},\
	{{EV_ABS, ABS_Y, 16834}, {EV_KEY, KEY_S}},\
	*/

#define SHORTCUTS \
	{\
		.name = "konami",\
		.function = NULL,\
		.multi_device = false,\
		.type = consecutive,\
		.button_list = {\
			{{\
				{EV_KEY, BTN_DPAD_UP},\
				{EV_ABS, ABS_HAT0Y, -1},\
				{EV_ABS, ABS_Y, -16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_UP},\
				{EV_ABS, ABS_HAT0Y, -1},\
				{EV_ABS, ABS_Y, -16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_DOWN},\
				{EV_ABS, ABS_HAT0Y, 1},\
				{EV_ABS, ABS_Y, 16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_DOWN},\
				{EV_ABS, ABS_HAT0Y, 1},\
				{EV_ABS, ABS_Y, 16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_LEFT},\
				{EV_ABS, ABS_HAT0X, -1},\
				{EV_ABS, ABS_X, -16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_RIGHT},\
				{EV_ABS, ABS_HAT0X, 1},\
				{EV_ABS, ABS_X, 16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_LEFT},\
				{EV_ABS, ABS_HAT0X, -1},\
				{EV_ABS, ABS_X, -16834},\
			}},\
			{{\
				{EV_KEY, BTN_DPAD_RIGHT},\
				{EV_ABS, ABS_HAT0X, 1},\
				{EV_ABS, ABS_X, 16834},\
			}},\
			{{{EV_KEY, BTN_WEST}}},\
			{{{EV_KEY, BTN_EAST}}},\
		},\
	},

#endif
