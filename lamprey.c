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

int main (int argc, char **argv) {
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
		pthread_join(t_evdev, NULL);
	}
#endif


#if defined(HAVE_GTK3)
	pthread_join(t_gtk, NULL);
#endif

#if defined(HAVE_XDO)
	free(hl_xdo);
#endif

	threadtest_init();
	if (t_test) {
		hl_thread_join(t_test);
	}
	if (t_test2) {
		hl_thread_join(t_test2);
	}
	threadtest_destroy();
}
