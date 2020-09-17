#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "minesweeper.h"

s_minesweeper_game *minesweeper_create(int width,
                                       int height,
                                       int mine_count,
                                       void (*function_update_gamestate_callback)(struct s_minesweeper_game *),
                                       void (*function_update_cell_callback)(struct s_minesweeper_game *, int, int)) {
    // Prepares the random number generator
    srand(time(NULL) + getpid());

    // Instantiates variables. If malloc() fail: free all allocated memory!
    s_minesweeper_game *const game = malloc(sizeof(s_minesweeper_game));
    if (game == NULL) {
        return (NULL);
    }
    memset(game, 0, sizeof(s_minesweeper_game));

    const int array_size = width * height;
    game->cells = malloc(array_size * sizeof(s_minesweeper_cell));
    if (game->cells == NULL) {
        free(game);
        return (NULL);
    }
    memset(game->cells, 0, array_size * sizeof(s_minesweeper_cell));

    for (int idx = 0; idx < array_size; ++idx) {
        game->cells[idx] = malloc(sizeof(s_minesweeper_cell));
        memset(game->cells[idx], 0, sizeof(s_minesweeper_cell));

        if (game->cells[idx] == NULL) {
            while (idx >= 0) {
                free(game->cells[idx]);
                idx -= 1;
            }

            free(game->cells);
            free(game);
            return (NULL);
        }
    }

    // Prepares game
    game->state                              = GAME_STATE_PENDING;
    game->width                              = width;
    game->height                             = height;
    game->function_update_gamestate_callback = function_update_gamestate_callback;
    game->function_update_cell_callback      = function_update_cell_callback;

    // Randomly place mines and increment the mine counter
    while (game->mine_count < mine_count) {
        const int pos_width  = rand() % game->width;
        const int pos_height = rand() % game->height;
        s_minesweeper_cell *const cell = minesweeper_get_cell(game, pos_width, pos_height);

        // Set as mine if possible
        if (cell->has_mine == 0) {
            cell->has_mine = 1;
            game->mine_count += 1;

            // Update mine count on all adjacent cells
            s_minesweeper_cell **const adjacent_cells = minesweeper_get_adjacent_cells(game, pos_width, pos_height);
            for (int idx = 0; idx < ADJACENT_CELLS_MAX_COUNT; ++idx) {
                if (adjacent_cells[idx] != NULL) {
                    adjacent_cells[idx]->proximity_mine_count += 1;
                }
            }
            free(adjacent_cells);
        }
    }

    return (game);
}
