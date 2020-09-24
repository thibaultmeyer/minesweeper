#include "gui.h"

gboolean  gui_main_callback_click_mine(GtkWidget *button, GdkEventButton *event, s_position *position) {
    if (gl_context.minesweeper_game != NULL) {
        if (event->type == GDK_BUTTON_RELEASE && event->button == 1) {
            minesweeper_open_cell(gl_context.minesweeper_game, position->x, position->y);
        } else if (event->type == GDK_BUTTON_RELEASE && event->button == 3) {
            minesweeper_toggle_flag(gl_context.minesweeper_game, position->x, position->y);
        }
    }

    return TRUE;
}
