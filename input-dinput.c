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

BOOL CALLBACK input_dinput_enum_axis(const DIDEVICEOBJECTINSTANCE *instance, void *context) {
	if (instance->dwType & DIDFT_AXIS) {
		DIPROPRANGE propRange;
		propRange.diph.dwSize = sizeof(DIPROPRANGE);
		propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		propRange.diph.dwHow = DIPH_BYID;
		propRange.diph.dwObj = instance->dwType;
		propRange.lMin = -256;
		propRange.lMax = +256;

		// Set the range for the axis
		if (hl_input_dinput->joystick->SetProperty(DIPROP_RANGE, &propRange.diph) != DI_OK) {
			return DIENUM_STOP;
		}
	}

	return DIENUM_CONTINUE;
}

BOOL CALLBACK input_dinput_enum_devices(const DIDEVICEINSTANCE *instance, void *context) {
	if (hl_input_dinput->di->CreateDevice(instance->guidInstance, &hl_input_dinput->joystick, NULL) != DI_OK) {
		return DIENUM_CONTINUE;
	}

	if (hl_input_dinput->joystick->SetDataFormat(&c_dfDIJoystick2) != DI_OK) {
		return DIENUM_CONTINUE;
	}

	if (hl_input_dinput->joystick->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK) {
		return DIENUM_CONTINUE;
	}

	hl_input_dinput->capabilities.dwSize = sizeof(DIDEVCAPS);
	if (hl_input_dinput->joystick->GetCapabilities(&hl_input_dinput->capabilities) != DI_OK) {
		return DIENUM_CONTINUE;
	}

	if (hl_input_dinput->joystick->EnumObjects(input_dinput_enum_axis, NULL, DIDFT_AXIS) != DI_OK) {
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

void hl_input_dinput_init() {
	hl_input_dinput = (struct hl_input_dinput *)malloc(sizeof(struct hl_input_dinput));

	if (DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&hl_input_dinput->di, NULL) != DI_OK) {
		return;
	}

	if (hl_input_dinput->di->EnumDevices(DI8DEVCLASS_GAMECTRL, input_dinput_enum_devices, NULL, DIEDFL_ATTACHEDONLY) != DI_OK) {
		return;
	}

	hl_thread_create(&t_input_dinput, hl_input_dinput_poll, NULL);

	hl_mutex_unlock(&mutex_input_dinput);

	return;
}

void *hl_input_dinput_poll() {
	struct dinput_button_maps {
		WORD dinput;
		int mapto;
	} dinput_button_maps[] = {
		{ 0, BTN_WEST },
		{ 1, BTN_SOUTH },
		{ 2, BTN_EAST },
		{ 3, BTN_NORTH },
		{ 4, BTN_TR },
		{ 5, BTN_TL },
		{ 6, BTN_TR2 },
		{ 7, BTN_TL2 },
		{ 8, BTN_START },
		{ 9, BTN_SELECT },
		{ 10, BTN_THUMBR },
		{ 11, BTN_THUMBL },
	};

	DIJOYSTATE2 state;
	HRESULT hr;
	
	do {
		if ((hr = hl_input_dinput->joystick->Poll()) != DI_OK) {
			hr = hl_input_dinput->joystick->Acquire();
			while (hr == DIERR_INPUTLOST) {
				hr = hl_input_dinput->joystick->Acquire();
			}
		}

		if ((hr == DIERR_INVALIDPARAM) || (hr == DIERR_NOTINITIALIZED)) {
			break;
		}

		if (hr == DIERR_OTHERAPPHASPRIO) {
			/* Somebody else has control.  What do we do?  We don't ask for
			 * exclusive access, so maybe we just never hit this?
			 * Keep trying, I suppose.
			 */
			continue;
		}

		if ((hr = hl_input_dinput->joystick->GetDeviceState(sizeof(DIJOYSTATE2), &state)) == DI_OK) {
			bool dpadChanged = false;
			bool pRight = false;
			bool pLeft = false;
			bool pUp = false;
			bool pDown = false;

			for (int i = 0; i < hl_input_dinput->capabilities.dwButtons; i++) {
				if (state.rgbButtons[i] != hl_input_dinput->state.rgbButtons[i]) {
					if (state.rgbButtons[i] & 0x80) {
						hl_controller_change("Dinput 0", 0, EV_KEY, dinput_button_maps[i].mapto, 1);
					} else {
						hl_controller_change("Dinput 0", 0, EV_KEY, dinput_button_maps[i].mapto, 0);
					}
				}
			}

			for (int i = 0; i < hl_input_dinput->capabilities.dwPOVs; i++) {
				if (state.rgdwPOV[i] != hl_input_dinput->state.rgdwPOV[i]) {
					dpadChanged = true;

					/* What the fuck?  This is weeeeeird... */
					switch (state.rgdwPOV[i]) {
					case 0:
						pUp = true;
						break;
					case 4500:
						pUp = true;
						pRight = true;
						break;
					case 9000:
						pRight = true;
						break;
					case 13500:
						pDown = true;
						pRight = true;
						break;
					case 18000:
						pDown = true;
						break;
					case 22500:
						pDown = true;
						pLeft = true;
						break;
					case 27000:
						pLeft = true;
						break;
					case 31500:
						pUp = true;
						pLeft = true;
						break;
					}
				}
			}

			if (state.lX != hl_input_dinput->state.lX) {
				dpadChanged = true;
				if (state.lX > (256 * AXIS_DEADZONE)) {
					pRight = true;
				} else if (state.lX < (-256 * AXIS_DEADZONE)) {
					pLeft = true;
				}
			}

			if (state.lY != hl_input_dinput->state.lY) {
				dpadChanged = true;
				if (state.lY >(256 * AXIS_DEADZONE)) {
					pDown = true;
				} else if (state.lY < (-256 * AXIS_DEADZONE)) {
					pUp = true;
				}
			}

			if (dpadChanged) {
				if (pRight) {
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_RIGHT, 1);
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_LEFT, 0);
				} else if (pLeft) {
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_LEFT, 1);
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_RIGHT, 0);
				} else {
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_LEFT, 0);
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_RIGHT, 0);
				}

				if (pDown) {
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_DOWN, 1);
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_UP, 0);
				} else if (pUp) {
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_UP, 1);
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_DOWN, 0);
				} else {
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_UP, 0);
					hl_controller_change("Dinput 0", 0, EV_KEY, BTN_DPAD_DOWN, 0);
				}
			}
		}

		hl_input_dinput->state = state;
		Sleep(33);
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

	hl_input_dinput->joystick->Unacquire();

	free(hl_input_dinput);
	hl_input_dinput = NULL;

	hl_mutex_unlock(&mutex_input_dinput);

	hl_thread_exit();
}

void hl_input_dinput_inject(int id, uint8_t type, uint16_t code, int16_t value) {
}
