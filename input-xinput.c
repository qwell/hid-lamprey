/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <windows.h>
#include <xinput.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/input.h"

hl_thread_t t_input_xinput;
hl_mutex_t mutex_input_xinput;

bool xinput_button_changed(WORD oldButtons, WORD newButtons, WORD button) {
	if ((oldButtons & button) != (newButtons & button)) {
		return TRUE;
	}

	return FALSE;
}

void hl_input_xinput_init() {
	hl_mutex_create(&mutex_input_xinput);
	hl_thread_create(&t_input_xinput, hl_input_xinput_poll, NULL);
}

void *hl_input_xinput_poll() {
	struct xinput_button_maps {
		WORD xinput;
		int mapto;
	} xinput_button_maps[] = {
		{ XINPUT_GAMEPAD_DPAD_UP, BTN_DPAD_UP },
		{ XINPUT_GAMEPAD_DPAD_DOWN, BTN_DPAD_DOWN },
		{ XINPUT_GAMEPAD_DPAD_LEFT, BTN_DPAD_LEFT },
		{ XINPUT_GAMEPAD_DPAD_RIGHT, BTN_DPAD_RIGHT },
		{ XINPUT_GAMEPAD_START, BTN_START },
		{ XINPUT_GAMEPAD_BACK, BTN_SELECT},
		{ XINPUT_GAMEPAD_LEFT_THUMB, BTN_THUMBL },
		{ XINPUT_GAMEPAD_RIGHT_THUMB, BTN_THUMBR },
		{ XINPUT_GAMEPAD_LEFT_SHOULDER, BTN_TL },
		{ XINPUT_GAMEPAD_RIGHT_SHOULDER, BTN_TR },
		{ XINPUT_GAMEPAD_A, BTN_SOUTH },
		{ XINPUT_GAMEPAD_B, BTN_EAST },
		{ XINPUT_GAMEPAD_X, BTN_WEST },
		{ XINPUT_GAMEPAD_Y, BTN_NORTH },
	};

	struct xinput_device {
		int id;
		char name[16];
		bool connected;
		XINPUT_STATE state;
	} xinput_devices[4] = { {0, "Xinput 0"}, {1, "Xinput 1"}, {2, "Xinput 2"}, {3, "Xinput 3"} };

	int res = 0;

	do {
		for (int i = 0; i < 4; i++) {
			hl_mutex_lock(&mutex_input_xinput);
			XINPUT_STATE newState;
			bool changed = FALSE;

			if (XInputGetState(i, &newState)) {
				if (xinput_devices[i].connected) {
					xinput_devices[i].connected = FALSE;
					debug_print("Device %s disconnected.\n", xinput_devices[i].name);
				}
				continue;
			}
			if (!xinput_devices[i].connected) {
				xinput_devices[i].connected = TRUE;
				debug_print("Device %s connected.\n", xinput_devices[i].name);
			}

			if (newState.dwPacketNumber <= xinput_devices[i].state.dwPacketNumber) {
				continue;
			}

			for (int j = 0; j < sizeof(xinput_button_maps) / sizeof(*xinput_button_maps); j++) {
				if (xinput_button_changed(xinput_devices[i].state.Gamepad.wButtons, newState.Gamepad.wButtons, xinput_button_maps[j].xinput)) {
					int value = newState.Gamepad.wButtons & xinput_button_maps[j].xinput ? 1 : 0;
					hl_controller_change(xinput_devices[i].name, i, EV_KEY, xinput_button_maps[j].mapto, value);
					debug_print("Controller %s, Button: %d = %d\n", xinput_devices[i].name, xinput_button_maps[j].xinput, value);
				}
			}

			if (xinput_devices[i].state.Gamepad.bLeftTrigger != newState.Gamepad.bLeftTrigger) {
				hl_controller_change(xinput_devices[i].name, i, EV_ABS, ABS_HAT2Y, newState.Gamepad.bLeftTrigger);
				debug_print("Controller %s, ABS_HAT2Y = %d\n", xinput_devices[i].name, value);
			}
			if (xinput_devices[i].state.Gamepad.bRightTrigger != newState.Gamepad.bRightTrigger) {
				hl_controller_change(xinput_devices[i].name, i, EV_ABS, ABS_HAT2X, newState.Gamepad.bRightTrigger);
				debug_print("Controller %s, ABS_HAT2X: %d = %d\n", xinput_devices[i].name, value);
			}
			if (xinput_devices[i].state.Gamepad.sThumbLX != newState.Gamepad.sThumbLX) {
				hl_controller_change(xinput_devices[i].name, i, EV_ABS, ABS_X, newState.Gamepad.sThumbLX);
				debug_print("Controller %s, ABS_X: %d = %d\n", xinput_devices[i].name, value);
			}
			if (xinput_devices[i].state.Gamepad.sThumbLY != newState.Gamepad.sThumbLY) {
				hl_controller_change(xinput_devices[i].name, i, EV_ABS, ABS_Y, newState.Gamepad.sThumbLY);
				debug_print("Controller %s, ABS_Y: %d = %d\n", xinput_devices[i].name, value);
			}
			if (xinput_devices[i].state.Gamepad.sThumbRX != newState.Gamepad.sThumbRX) {
				hl_controller_change(xinput_devices[i].name, i, EV_ABS, ABS_RX, newState.Gamepad.sThumbRX);
				debug_print("Controller %s, ABS_RX: %d = %d\n", xinput_devices[i].name, value);
			}
			if (xinput_devices[i].state.Gamepad.sThumbRY != newState.Gamepad.sThumbRY) {
				hl_controller_change(xinput_devices[i].name, i, EV_ABS, ABS_RY, newState.Gamepad.sThumbRY);
				debug_print("Controller %s, ABS_RY: %d = %d\n", xinput_devices[i].name, value);
			}

			xinput_devices[i].state = newState;

			hl_mutex_unlock(&mutex_input_xinput);
		}
		Sleep(33);
	} while (res == 0);

	hl_input_xinput_destroy();

	return NULL;
}

void hl_input_xinput_destroy() {
	hl_thread_exit();
}

void hl_input_xinput_inject(int id, uint8_t type, uint16_t code, int16_t value) {
}
