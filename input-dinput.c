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
#include "include/input.h"

hl_thread_t t_input_dinput;
hl_mutex_t mutex_input_dinput;
struct hl_input_dinput *hl_input_dinput = NULL;

#define padUp    1 << 0
#define padRight 1 << 1
#define padDown  1 << 2
#define padLeft  1 << 3

BOOL CALLBACK input_dinput_enum_axis(const DIDEVICEOBJECTINSTANCE *instance, void *ptr) {
	LPDIRECTINPUTDEVICE8 device = (LPDIRECTINPUTDEVICE8)ptr;

	if (instance->dwType & DIDFT_AXIS) {
		DIPROPRANGE propRange;
		propRange.diph.dwSize = sizeof(DIPROPRANGE);
		propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		propRange.diph.dwHow = DIPH_BYID;
		propRange.diph.dwObj = instance->dwType;
		propRange.lMin = -256;
		propRange.lMax = 256;

		// Set the range for the axis
		if (device->SetProperty(DIPROP_RANGE, &propRange.diph) != DI_OK) {
			return DIENUM_STOP;
		}
	}

	return DIENUM_CONTINUE;
}

BOOL CALLBACK input_dinput_enum_devices(const DIDEVICEINSTANCE *instance, void *context) {
	struct dinput_device *input = (struct dinput_device *)calloc(1, sizeof(struct dinput_device));

	int devtype = GET_DIDEVICE_TYPE(instance->dwDevType);
	int devsubtype = GET_DIDEVICE_SUBTYPE(instance->dwDevType);

	if (hl_input_dinput->di->CreateDevice(instance->guidInstance, &input->device, NULL) != DI_OK) {
		free(input);
		return DIENUM_CONTINUE;
	}

	switch (devtype) {
	case DI8DEVTYPE_GAMEPAD:
	case DI8DEVTYPE_JOYSTICK:
		if (input->device->SetDataFormat(&c_dfDIJoystick2) != DI_OK) {
			free(input);
			return DIENUM_CONTINUE;
		}
		if (input->device->EnumObjects(input_dinput_enum_axis, input->device, DIDFT_AXIS) != DI_OK) {
			free(input);
			return DIENUM_CONTINUE;
		}
		break;
	case DI8DEVTYPE_MOUSE:
	case DI8DEVTYPE_SCREENPOINTER:
		if (input->device->SetDataFormat(&c_dfDIMouse2) != DI_OK) {
			free(input);
			return DIENUM_CONTINUE;
		}
		if (input->device->EnumObjects(input_dinput_enum_axis, input->device, DIDFT_AXIS) != DI_OK) {
			free(input);
			return DIENUM_CONTINUE;
		}
		break;
	case DI8DEVTYPE_KEYBOARD:
		if (input->device->SetDataFormat(&c_dfDIKeyboard) != DI_OK) {
			free(input);
			return DIENUM_CONTINUE;
		}
		break;
	default:
		free(input);
		return DIENUM_CONTINUE;
	}

	if (input->device->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK) {
		free(input);
		return DIENUM_CONTINUE;
	}

	input->capabilities.dwSize = sizeof(DIDEVCAPS);
	if (input->device->GetCapabilities(&input->capabilities) != DI_OK) {
		free(input);
		return DIENUM_CONTINUE;
	}

	input->type = devtype;

	switch (input->type) {
	case DI8DEVTYPE_GAMEPAD:
	case DI8DEVTYPE_JOYSTICK:
		snprintf(input->name, sizeof(input->name) - 1, "Dinput gamepad%d", hl_input_dinput->gamepad_count);
		hl_input_dinput->gamepad_count++;
		break;
	case DI8DEVTYPE_MOUSE:
	case DI8DEVTYPE_SCREENPOINTER:
		snprintf(input->name, sizeof(input->name) - 1, "Dinput mouse%d", hl_input_dinput->mouse_count);
		hl_input_dinput->mouse_count++;
		break;
	case DI8DEVTYPE_KEYBOARD:
		snprintf(input->name, sizeof(input->name) - 1, "Dinput keyboard%d", hl_input_dinput->keyboard_count);
		hl_input_dinput->keyboard_count++;
		break;
	}

	hl_input_dinput->devices = (struct dinput_device **)realloc(hl_input_dinput->devices, (hl_input_dinput->device_count + 1) * sizeof(*hl_input_dinput->devices));
	hl_input_dinput->devices[hl_input_dinput->device_count] = input;
	hl_input_dinput->device_count++;

	return DIENUM_CONTINUE;
}

