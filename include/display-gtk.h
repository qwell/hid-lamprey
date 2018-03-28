/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <gtk/gtk.h>

extern pthread_mutex_t mutex_gtk;

struct gtk_args {
	int argc;
	char **argv;
};

void *hl_display_gtk(void *ptr);
