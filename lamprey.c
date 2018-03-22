#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/settings.h"

#include "include/evdev.h"
#include "include/xdo.h"

#ifndef __linux__
#error "No.  Go get a real OS and try again."
#endif

int main () {
//	hl_xdo_init();

	pthread_t t_evdev;
	struct hl_evdev *hl_init;

	/* Initialize evdev data. */
	hl_init = hl_evdev_init();

	/* Spawn off a thread to handle evdev polling. */
	pthread_create(&t_evdev, NULL, hl_evdev_poll, (void *)hl_init);

	// Do...stuff.

	pthread_join(t_evdev, NULL);
	free(hl_init);
}
