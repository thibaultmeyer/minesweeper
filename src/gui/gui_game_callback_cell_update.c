#include "gui.h"

void gui_game_callback_cell_update(struct s_minesweeper_game *game_instance,
                                   struct s_minesweeper_cell *game_cell,
                                   int x,
                                   int y) {
    (void) game_instance;  // Unused parameter

    GtkWidget *const gtk_button = gtk_grid_get_child_at(gl_context.gtk_grid, x + 1, y + 1);

    if (gtk_button != NULL) {
        if (game_cell->has_mine) {
            gtk_button_set_label(GTK_BUTTON(gtk_button), "\U0001F4A3");
        } else if (game_cell->has_flag) {
            gtk_button_set_label(GTK_BUTTON(gtk_button), "\U0001F6A9");
        } else if (game_cell->is_opened) {
            gtk_widget_set_sensitive(gtk_button, FALSE);
        } else {
            gtk_button_set_label(GTK_BUTTON(gtk_button), "");
        }
    }
}
