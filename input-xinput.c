#include <windows.h>
#include <xinput.h>

#include "include/lamprey.h"

#include "include/input.h"
#include "include/threads.h"

HL_THREAD t_input_xinput;
HL_MUTEX mutex_input_xinput;

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
	struct xinput_maps {
		WORD xinput;
		int mapto;
	} xinput_maps[] = {
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

			for (int j = 0; j < sizeof(xinput_maps) / sizeof(*xinput_maps); j++) {
				if (xinput_button_changed(xinput_devices[i].state.Gamepad.wButtons, newState.Gamepad.wButtons, xinput_maps[j].xinput)) {
					int value = newState.Gamepad.wButtons & xinput_maps[j].xinput ? 1 : 0;
					hl_controller_change(xinput_devices[i].name, i, EV_KEY, xinput_maps[j].mapto, value);
					debug_print("Controller %s, Button: %d = %d\n", xinput_devices[i].name, xinput_maps[j].xinput, value);
				}
			}

			xinput_devices[i].state = newState;

			hl_mutex_unlock(&mutex_input_xinput);
		}
	} while (res == 0);

	hl_input_xinput_destroy();

	return NULL;
}

void hl_input_xinput_destroy() {
	//hl_thread_exit();
}

void hl_input_xinput_inject(int id, uint8_t type, uint16_t code, int16_t value) {
}