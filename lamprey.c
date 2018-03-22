#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/settings.h"

#include "include/display.h"
#include "include/evdev.h"
#include "include/xdo.h"

#ifndef __linux__
#error "No.  Go get a real OS and try again."
#endif

int main (int argc, char **argv) {
//	hl_xdo_init();

	pthread_t t_evdev;
	pthread_t t_gtk;

	struct hl_evdev *hl_init;
	struct gtk_args args = {argc, argv};

	/* Initialize evdev data. */
	hl_init = hl_evdev_init();

	/* Spawn off a thread to handle evdev polling. */
	pthread_create(&t_evdev, NULL, hl_evdev_poll, (void *)hl_init);
	pthread_create(&t_gtk, NULL, hl_display_gtk, (void*)&args);

	// Do...stuff.

	pthread_join(t_evdev, NULL);
	free(hl_init);
}
