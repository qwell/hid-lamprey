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

#if defined(HAVE_XML2)
#include "settings-xml2.h"

#define hl_settings_load(...) hl_settings_xml_load(__VA_ARGS__)
#endif

// #define AXIS_DEADZONE .2
// #define HAT_DEADZONE 0

#define DEVICE_ROCKCANDY "3/e6f-11f:Rock Candy Gamepad Wired Controller"
#define DEVICE_XBOX "3/45e-2a1:Xbox 360 Wireless Receiver (XBOX)"
#define DEVICE_KEYBOARD "11/1-1:AT Translated Set 2 keyboard"
#define DEVICE_KEYBOARD2 "3/258a-1:SINO WEALTH USB KEYBOARD"

#define CONTROLLER_DISPLAYS \
	{\
		.name = "SNES",\
		.devices = {DEVICE_XBOX, DEVICE_ROCKCANDY},\
		.mapping = {\
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
			{"Y", {{EV_KEY, BTN_NORTH}}},\
			{"B", {{EV_KEY, BTN_SOUTH}}},\
			{"X", {{EV_KEY, BTN_WEST}}},\
			{"A", {{EV_KEY, BTN_EAST}}},\
			{"s", {{EV_KEY, BTN_SELECT}}},\
			{"S", {{EV_KEY, BTN_START}}},\
		},\
		.layout = {\
			" _|^|_  [L][R]   (X)  \n"\
			"|<   >|        (Y) (A)\n"\
			" ‾|v|‾  /s//S/   (B)  "\
		},\
	},\
	{\
		.name = "keyboard",\
		.devices = {DEVICE_KEYBOARD, DEVICE_KEYBOARD2},\
		.mapping = {\
			{"W", {{EV_KEY, KEY_W}}},\
			{"A", {{EV_KEY, KEY_A}}},\
			{"S", {{EV_KEY, KEY_S}}},\
			{"D", {{EV_KEY, KEY_D}}},\
		},\
		.layout = {\
			"   [W]   \n"\
			"[A][S][D]"\
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
		.devices = {DEVICE_XBOX, DEVICE_ROCKCANDY},\
		.type = consecutive,\
		.button_list = {\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_UP},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_UP},\
				&(struct button_trigger){EV_ABS, ABS_HAT0Y, -1},\
				&(struct button_trigger){EV_ABS, ABS_Y, -16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_UP},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_UP},\
				&(struct button_trigger){EV_ABS, ABS_HAT0Y, -1},\
				&(struct button_trigger){EV_ABS, ABS_Y, -16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_DOWN},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_DOWN},\
				&(struct button_trigger){EV_ABS, ABS_HAT0Y, 1},\
				&(struct button_trigger){EV_ABS, ABS_Y, 16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_DOWN},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_DOWN},\
				&(struct button_trigger){EV_ABS, ABS_HAT0Y, 1},\
				&(struct button_trigger){EV_ABS, ABS_Y, 16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_LEFT},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_LEFT},\
				&(struct button_trigger){EV_ABS, ABS_HAT0X, -1},\
				&(struct button_trigger){EV_ABS, ABS_X, -16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_RIGHT},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_RIGHT},\
				&(struct button_trigger){EV_ABS, ABS_HAT0X, 1},\
				&(struct button_trigger){EV_ABS, ABS_X, 16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_LEFT},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_LEFT},\
				&(struct button_trigger){EV_ABS, ABS_HAT0X, -1},\
				&(struct button_trigger){EV_ABS, ABS_X, -16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_RIGHT},\
				&(struct button_trigger){EV_KEY, BTN_DPAD_RIGHT},\
				&(struct button_trigger){EV_ABS, ABS_HAT0X, 1},\
				&(struct button_trigger){EV_ABS, ABS_X, 16834},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_B},\
				&(struct button_trigger){EV_KEY, BTN_WEST}\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_A},\
				&(struct button_trigger){EV_KEY, BTN_EAST}\
			}},\
		},\
	},\
	{\
		.name = "simultest",\
		.function = &callback_test,\
		.args = &(struct cb_test){\
			.foo="Some args",\
			.bar=99,\
		},\
		.type = simultaneous,\
		.button_list = {\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_A},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_S},\
			}},\
			&(struct button){{\
				&(struct button_trigger){EV_KEY, KEY_D},\
			}},\
		},\
	},

#endif
