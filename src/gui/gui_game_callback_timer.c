#include "gui.h"

gboolean gui_game_callback_timer(gpointer user_data) {
    s_minesweeper_game *const game = user_data;

    // Increments timer
    game->timer += 1;
    if (game->timer >= 1000) {
        minesweeper_change_game_state(game, GAME_STATE_GAME_OVER);
    }

    // Reset HUD
    gchar *const g_str_timer = g_strdup_printf("%03i", game->timer);
    gtk_label_set_text(gl_context.gtk_label_timer, g_str_timer);
    g_free(g_str_timer);

    return (TRUE);
}
