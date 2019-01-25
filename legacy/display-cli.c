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

void hl_cli_init(int argc, char **argv) {
	printf("CLI Initialized.\n");
}

void hl_cli_output_controller(struct controller *controller) {
	char pressed[256] = {0};
	struct hl_skin *skinActive = NULL;

	if (!controller) {
		return;
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

	for (int i = 0; i < controller->button_count; i++) {
		struct button_state *button = controller->buttons[i];

		if (button->value) {
			for (int j = 0; j < skinActive->button_count; j++) {
				if (!strstr(pressed, skinActive->buttons[j]->cli_char)) {
					strcat(pressed, skinActive->buttons[j]->cli_char);
				}
			}

			for (int j = 0; j < skinActive->axis_count; j++) {
				if (!strstr(pressed, skinActive->axes[j]->cli_char)) {
					strcat(pressed, skinActive->axes[j]->cli_char);
				}
			}
		}
	}

	printf("\n");
	for (int i = 0; i < sizeof(skinActive->cli_layout); i++) {
		char layout_char[5];
		char *ptr = layout_char;
		*ptr = skinActive->cli_layout[i];

		/* Deal with UTF-8 characters. */
		while ((skinActive->cli_layout[i + 1] & 0xC0) == 0x80) {
			*++ptr = skinActive->cli_layout[++i];
		}

		*++ptr = '\0';

		if (strlen(layout_char) == 0) {
			break;
		}

		if (strstr(pressed, layout_char)) {
#if defined(_WIN32)
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO console;
			WORD attr;
			GetConsoleScreenBufferInfo(handle, &console);
			attr = console.wAttributes;
			SetConsoleTextAttribute(handle, FOREGROUND_RED);
			printf("%s", layout_char);
			SetConsoleTextAttribute(handle, attr);
#else
			printf("\e[31m%s\e[39m", layout_char);
#endif
		} else {
			printf("%s", layout_char);
		}
	}
	printf("\n");
}
