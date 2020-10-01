#include "gui.h"

void gui_main_callback_window_destroy(GtkWidget *const widget, gpointer app) {
    // Stop timer
    if (gl_context.gtk_timer > 0) {
        g_source_remove(gl_context.gtk_timer);
        gl_context.gtk_timer = 0;
    }

    // Free the main Gtk window
    gtk_widget_destroy(widget);

    // Quit Gtk application
    g_application_quit(G_APPLICATION(app));
}
