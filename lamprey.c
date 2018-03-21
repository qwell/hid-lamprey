#include <stdio.h>

#include "include/settings.h"

#include "include/evdev.h"
#include "include/xdo.h"

#ifndef __linux__
#error "No.  Go get a real OS and try again."
#endif

int main () {
//	hl_xdo_init();

	// TODO: ...pthreads
	hl_evdev_start();
}
