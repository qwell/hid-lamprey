/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/display.h"
#include "include/input.h"

struct controller_display controller_displays[] = {
	CONTROLLER_DISPLAYS
};

const struct codeswap {
	struct button_trigger in;
	struct button_trigger out;
} codeswaps[] = {
	CODESWAPS
};

struct shortcut shortcuts[] = {
	SHORTCUTS
};

int controller_check_device(const char *device, const char *device_list[], int count) {
	if (count == 0) {
		return 1;
	}

	for (int i = 0; i < count; i++) {
		if (!device_list[i]) {
			if (i == 0) {
				return 1;
			}
		} else if (!strcmp(device, device_list[i])) {
			return 1;
		}
	}

	return 0;
}

void controller_shortcut_simultaneous(struct shortcut *shortcut) {
	int triggered = 1; /* Assume success. */

	for (int i = 0; i < sizeof(shortcut->button_list) / sizeof(*shortcut->button_list); i++) {
		struct button *button = shortcut->button_list[i];
		if (!button) {
			continue;
		}

		for (int j = 0; j < sizeof(button->buttons) / sizeof(*button->buttons); j++) {
			const struct button_trigger *trigger = button->buttons[j];
			if (!trigger) {
				continue;
			}

			if (!button->state) {
				triggered = 0;
			}
		}
	}

	if (triggered && shortcut->function) {
		shortcut->function(shortcut->args ? : NULL);
	}
}

void controller_shortcuts(const char *device, uint8_t type, uint16_t code, int16_t value) {
	for (int i = 0; i < sizeof(shortcuts) / sizeof(*shortcuts); i++) {
		struct shortcut *shortcut = &shortcuts[i];

		if (!controller_check_device(device, shortcut->devices, sizeof(shortcut->devices) / sizeof(*shortcut->devices))) {
			continue;
		}

		for (int i = 0; i < sizeof(shortcut->button_list) / sizeof(*shortcut->button_list); i++) {
			struct button *button = shortcut->button_list[i];
			if (!button) {
				continue;
			}

			for (int j = 0; j < sizeof(button->buttons) / sizeof(*button->buttons); j++) {
				const struct button_trigger *trigger = button->buttons[j];
				if (!trigger) {
					continue;
				}

				if (type == trigger->type && code == trigger->code) {
					if (trigger->triggervalue < 0) {
						button->state = (value <= trigger->triggervalue);
					} else if (trigger->triggervalue > 0) {
						button->state = (value >= trigger->triggervalue);
					} else {
						button->state = value ? 1 : 0;
					}
				}
			}
		}

		switch (shortcut->type) {
		case simultaneous:
			controller_shortcut_simultaneous(shortcut);
			break;
		case consecutive:
			break;
		}
	}

}

void controller_codeswaps(int id, uint8_t type, uint16_t code, int16_t value) {
	for (int i = 0; i < sizeof(codeswaps) / sizeof(*codeswaps); i++) {
		struct codeswap emu = codeswaps[i];
		if (type == emu.in.type && code == emu.in.code) {
			int emuvalue = 0;
			if (emu.in.triggervalue < 0) {
				emuvalue = (value <= emu.in.triggervalue);
			} else if (emu.in.triggervalue > 0) {
				emuvalue = (value >= emu.in.triggervalue);
			} else {
				emuvalue = value ? 1 : 0;
			}
			if (emuvalue && emu.out.triggervalue) {
				emuvalue = emu.out.triggervalue;
			}

			hl_input_inject(id, emu.out.type, emu.out.code, emuvalue);
			debug_print("Code %d (%d) converted to %d (%d)\n",
				emu.in.code, value,
				emu.out.code, emuvalue);
		}
	}
}

void hl_controller_change(const char *device, int id, uint8_t type, uint16_t code, int16_t value) {
	for (int i = 0; i < sizeof(controller_displays) / sizeof(*controller_displays); i++) {
		struct controller_display *controller = &controller_displays[i];

		if (!controller_check_device(device, controller->devices, sizeof(controller->devices) / sizeof(*controller->devices))) {
			continue;
		}

		for (int j = 0; j < sizeof(controller->mapping) / sizeof(*controller->mapping); j++) {
			struct controller_display_mapping *mapping = &controller->mapping[j];

			for (int k = 0; k < sizeof(mapping->buttons) / sizeof(*mapping->buttons); k++) {
				const struct button_trigger *trigger = &mapping->buttons[k];

				if (code == trigger->code && type == trigger->type) {
					/* Things may not work properly if you have multiple buttons
					 * assigned to a mapping that are concurrently triggered.
					 */
					if (trigger->triggervalue < 0) {
						mapping->value = (value <= trigger->triggervalue);
					} else if (trigger->triggervalue > 0) {
						mapping->value = (value >= trigger->triggervalue);
					} else {
						mapping->value = value ? 1 : 0;
					}
				}

			}
		}

		hl_display_output_controller(controller);
	}

	controller_shortcuts(device, type, code, value);

	controller_codeswaps(id, type, code, value);
	return;
}