void hl_input_dinput_init() {
	hl_mutex_create(&mutex_input_xinput);

	hl_mutex_lock(&mutex_input_dinput);

	hl_input_dinput = (struct hl_input_dinput *)calloc(1, sizeof(struct hl_input_dinput));

	if (DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&hl_input_dinput->di, NULL) != DI_OK) {
		hl_mutex_unlock(&mutex_input_dinput);
		return;
	}

	if (hl_input_dinput->di->EnumDevices(DI8DEVCLASS_ALL, input_dinput_enum_devices, NULL, DIEDFL_ATTACHEDONLY) != DI_OK) {
		hl_mutex_unlock(&mutex_input_dinput);
		return;
	}

	if (hl_input_dinput->device_count > 0) {
		hl_thread_create(&t_input_dinput, hl_input_dinput_poll, NULL);
	}

	hl_mutex_unlock(&mutex_input_dinput);

	return;
}

int dinput_get_padstate(DWORD state) {
	/* What the fuck?  This is weeeeeird... */
	switch (state) {
	case 0:
		return padUp;
	case 4500:
		return padUp | padRight;
	case 9000:
		return padRight;
	case 13500:
		return padRight | padDown;
	case 18000:
		return padDown;
	case 22500:
		return padDown | padLeft;
	case 27000:
		return padLeft;
	case 31500:
		return padLeft | padUp;
	}

	return 0;
}

