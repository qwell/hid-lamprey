#include <Windows.h>
#include <xinput.h>

#include "include/lamprey.h"

#include "include/input.h"

XINPUT_CAPABILITIES m_xinputCaps;
XINPUT_STATE m_xinputState;
bool m_isControllerConnected = FALSE;

void hl_input_xinput_init() {
	if (XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &m_xinputCaps)) {
		printf("No Xinput controller\n");
		return;
	}

	m_isControllerConnected = TRUE;

	if(XInputGetState(0, &m_xinputState)) {
		printf("Xinput controller disconnected.\n");
		m_isControllerConnected = false;
	}

	hl_controller_change("3/45e-2a1:Xbox 360 Wireless Receiver (XBOX)", 0, EV_KEY, BTN_SOUTH, 1);
	printf("Buttons %d A: %d\n", m_xinputState.Gamepad.wButtons, m_xinputState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
}

void hl_input_xinput_destroy() {
}

void *hl_input_xinput_poll() {
	return NULL;
}

void hl_input_xinput_inject(int id, uint8_t type, uint16_t code, int16_t value) {
}