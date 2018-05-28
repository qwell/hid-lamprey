/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/display.h"

struct codelookup codelookups[] = {
	CODETABLE
};
int codelookup_count = sizeof(codelookups);

struct input_mapping **input_mappings;
int input_mapping_count = 0;

struct emulation **emulations;
int emulation_count = 0;

struct shortcut **shortcuts;
int shortcut_count = 0;

struct device **devices;
int device_count = 0;

struct button_code *hl_controller_get_code_by_name(char *type, char *name) {
	for (int i = 0; i < codelookup_count / sizeof(*codelookups); i++) {
		struct codelookup code = codelookups[i];
		if (code.typestr && !strcmp(code.typestr, type)) {
			for (int j = 0; j < sizeof(code.codes) / sizeof(*code.codes); j++) {
				if (code.codes[j].codestr && !strcmp(code.codes[j].codestr, name)) {
					struct button_code *test = (struct button_code *)calloc(1, sizeof(*test));
					test->type = code.type;
					test->code = code.codes[j].code;
					return test;
				}
			}
		}
	}
	return NULL;
}

int hl_controller_scale_range(int curvalue, int curmin, int curmax, bool usedeadzone) {
	int newmin = -256;
	int newmax = 255;
	int value = 0;

	/* Find midpoint of possible range.
	* 0 -> 255 = 128
	* -32768 -> 32767 = 0
	*/
	int zeroish = curmin + curmax;
	/* Make it even. */
	zeroish = zeroish % 2 ? zeroish : zeroish + 1;
	/* Div 2 to get the midpoint. */
	int relzero = zeroish ? round(zeroish / 2) : zeroish;

	int rangesize = (curmax - curmin);
	int deadsize = 0;
	if (usedeadzone) {
		deadsize = ((rangesize % 2 ? rangesize : rangesize + 1) / 2) * hl_settings->deadzone_axis;
	}

	/* Scale value
	 * from min > relzero +/- deadsize > max
	 * to newmin > 0 > newmax
	 */
	if (curvalue >= relzero + deadsize) {
		value = (newmax - relzero) * (curvalue - (relzero + deadsize)) / (curmax - (relzero + deadsize));
	} else if (curvalue <= relzero - deadsize) {
		value = (relzero + newmin) * ((relzero - deadsize) - curvalue) / ((relzero - deadsize) - curmin);
	}

	return value;
}

int controller_check_device(const char *device, char *device_list[], int count) {
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

	for (int i = 0; i < shortcut->button_count; i++) {
		struct shortcut_button *button = shortcut->buttons[i];
		if (!button) {
			continue;
		}

		if (!button->state) {
			triggered = 0;
		}
	}

	if (triggered) {
		debug_print("Triggered shortcut: %s\n", shortcut->name);
		if (shortcut->function) {
			shortcut->function(shortcut->args ? shortcut->args : NULL);
		}
	}
}

void controller_shortcut_consecutive(struct shortcut *shortcut) {
#if 0
	static struct test {
	} *foo = NULL;

	if (!foo) {
		foo = calloc(1, sizeof(foo));
	};

	int triggered = 0; /* Assume failure. */

	for (int i = 0; i < sizeof(shortcut->buttons) / sizeof(*shortcut->buttons); i++) {
		struct button *button = shortcut->buttons[i];
		if (!button) {
			continue;
		}

		if (!button->state) {
			triggered = 0;
		}
	}

	free(foo);
	foo = NULL;
#endif
}

