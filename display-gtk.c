#include "include/display.h"

#include <gtk/gtk.h>

void print_hello(GtkWidget *widget, gpointer data) {
	g_print("Hello World\n");
}
void *hl_display_gtk(void *ptr) {
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
	return NULL;
}
