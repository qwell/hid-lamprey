#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "evdev.h"

#define DEVICE_PATH1 "pci-0000:03:00.0-usb-0:3:1.0-event-joystick"
#define DEVICE_PATH2 "pci-0000:11:00.3-usb-0:4.3:1.0-event-kbd"
#define DEVICE_PATH(i) (i == 0 ? DEVICE_PATH1 : DEVICE_PATH2)

typedef enum {
	simultaneous = 0,
	consecutive = 1
} shortcut_type;

struct shortcut {
	void (*function) ();
	shortcut_type type;
	/* List of keys that trigger the shortcut.
	 * See https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
	 */
	int keys[];
};

static struct shortcut konami = {
	.function = NULL,
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
