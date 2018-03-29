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

const struct shortcut shortcuts[] = {
	SHORTCUTS
};

void hl_controller_change(const char *device, int id, uint8_t type, uint16_t code, int16_t value) {
	for (int i = 0; i < sizeof(controller_displays) / sizeof(*controller_displays); i++) {
		struct controller_display *controller = &controller_displays[i];
		int usedevice = 0;

		char pressed[256] = {0};

		for (int j = 0; j < sizeof(controller->devices) / sizeof(*controller->devices); j++) {
			if (!controller->devices[j]) {
				if (j == 0) {
					usedevice = 1;
				}
				break;
			}
			if (!strcmp(device, controller->devices[j])) {
				usedevice = 1;
				break;
			}
		}
		if (!usedevice) {
			continue;
		}

		for (int j = 0; j < sizeof(controller->mapping) / sizeof(*controller->mapping); j++) {
			struct controller_display_mapping *mapping = &controller->mapping[j];

			for (int k = 0; k < sizeof(mapping->buttons) / sizeof(*mapping->buttons); k++) {
				const struct button_trigger *button = &mapping->buttons[k];

				if (code == button->code && type == button->type) {
					/* Things may not work properly if you have multiple buttons
					 * assigned to a mapping that are concurrently triggered.
					 */
					if (button->triggervalue < 0) {
						mapping->value = (value <= button->triggervalue);
					} else if (button->triggervalue > 0) {
						mapping->value = (value >= button->triggervalue);
					} else {
						mapping->value = value ? 1 : 0;
					}
				}

			}

			if (mapping->value && !strstr(pressed, mapping->display)) {
				strcat(pressed, mapping->display);
			}
		}

		printf("\n");
		for (int j = 0; j < sizeof(controller->layout); j++) {
			char layout_char[5];
			char *ptr = layout_char;
			*ptr = controller->layout[j];

			/* Deal with UTF-8 characters. */
			while ((controller->layout[j + 1] & 0xC0) == 0x80) {
				*++ptr = controller->layout[++j];
			}

			*++ptr = '\0';

			if (strlen(layout_char) == 0) {
				break;
			}

			if (strstr(pressed, layout_char)) {
				printf("\e[31m%s\e[39m", layout_char);
			} else {
				printf("%s", layout_char);
			}
		}
		printf("\n");
	}

/* TODO Do something with the shortcuts.
	for (int i = 0; i < sizeof(shortcuts) / sizeof(*shortcuts); i++) {
		const struct shortcut *shortcut = &shortcuts[i];
		for (int j = 0; j < sizeof(shortcut->button_list) / sizeof(*shortcut->button_list); j++) {
			const struct button *button = &shortcut->button_list[j];
			for (int k = 0; k < sizeof(button->buttons) / sizeof(*button->buttons); k++) {
				const struct button_trigger *map = &button->buttons[k];
				if (map->type != 0) {
					printf("Button %d (%d) [%d]\n", map->code, map->type, map->triggervalue);
				}
			}
		}
	}
*/

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
	return;
}
