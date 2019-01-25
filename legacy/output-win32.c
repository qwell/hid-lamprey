/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "include/lamprey.h"

#include "include/controller.h"

void hl_output_win32_init() {
}

void hl_output_win32_destroy() {
}

void hl_output_win32_inject(uint8_t type, uint16_t code, int16_t value) {
	/*
	int keys[9] = { VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU, VK_LWIN, VK_RWIN, VK_CAPITAL };
	SHORT keystate[9];
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
		keystate[i] = GetAsyncKeyState(keys[i]) & 0x8000;
	}

	INPUT input;
	int scancode;

	for (int i = 0; i < codelookup_count / sizeof(*codelookups); i++) {
		struct codelookup lookup = codelookups[i];
		if (lookup.type == type) {
			for (int j = 0; j < sizeof(lookup.codes) / sizeof(*lookup.codes); j++) {
				if (lookup.codes[j].code == code) {
					struct button_code *test = (struct button_code *)calloc(1, sizeof(*test));
					test->type = code.type;
					test->code = code.codes[j].code;
					return test;
				}
			}
		}
	}
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = 0;
	input.ki.wScan = scan_code;
	input.ki.dwFlags = 0;
	input.ki.time = 0;
	SendInput(1, &input, sizeof(input));
	*/

	/* Input methods
	 *
	 * SendInput - foreground window
	 * SendMessage - Synchronous, background window
	 * PostMessage - Asynchronous, background window
	 */
}
