#ifndef _EVDEV_H
#define _EVDEV_H

#include <stdbool.h>

#include <libevdev/libevdev.h>

//#define LOW_KEY BTN_MISC
//#define HIGH_KEY BTN_THUMBR
#define LOW_KEY KEY_ESC
#define HIGH_KEY KEY_MAX

#define LOW_AXIS ABS_X
#define HIGH_AXIS ABS_BRAKE

#define LOW_HAT ABS_HAT0X
#define HIGH_HAT ABS_HAT3Y

void gamepad_start();

typedef enum {
	simultaneous = 0,
	consecutive = 1
} shortcut_type;

struct shortcut {
	void (*function) ();
	shortcut_type type;
	bool multi_device;
	/* List of keys that trigger the shortcut.
	 * See https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
	 */
	int keys[];
};

#endif
