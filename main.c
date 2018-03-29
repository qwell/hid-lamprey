/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <locale.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/lamprey.h"

#include "include/display.h"
#include "include/input.h"
#include "include/xdo.h"

int main (int argc, char **argv) {
	setlocale(LC_ALL, "");

#ifdef USE_XDO
	struct hl_xdo *hl_xdo = NULL;
#endif

	printf("Lamprey Version: %s\n", HL_VERSION);

	/* Initialize input data. */
	hl_input_init();

#ifdef USE_XDO
	/* Initialize xdo data. */
	hl_xdo = hl_xdo_init();
#endif

	hl_display_init(argc, argv);

	// Do...stuff.

#ifdef USE_EVDEV
	if (hl_evdev) {
		pthread_join(t_evdev, NULL);
	}
#endif


#ifdef USE_GTK
	pthread_join(t_gtk, NULL);
#endif

#ifdef USE_XDO
	free(hl_xdo);
#endif
}
