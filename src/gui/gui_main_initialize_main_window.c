#include "gui.h"
#include "../version.h"

void gui_main_initialize_main_window(GtkApplication *const app) {

    // Create header bar
    GtkHeaderBar *const header_bar = GTK_HEADER_BAR(gtk_header_bar_new());
    gtk_widget_show(GTK_WIDGET(header_bar));
    gtk_header_bar_set_title(header_bar, MINESWEEPER_APPNAME);
    gtk_header_bar_set_show_close_button(header_bar, TRUE);

    // Create the main window
    GtkWindow *const gtk_window = GTK_WINDOW(gtk_application_window_new(app));
    gtk_application_add_window(app, gtk_window);

    gtk_window_set_title(gtk_window, MINESWEEPER_APPNAME);
    gtk_window_set_default_size(gtk_window, 640, 480);
    gtk_window_set_titlebar(gtk_window, GTK_WIDGET(header_bar));
    gtk_window_set_resizable(gtk_window, FALSE);

    g_signal_connect(gtk_window, "destroy", G_CALLBACK(gui_main_callback_window_destroy), app);

    gtk_widget_show_all(GTK_WIDGET(gtk_window));
}
