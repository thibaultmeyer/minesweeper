#include "gui.h"
#include "gui_image_logo.h"
#include "../version.h"

void gui_main_callback_menu_about(GtkApplication *const app, gpointer window) {
    (void) app;        // Unused parameter

    GdkPixbuf      *pixbuf    = gui_image_load_from_memory_scale(gui_image_logo_bytes, gui_image_logo_length, 64, 64);
    GtkAboutDialog *gtk_about = GTK_ABOUT_DIALOG(gtk_about_dialog_new());

    gtk_about_dialog_set_comments(gtk_about, MINESWEEPER_DESCRIPTION);
    gtk_about_dialog_set_copyright(gtk_about, MINESWEEPER_COPYRIGHT);
    gtk_about_dialog_set_license_type(gtk_about, GTK_LICENSE_MIT_X11);
    gtk_about_dialog_set_logo(gtk_about, pixbuf);
    gtk_about_dialog_set_program_name(gtk_about, MINESWEEPER_APPNAME);
    gtk_about_dialog_set_version(gtk_about, MINESWEEPER_VERSION);
    gtk_about_dialog_set_website(gtk_about, MINESWEEPER_WEBSITE);

    gtk_window_set_transient_for(GTK_WINDOW(gtk_about), GTK_WINDOW(window));
    gtk_dialog_run(GTK_DIALOG(gtk_about));

    g_object_unref(pixbuf);
    g_object_unref(gtk_about);
}
