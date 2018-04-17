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
#if defined(HAVE_XDO)
#include "include/xdo.h"
#endif

#include "include/threads.h"

#if defined(_WIN32)
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	return lamprey_entry(0, NULL, hInstance, nCmdShow);
}
#else
int main(int argc, char **argv) {
	return lamprey_entry(argc, argv);
}
#endif

LAMPREY_ENTRY_FUNC {
	setlocale(LC_ALL, "");

#if defined(HAVE_XDO)
	struct hl_xdo *hl_xdo = NULL;
#endif

	printf("Lamprey Version: " PACKAGE_VERSION "\n");

	hl_settings_load();

	/* Initialize input data. */
	hl_input_init();

#if defined(HAVE_XDO)
	/* Initialize xdo data. */
	hl_xdo = hl_xdo_init();
#endif

	hl_display_init(argc, argv);

	// Do...stuff.

#if defined(HAVE_EVDEV)
	if (hl_evdev) {
		hl_thread_join(t_evdev);
	}
#endif

#if defined(_WIN32)
if (t_input_xinput) {
	hl_thread_join(t_input_xinput);
}
#endif


#if defined(HAVE_GTK3)
	pthread_join(t_gtk, NULL);
#endif

#if defined(HAVE_XDO)
	free(hl_xdo);
#endif

	return 0;
}
