#include "gui.h"

void gui_main_callback_app_activate(GtkApplication *const app, gpointer user_data) {
    (void) user_data;  // Unused parameter

    gui_main_initialize_main_window(app);
}
