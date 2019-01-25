/*
 * Copyright (C) 2018, Jason Parker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <stdlib.h>
#include <string.h>

#include "include/lamprey.h"

#include "include/controller.h"
#include "include/display.h"

hl_thread_t t_gtk;
hl_mutex_t mutex_gtk;

void print_hello(GtkWidget *widget, gpointer data) {
	g_print("Hello World\n");
}

void hl_gtk_init(int argc, char **argv) {
	gtk_init(&argc, &argv);

	/* Spawn another thread for gtk window handling. */
	hl_mutex_create(&mutex_gtk);
	hl_mutex_lock(&mutex_gtk);
	hl_thread_create(&t_gtk, hl_gtk_show, NULL);
	hl_mutex_unlock(&mutex_gtk);
}

void *hl_gtk_show(void *ptr) {
	//TODO Add locking?

	GtkBuilder *builder;
	GtkWidget *window;

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "glade/display.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_display"));
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();

	hl_gtk_destroy();

	return NULL;
}

void hl_gtk_destroy() {
	hl_thread_exit();
}

void hl_gtk_output_controller(struct controller *controller) {
}
