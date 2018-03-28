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

#include "include/display.h"

pthread_t t_gtk;
pthread_mutex_t mutex_gtk = PTHREAD_MUTEX_INITIALIZER;

void print_hello(GtkWidget *widget, gpointer data) {
	g_print("Hello World\n");
}

void hl_gtk_init(int argc, char **argv) {
	struct gtk_args *args = malloc(sizeof(*args));
	args->argc = argc;
	memcpy(args->argv, argv, sizeof(*args->argv));

	/* Spawn another thread for gtk window handling. */
	pthread_mutex_lock(&mutex_gtk);
	pthread_create(&t_gtk, NULL, hl_gtk_show, args);
	pthread_mutex_unlock(&mutex_gtk);
}

void *hl_gtk_show(void *ptr) {
	//TODO Add locking.
	struct gtk_args *args = ptr;

	GtkBuilder *builder;
	GtkWidget *window;

	gtk_init(&args->argc, &args->argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "glade/display.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_display"));
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();

	free(args);

	return NULL;
}