void *hl_input_dinput_poll() {
	struct dinput_button_maps {
		WORD dinput;
		int maptype;
		int mapcode;
		int mapvalue;
	};
	struct dinput_button_maps dinput_gamepad_button_maps[2][16] = { {
			/* 8 buttons */
			{ 0, EV_KEY, BTN_SOUTH },
			{ 1, EV_KEY, BTN_EAST },
			{ 2, EV_KEY, BTN_WEST },
			{ 3, EV_KEY, BTN_NORTH },
			{ 4, EV_KEY, BTN_TL },
			{ 5, EV_KEY, BTN_TR },
			{ 6, EV_KEY, BTN_SELECT },
			{ 7, EV_KEY, BTN_START },
		},{
			/* 12 buttons */
			{ 0, EV_KEY, BTN_WEST },
			{ 1, EV_KEY, BTN_SOUTH },
			{ 2, EV_KEY, BTN_EAST },
			{ 3, EV_KEY, BTN_NORTH },
			{ 4, EV_KEY, BTN_TR },
			{ 5, EV_KEY, BTN_TL },
			{ 6, EV_KEY, BTN_TR2 },
			{ 7, EV_KEY, BTN_TL2 },
			{ 8, EV_KEY, BTN_START },
			{ 9, EV_KEY, BTN_SELECT },
			{ 10, EV_KEY, BTN_THUMBR },
			{ 11, EV_KEY, BTN_THUMBL },
		}
	};
	struct dinput_button_maps dinput_keyboard_button_maps[256] = {
		{ DIK_LEFT, EV_KEY, BTN_DPAD_LEFT },
		{ DIK_RIGHT, EV_KEY, BTN_DPAD_RIGHT },
		{ DIK_UP, EV_KEY, BTN_DPAD_UP },
		{ DIK_DOWN, EV_KEY, BTN_DPAD_DOWN },
		{ DIK_NUMPAD8, EV_KEY, BTN_DPAD_UP },
		{ DIK_NUMPAD4, EV_KEY, BTN_DPAD_LEFT },
		{ DIK_NUMPAD5, EV_KEY, BTN_DPAD_DOWN },
		{ DIK_NUMPAD6, EV_KEY, BTN_DPAD_RIGHT },
		{ DIK_LSHIFT, EV_KEY, BTN_TL },
		{ DIK_RSHIFT, EV_KEY, BTN_TR },
		{ DIK_MINUS, EV_KEY, BTN_SELECT },
		{ DIK_EQUALS, EV_KEY, BTN_START },
		{ DIK_1, EV_KEY, BTN_NORTH },
		{ DIK_2, EV_KEY, BTN_EAST },
		{ DIK_3, EV_KEY, BTN_SOUTH },
		{ DIK_4, EV_KEY, BTN_WEST },
		{ DIK_I, EV_ABS, ABS_Y, -128 },
		{ DIK_J, EV_ABS, ABS_X, -128 },
		{ DIK_K, EV_ABS, ABS_Y, 128 },
		{ DIK_L, EV_ABS, ABS_X, 128 },
	};

	HRESULT hr = DI_OK;

	HANDLE events[32] = {};

	hl_mutex_lock(&mutex_input_dinput);
	for (int i = 0; i < hl_input_dinput->device_count; i++) {
		HANDLE event = CreateEvent(NULL, false, false, NULL);
		if (!event) {
			continue;
		}

		if (hl_input_dinput->devices[i]->device->SetEventNotification(event) != DI_OK) {
			continue;
		}
		hr = hl_input_dinput->devices[i]->device->Acquire();
		while (hr == DIERR_INPUTLOST) {
			hr = hl_input_dinput->devices[i]->device->Acquire();
		}

		hl_input_dinput->devices[i]->event = event;
		events[i] = event;
	}
	hl_mutex_unlock(&mutex_input_dinput);

	do {
		DWORD msg;

		msg = MsgWaitForMultipleObjects(hl_input_dinput->device_count, events, false, INFINITE, QS_ALLINPUT);
		if (msg >= WAIT_OBJECT_0 && msg <= WAIT_OBJECT_0 + hl_input_dinput->device_count) {
			int devnum = msg - WAIT_OBJECT_0;
			struct dinput_device *input;

			BYTE state[256];

			hl_mutex_lock(&mutex_input_dinput);

			input = hl_input_dinput->devices[devnum];

			switch (input->type) {
			case DI8DEVTYPE_GAMEPAD:
			case DI8DEVTYPE_JOYSTICK:
			{
				DIJOYSTATE2 oldstate;
				DIJOYSTATE2 newstate;

				if ((hr = input->device->GetDeviceState(sizeof(DIJOYSTATE2), &newstate)) == DI_OK) {
					bool axisHChanged = false;
					bool axisVChanged = false;

					int map = -1;

					memcpy(&oldstate, &hl_input_dinput->devices[devnum]->state, sizeof(oldstate));
					memcpy(&state, &newstate, sizeof(newstate));

					switch (input->capabilities.dwButtons) {
					case 8:
						map = 0;
						break;
					case 12:
						map = 1;
						break;
					}
					if (map >= 0) {
						for (int i = 0; i < input->capabilities.dwButtons; i++) {
							struct dinput_button_maps curmap = dinput_gamepad_button_maps[map][i];
							if (newstate.rgbButtons[i] != oldstate.rgbButtons[i]) {
								if (newstate.rgbButtons[i] & 0x80) {
									hl_controller_change(input->name, 0, curmap.maptype, curmap.mapcode, curmap.mapvalue ? curmap.mapvalue : 1);
								} else {
									hl_controller_change(input->name, 0, curmap.maptype, curmap.mapcode, 0);
								}
							}
						}
					}
					for (int i = 0; i < input->capabilities.dwPOVs; i++) {
						if (newstate.rgdwPOV[i] != oldstate.rgdwPOV[i]) {
							int oldPad = dinput_get_padstate(oldstate.rgdwPOV[i]);
							int newPad = dinput_get_padstate(newstate.rgdwPOV[i]);
							int sharePad = oldPad ^ newPad;

							oldPad &= sharePad;
							newPad &= sharePad;

							if (oldPad & padUp) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_UP, 0);
							} else if (newPad & padUp) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_UP, 1);
							}

							if (oldPad & padRight) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_RIGHT, 0);
							} else if (newPad & padRight) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_RIGHT, 1);
							}

							if (oldPad & padDown) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_DOWN, 0);
							} else if (newPad & padDown) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_DOWN, 1);
							}

							if (oldPad & padLeft) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_LEFT, 0);
							} else if (newPad & padLeft) {
								hl_controller_change(input->name, 0, EV_KEY, BTN_DPAD_LEFT, 1);
							}
						}
					}

					if (hl_controller_scale_range(newstate.lX, -256, 256) != hl_controller_scale_range(oldstate.lX, -256, 256)) {
						hl_controller_change(input->name, 0, EV_ABS, ABS_X, hl_controller_scale_range(newstate.lX, -256, 256));
					}
					if (hl_controller_scale_range(newstate.lY, -256, 256) != hl_controller_scale_range(oldstate.lY, -256, 256)) {
						hl_controller_change(input->name, 0, EV_ABS, ABS_Y, hl_controller_scale_range(newstate.lY, -256, 256));
					}

					/* TODO Is this what all controllers look like for right stick?
					 * Confirmed: No.
					if (hl_controller_scale_range(newstate.rglSlider[0], -256, 256) != hl_controller_scale_range(oldstate.rglSlider[0], -256, 256)) {
						hl_controller_change(input->name, 0, EV_ABS, ABS_RX, hl_controller_scale_range(newstate.rglSlider[0], -256, 256));
					}
					if (hl_controller_scale_range(newstate.lRz, -256, 256) != hl_controller_scale_range(oldstate.lRz, -256, 256)) {
						hl_controller_change(input->name, 0, EV_ABS, ABS_RY, hl_controller_scale_range(newstate.lRz, -256, 256));
					}
					*/
				}
				break;
			}
			case DI8DEVTYPE_MOUSE:
			case DI8DEVTYPE_SCREENPOINTER:
			{
				DIMOUSESTATE2 oldstate;
				DIMOUSESTATE2 newstate;
				if ((hr = input->device->GetDeviceState(sizeof(DIMOUSESTATE2), &newstate)) == DI_OK) {
					memcpy(&oldstate, &hl_input_dinput->devices[devnum]->state, sizeof(oldstate));
					memcpy(&state, &newstate, sizeof(newstate));
				}
			}

				break;
			case DI8DEVTYPE_KEYBOARD:
			{
				BYTE oldstate[256];
				BYTE newstate[256];
				if ((hr = input->device->GetDeviceState(sizeof(newstate), &newstate)) == DI_OK) {
					memcpy(&oldstate, &hl_input_dinput->devices[devnum]->state, sizeof(oldstate));
					memcpy(&state, &newstate, sizeof(newstate));

					for (int i = 0; i < sizeof(dinput_keyboard_button_maps) / sizeof(*dinput_keyboard_button_maps); i++) {
						struct dinput_button_maps curmap = dinput_keyboard_button_maps[i];
						BYTE aold = oldstate[curmap.dinput];
						BYTE anew = newstate[curmap.dinput];
						if (newstate[curmap.dinput] != oldstate[curmap.dinput]) {
							if (newstate[curmap.dinput] & 0x80) {
								hl_controller_change(input->name, 0, curmap.maptype, curmap.mapcode, curmap.mapvalue ? curmap.mapvalue : 1);
							} else {
								hl_controller_change(input->name, 0, curmap.maptype, curmap.mapcode, 0);
							}
						}
					}
				}
				break;
			}
			}

			memcpy(&hl_input_dinput->devices[devnum]->state, &state, sizeof(hl_input_dinput->devices[devnum]->state));

			hl_mutex_unlock(&mutex_input_dinput);
		}
	} while (hr == DI_OK || hr == DIERR_OTHERAPPHASPRIO);

	hl_input_dinput_destroy();

	return NULL;
}

void hl_input_dinput_destroy() {
	hl_mutex_lock(&mutex_input_dinput);

	if (hl_input_dinput == NULL) {
		hl_mutex_unlock(&mutex_input_dinput);
		return;
	}

	for (int i = 0; i < hl_input_dinput->device_count; i++) {
		hl_input_dinput->devices[i]->device->Unacquire();
		free(hl_input_dinput->devices[i]);
	}

	free(hl_input_dinput->devices);
	free(hl_input_dinput);
	hl_input_dinput = NULL;

	hl_mutex_unlock(&mutex_input_dinput);

	hl_thread_exit();
}

void hl_input_dinput_inject(int id, uint8_t type, uint16_t code, int16_t value) {
}
