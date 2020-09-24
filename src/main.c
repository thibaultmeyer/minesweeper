#include "gui/gui.h"

s_context gl_context = {0};

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);
    GtkApplication *const app = gtk_application_new(MINESWEEPER_GUI_APPLICATION_ID, G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(gui_main_callback_app_activate), NULL);
    const int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    // Return status
    return (status);
}
