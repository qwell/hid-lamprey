/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef LAMPREY_DISPLAY_H
#define LAMPREY_DISPLAY_H

#include "controller.h"

#if defined(HAVE_CLI) && defined(HAVE_GTK3)
#include "display-cli.h"
#include "display-gtk.h"

#define hl_display_init(...) {\
	hl_cli_init(__VA_ARGS__);\
	hl_gtk_init(__VA_ARGS__);\
}
#define hl_display_output_raw(device, rawname, value) { \
}

#define hl_display_output_controller(controller) {\
	hl_cli_output_controller(controller);\
	hl_gtk_output_controller(controller);\
}
#elif defined(HAVE_CLI) && defined(_WIN32)
#include "display-cli.h"
#include "display-win32.h"

#define hl_display_init(...) {\
	hl_cli_init(__VA_ARGS__);\
	hl_display_win32_init(__VA_ARGS__);\
}

#define hl_display_output_raw(device, rawname, value) { \
	hl_display_win32_output_raw(device, rawname, value);\
}

#define hl_display_output_controller(controller) {\
	hl_cli_output_controller(controller);\
	hl_display_win32_output_controller(controller);\
}
#elif defined(HAVE_CLI)
#include "display-cli.h"

#define hl_display_init(...) hl_cli_init(__VA_ARGS__)
#define hl_display_output_controller(controller) hl_cli_output_controller(controller);
#elif defined(HAVE_GTK3)
#include "display-gtk.h"

#define hl_display_init(...) hl_gtk_init(__VA_ARGS__)
#define hl_display_output_controller(controller) hl_gtk_output_controller(controller);
#elif defined(_WIN32)
#include "display-win32.h"

#define hl_display_init(...) hl_display_win32_init(__VA_ARGS__)
#define hl_display_output_raw(device, rawname, value) { \
	hl_display_win32_output_raw(device, rawname, value);\
}
#define hl_display_output_controller(controller) hl_display_win32_output_controller(controller)
#else
#define hl_display_init(...)
#define hl_display_output_controller(controller)
#endif

#endif
