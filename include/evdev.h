#ifndef _EVDEV_H
#define _EVDEV_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/poll.h>

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#include "evdev-keytable.h"

struct keylookup {
	char *name;
	int key;
};

#define LOW_KEY KEY_ESC
#define HIGH_KEY KEY_MAX

#define LOW_AXIS ABS_X
#define HIGH_AXIS ABS_BRAKE

#define LOW_HAT ABS_HAT0X
#define HIGH_HAT ABS_HAT3Y

#define LOW_REL REL_X
#define HIGH_REL REL_MAX

struct button_mapping {
	uint8_t type;
	uint16_t code;
	int16_t triggervalue;
};

struct controller_mapping {
	char display;
	struct button_mapping buttons[8];
	bool value;
};

struct controller {
	char *name;
	char *device;
	struct controller_mapping mapping[64];
	char layout[8][32];
};

typedef enum {
	simultaneous = 0,
	consecutive = 1
} hl_shortcut_type;

struct key_data {
};

struct axis_data {
	int min;
	int max;
};

struct hat_data {
	int min;
	int max;
};

struct hl_evdev {
	struct libevdev *dev_list[256];
	struct pollfd fds[256];
	int nfds;
	struct maps {
		struct key_data key_map[HIGH_KEY - LOW_KEY];
		struct axis_data abs_map[HIGH_AXIS - LOW_AXIS];
		struct hat_data hat_map[HIGH_HAT - LOW_HAT];
	} maps;
};

struct hl_shortcut {
	void (*function) ();
	hl_shortcut_type type;
	bool multi_device;
	/* List of keys that trigger the shortcut.
	 * See https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
	 */
	int keys[];
};

void *hl_evdev_init();
void *hl_evdev_poll(void *hl_init);

void key_press(const char *device, uint8_t type, uint16_t key, int16_t value);
void axis_move(const char *device, uint8_t type, uint8_t axis, int16_t value);

#endif
