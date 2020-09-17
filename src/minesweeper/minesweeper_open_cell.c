#include <string.h>
#include "minesweeper.h"

void minesweeper_open_cell(s_minesweeper_game *const game, int pos_width, int pos_height) {
    if (game != NULL) {
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

        // Open
        if (cell != NULL && !cell->is_opened) {

            // Remove flag if set
            if (cell->has_flag) {
                cell->has_flag = !cell->has_flag;
            }

            // Set opened
            cell->is_opened = 1;
            game->open_cell_count += 1;

            // Callback
            if (game->function_update_cell_callback != NULL) {
                game->function_update_cell_callback(game, pos_width, pos_height);
            }

            // Check if current cell contains a mine
            if (cell->has_mine) {
                game->state = GAME_STATE_GAME_OVER;

                // Callback
                if (game->function_update_gamestate_callback != NULL) {
                    game->function_update_gamestate_callback(game);
                }

                // Exit function
                return;
            }

            // Try to open another adjacent "empty" cells
            if (cell->proximity_mine_count == 0) {
                // TODO: implements this part
            }

            // Check if all cells are explored
            if (game->state != GAME_STATE_WIN && minesweeper_is_all_cells_open(game)) {
                game->state = GAME_STATE_WIN;

                // Callback
                if (game->function_update_gamestate_callback != NULL) {
                    game->function_update_gamestate_callback(game);
                }
            }
        }
    }
}
