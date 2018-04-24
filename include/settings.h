/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_SETTINGS_H
#define LAMPREY_SETTINGS_H

#if defined(HAVE_XML2)
#include "settings-xml2.h"

#define hl_settings_load(...) hl_settings_xml_load(__VA_ARGS__)
#else
#define hl_settings_load(...)
#endif

// #define AXIS_DEADZONE .2
// #define HAT_DEADZONE 0

#define DEVICE_ROCKCANDY "3/e6f-11f:Rock Candy Gamepad Wired Controller"
#define DEVICE_XBOX "3/45e-2a1:Xbox 360 Wireless Receiver (XBOX)"
#define DEVICE_DINPUT0 "Dinput 0"
#define DEVICE_XINPUT0 "Xinput 0"
#define DEVICE_KEYBOARD "11/1-1:AT Translated Set 2 keyboard"
#define DEVICE_KEYBOARD2 "3/258a-1:SINO WEALTH USB KEYBOARD"

#define CONTROLLER_DISPLAYS \
	{\
		"SNES",\
		{DEVICE_XBOX, DEVICE_ROCKCANDY, DEVICE_DINPUT0, DEVICE_XINPUT0},\
		{\
			{"^", {\
				{EV_KEY, BTN_DPAD_UP},\
				{EV_ABS, ABS_HAT0Y, -1},\
				{EV_ABS, ABS_Y, -16834},\
			}},\
			{"v", {\
				{EV_KEY, BTN_DPAD_DOWN},\
				{EV_ABS, ABS_HAT0Y, 1},\
				{EV_ABS, ABS_Y, 16834},\
			}},\
			{"<", {\
				{EV_KEY, BTN_DPAD_LEFT},\
				{EV_ABS, ABS_HAT0X, -1},\
				{EV_ABS, ABS_X, -16834},\
			}},\
			{">", {\
				{EV_KEY, BTN_DPAD_RIGHT},\
				{EV_ABS, ABS_HAT0X, 1},\
				{EV_ABS, ABS_X, 16834},\
			}},\
			{"L", {{EV_KEY, BTN_TL}}},\
			{"R", {{EV_KEY, BTN_TR}}},\
			{"Y", {{EV_KEY, BTN_WEST}}},\
			{"B", {{EV_KEY, BTN_SOUTH}}},\
			{"X", {{EV_KEY, BTN_NORTH}}},\
			{"A", {{EV_KEY, BTN_EAST}}},\
			{"s", {{EV_KEY, BTN_SELECT}}},\
			{"S", {{EV_KEY, BTN_START}}},\
		},\
		{\
			" _|^|_  [L][R]   (X)  \n"\
			"|<   >|        (Y) (A)\n"\
			" ‾|v|‾  /s//S/   (B)  "\
		},\
	},\
	{\
		"keyboard",\
		{DEVICE_KEYBOARD, DEVICE_KEYBOARD2},\
		{\
			{"W", {{EV_KEY, KEY_W}}},\
			{"A", {{EV_KEY, KEY_A}}},\
			{"S", {{EV_KEY, KEY_S}}},\
			{"D", {{EV_KEY, KEY_D}}},\
		},\
		{\
			"   [W]   \n"\
			"[A][S][D]"\
		},\
	},

#endif
