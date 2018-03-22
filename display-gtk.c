#include "include/display.h"

#include <gtk/gtk.h>

static void display_activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

	gtk_widget_show_all (window);
}

void *hl_display_gtk(void *ptr) {
	struct gtk_args *args = ptr;
	GtkApplication *app;
	int status;

	app = gtk_application_new("com.ntbox.lamprey", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (display_activate), NULL);
	status = g_application_run (G_APPLICATION (app), args->argc, args->argv);
	g_object_unref (app);

	return status ? NULL : NULL;
}
