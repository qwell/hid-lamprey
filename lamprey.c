/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/display.h"

#if defined(HAVE_XML2)
#include "include/skin.h"
#endif

#if defined(HAVE_XDO)
#include "include/xdo.h"
#endif

#include "include/threads.h"

#if defined(_WIN32)
int main(void) {
	int argc = 0;
	char **argv = NULL;

#if defined(HAVE_CLI)
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif
#else
int main(int argc, char **argv) {
#endif
	setlocale(LC_ALL, "");

#if defined(HAVE_XDO)
	struct hl_xdo *hl_xdo = NULL;
#endif

	printf("Lamprey Version: " PACKAGE_VERSION "\n");

	hl_settings_init();
	hl_settings_load_settings();
	hl_settings_load_mappings();
	hl_settings_load_shortcuts();
	hl_settings_load_emulations();

#if defined(HAVE_XML2)
	if (hl_settings->skin) {
		hl_skin_load(hl_settings->skin->name, hl_settings->skin->background);
	}
#endif

	/* Initialize input data. */
	hl_input_init();

	/* Initialize output data. */
	hl_output_init();

#if defined(HAVE_XDO)
	/* Initialize xdo data. */
	hl_xdo = hl_xdo_init();
#endif

	hl_display_init(argc, argv);

	// Do...stuff.

	hl_output_destroy();

#if defined(HAVE_EVDEV)
	if (hl_input_evdev) {
		hl_thread_join(t_input_evdev);
	}
#endif

#if defined(_WIN32)
	if (t_display_win32) {
		hl_thread_join(t_display_win32);
	}
	if (t_input_xinput) {
		hl_thread_join(t_input_xinput);
	}
#endif

#if defined(HAVE_GTK3)
	hl_thread_join(t_gtk);
#endif

#if defined(HAVE_XDO)
	free(hl_xdo);
#endif

	hl_settings_destroy();

	return 0;
}