void controller_shortcuts(const char *device, uint8_t type, uint16_t code, int16_t value) {
	for (int i = 0; i < shortcut_count; i++) {
		struct shortcut *shortcut = shortcuts[i];

		if (!controller_check_device(device, shortcut->devices, shortcut->device_count)) {
			continue;
		}

		for (int j = 0; j < shortcut->button_count; j++) {
			struct shortcut_button *button = shortcut->buttons[j];
			if (!button) {
				continue;
			}

			if (type == button->type && code == button->code) {
				if (button->trigger_low < 0 || button->trigger_high > 0) {
					if (button->trigger_low < 0 && value <= button->trigger_low) {
						button->state = true;
					} else if (button->trigger_high > 0 && value >= button->trigger_high) {
						button->state = true;
					} else {
						button->state = false;
					}
				} else {
					button->state = value ? true : false;
				}
			}
		}

		switch (shortcut->type) {
		case simultaneous:
			controller_shortcut_simultaneous(shortcut);
			break;
		case consecutive:
			controller_shortcut_consecutive(shortcut);
			break;
		}
	}

}

void controller_emulations(int id, uint8_t type, uint16_t code, int16_t value) {
	for (int i = 0; i < emulation_count; i++) {
		struct emulation *emu = emulations[i];
		if (type == emu->in->type && code == emu->in->code) {
			int emuvalue = 0;
			if (emu->in->trigger_low < 0 || emu->in->trigger_high > 0) {
				if (emu->in->trigger_low < 0 && value <= emu->in->trigger_low) {
					emuvalue = true;
				} else if (emu->in->trigger_high > 0 && value >= emu->in->trigger_high) {
					emuvalue = true;
				} else {
					emuvalue = false;
				}
			} else {
				emuvalue = value ? true : false;
			}
			if (emuvalue && emu->out->trigger) {
				emuvalue = emu->out->trigger;
			}

			hl_output_inject(emu->out->type, emu->out->code, emuvalue);
			debug_print("Code %d (%d) converted to %d (%d)\n",
				emu->in->code, value,
				emu->out->code, emuvalue);
		}
	}
}

void controller_set_button(struct controller *controller, uint8_t type, uint16_t code, int16_t value) {
	struct button_state *button;

	/* Check whether this button is already in our list. */
	for (int j = 0; j < controller->button_count; j++) {
		if (type == controller->buttons[j]->type && code == controller->buttons[j]->code) {
			/* We're good.  Set it and bail out. */
			controller->buttons[j]->value = value;
			if (type == EV_REL && value != 0) {
				controller->buttons[j]->decay = value;
			}

			return;
		}
	}

	/* Button doesn't exist.  Create it. */
	button = (struct button_state *)calloc(1, sizeof(*button));

	button->type = type;
	button->code = code;
	button->value = value;
	if (type == EV_REL && value != 0) {
		button->decay = value;
	}

	controller->buttons = (struct button_state **)realloc(controller->buttons, (controller->button_count + 1) * sizeof(*controller->buttons));
	controller->buttons[controller->button_count] = button;
	controller->button_count++;
}

void hl_controller_raw(const char *device, const char *rawname, int value) {
	hl_display_output_raw(device, rawname, value);
}

void hl_controller_change(const char *device, int id, uint8_t type, uint16_t code, int16_t value) {
	static struct controller *controller;
	struct hl_skin *skinActive = NULL;
	if (!controller) {
		controller = (struct controller *)calloc(1, sizeof(*controller));
	}

	for (int i = 0; i < hl_skin_count; i++) {
		if (!strcmp(hl_settings->skin->name, hl_skins[i]->name)) {
			skinActive = hl_skins[i];
			break;
		}
	}

	if (!skinActive) {
		return;
	}

	for (int i = 0; i < skinActive->button_count; i++) {
		struct hl_skin_button *skin_button = skinActive->buttons[i];
		if (type == skin_button->type && code == skin_button->code) {
			controller_set_button(controller, type, code, value);

			break;
		}
	}

	for (int i = 0; i < skinActive->axis_count; i++) {
		struct hl_skin_axis *skin_axis = skinActive->axes[i];
		if ((type == skin_axis->type_x && code == skin_axis->code_x) || (type == skin_axis->type_y && code == skin_axis->code_y)) {
			controller_set_button(controller, type, code, value);

			break;
		}
	}
	hl_display_output_controller(controller);

	controller_shortcuts(device, type, code, value);

	controller_emulations(id, type, code, value);
	return;
}
