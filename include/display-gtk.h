/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <gtk/gtk.h>

extern hl_thread_t t_gtk;
extern hl_mutex_t mutex_gtk;

void hl_gtk_init(int argc, char **argv);
void *hl_gtk_show(void *ptr);
void hl_gtk_destroy();
void hl_gtk_output_controller(struct controller_display *controller);
