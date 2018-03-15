#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <libevdev/libevdev.h>

#define DEVICE_PATH "pci-0000:03:00.0-usb-0:3:1.0-event-joystick"

typedef enum {
	simultaneous = 0,
	consecutive = 1
} shortcut_type;

struct shortcut {
	void (*function) ();
	shortcut_type type;
	/* List of buttons that trigger the shortcut.
	 * See https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
	 */
	int buttons[];
};

static struct shortcut konami = {
	.function = NULL,
	.type = consecutive,
	.buttons = {
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
