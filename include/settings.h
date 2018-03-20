#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "evdev.h"

#define DEVICE_PATH1 "pci-0000:03:00.0-usb-0:3:1.0-event-joystick"
#define DEVICE_PATH2 "pci-0000:11:00.3-usb-0:4.3:1.0-event-kbd"
#define DEVICE_PATH(i) (i == 0 ? DEVICE_PATH1 : DEVICE_PATH2)

static struct shortcut konami = {
	.function = NULL,
	.multi_device = false,
	.type = consecutive,
	.keys = {
		BTN_DPAD_UP,
		BTN_DPAD_UP,
		BTN_DPAD_DOWN,
		BTN_DPAD_DOWN,
		BTN_DPAD_LEFT,
		BTN_DPAD_RIGHT,
		BTN_DPAD_LEFT,
		BTN_DPAD_RIGHT,
		BTN_WEST,
		BTN_EAST,
	}
};

#include "defaults.h"
#endif
