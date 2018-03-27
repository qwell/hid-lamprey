/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/lamprey.h"

#include "include/display.h"
#include "include/evdev.h"
#include "include/xdo.h"

int main (int argc, char **argv) {
	pthread_t t_evdev;

#ifdef USE_GTK
	pthread_t t_gtk;
	struct gtk_args args = {argc, argv};
#endif

#ifdef USE_XDO
	struct hl_xdo *hl_xdo = NULL;
#endif

	printf("Lamprey Version: %s\n", HL_VERSION);

	pthread_mutex_lock(&mutex_evdev);
	/* Initialize evdev data. */
	if (hl_evdev_init()) {
		/* Spawn off a thread to handle evdev polling. */
		pthread_create(&t_evdev, NULL, hl_evdev_poll, NULL);
	}
	pthread_mutex_unlock(&mutex_evdev);

#ifdef USE_XDO
	/* Initialize xdo data. */
	hl_xdo = hl_xdo_init();
#endif

#ifdef USE_GTK
	/* Spawn another thread for gtk window handling. */
	pthread_create(&t_gtk, NULL, hl_display_gtk, (void*)&args);
#endif

	// Do...stuff.

	if (hl_evdev) {
		pthread_join(t_evdev, NULL);

		pthread_mutex_lock(&mutex_evdev);
		hl_evdev_destroy(hl_evdev);
		pthread_mutex_unlock(&mutex_evdev);
	}

#ifdef USE_GTK
	pthread_join(t_gtk, NULL);
#endif

#ifdef USE_XDO
	free(hl_xdo);
#endif
}
