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

void hl_cli_output_controller(struct controller_display *controller) {
	char pressed[256] = {0};

	for (int j = 0; j < sizeof(controller->mapping) / sizeof(*controller->mapping); j++) {
		struct controller_display_mapping *mapping = &controller->mapping[j];

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
