#include "gui.h"

void gui_main_callback_window_destroy(GtkWidget *const widget, gpointer app) {

    // Free the main Gtk window
    gtk_widget_destroy(widget);

    // Quit Gtk application
    g_application_quit(G_APPLICATION(app));
}
