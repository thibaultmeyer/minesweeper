#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

static void minesweeper_retrieve_cell_position(s_minesweeper_game *const game,
                                               s_minesweeper_cell *const cell,
                                               int *const pos_width,
                                               int *const pos_height) {
    *pos_width           = -1;
    *pos_height          = -1;
    const int array_size = game->width * game->height;

    for (int idx = 0; idx < array_size; ++idx) {
        if (game->cells[idx] == cell) {
            *pos_width  = idx % game->width;
            *pos_height = idx / game->width;
            break;
        }
    }
}

void minesweeper_open_cell(s_minesweeper_game *const game, int pos_width, int pos_height) {
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
            s_minesweeper_cell **const adjacent_cells = minesweeper_get_adjacent_cells(game, pos_width, pos_height);

            if (adjacent_cells != NULL) {
                for (int idx = 0; idx < ADJACENT_CELLS_MAX_COUNT; ++idx) {
                    if (adjacent_cells[idx] != NULL) {
                        int cell_pos_width  = -1;
                        int cell_pos_height = -1;

                        minesweeper_retrieve_cell_position(game,
                                                           adjacent_cells[idx],
                                                           &cell_pos_width,
                                                           &cell_pos_height);
                        minesweeper_open_cell(game, cell_pos_width, cell_pos_height);
                    }
                }

                free(adjacent_cells);
            }
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
