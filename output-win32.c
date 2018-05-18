/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "include/lamprey.h"

void hl_output_win32_init() {
}

void hl_output_win32_destroy() {
}

void hl_output_win32_inject(uint8_t type, uint16_t code, int16_t value) {
	INPUT inputs[32];
	int keys[9] = { VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU, VK_LWIN, VK_RWIN, VK_CAPITAL };
	SHORT keystate[9];
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
		keystate[i] = GetAsyncKeyState(keys[i]) & 0x8000;
	}

	/* Input methods
	 *
	 * SendInput - foreground window
	 * SendMessage - Synchronous, background window
	 * PostMessage - Asynchronous, background window
	 */
}
