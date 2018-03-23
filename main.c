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
	struct hl_evdev *hl_init;

#ifdef USE_GTK
	pthread_t t_gtk;
	struct gtk_args args = {argc, argv};
#endif

	/* Initialize evdev data. */
	hl_init = hl_evdev_init();

	/* Spawn off a thread to handle evdev polling. */
	pthread_create(&t_evdev, NULL, hl_evdev_poll, (void *)hl_init);

#ifdef USE_GTK
	/* Spawn another thread for gtk window handling. */
	pthread_create(&t_gtk, NULL, hl_display_gtk, (void*)&args);
#endif

	// Do...stuff.

	pthread_join(t_evdev, NULL);
#ifdef USE_GTK
	pthread_join(t_gtk, NULL);
#endif
	free(hl_init);
}
