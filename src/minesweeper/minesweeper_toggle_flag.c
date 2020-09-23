#include <string.h>
#include "minesweeper.h"

void minesweeper_toggle_flag(s_minesweeper_game *const game, int pos_width, int pos_height) {
    if (game == NULL) {
        return;
    }

    // Is first move? Change game state
    if (game->state == GAME_STATE_PENDING) {
        game->state = GAME_STATE_PLAYING;

        // Callback
        if (game->function_update_gamestate_callback != NULL) {
            game->function_update_gamestate_callback(game);
        }
    }

    // Retrieves cell
    s_minesweeper_cell *const cell = minesweeper_get_cell(game, pos_width, pos_height);

    // Flag
    if (cell != NULL && !cell->is_opened) {
        cell->has_flag = !cell->has_flag;
        game->flag_count += cell->has_flag ? 1 : -1;

        // Callback
        if (game->function_update_cell_callback != NULL) {
            game->function_update_cell_callback(game, pos_width, pos_height);
        }
    }
}
