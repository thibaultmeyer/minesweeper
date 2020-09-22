#include "gui.h"
#include "gui_image_logo.h"
#include "../version.h"

void gui_main_callback_menu_about(GtkApplication *const app, gpointer window) {
    (void) app;        // Unused parameter

    GdkPixbuf *const pixbuf = gui_image_load_from_memory_scale(gui_image_logo_bytes, gui_image_logo_length, 64, 64);

    gtk_show_about_dialog(GTK_WINDOW(window),
                          "comments", MINESWEEPER_DESCRIPTION,
                          "copyright", MINESWEEPER_COPYRIGHT,
                          "license_type", GTK_LICENSE_MIT_X11,
                          "logo", pixbuf,
                          "program_name", MINESWEEPER_APPNAME,
                          "version", MINESWEEPER_VERSION,
                          "website", MINESWEEPER_WEBSITE,
                          NULL);
    g_object_unref(pixbuf);
}
