#include "minesweeper.h"
#include <stdlib.h>
#include <string.h>

void minesweeper_destroy(s_minesweeper_game *game) {
    if (game != NULL) {
        for (int pos_height = 0; pos_height < game->height; ++pos_height) {
            for (int pos_width = 0; pos_width < game->width; ++pos_width) {
                s_minesweeper_cell *const cell = minesweeper_get_cell(game, pos_width, pos_height);

                memset(cell, 0, sizeof(s_minesweeper_cell));
                free(cell);
            }
        }

        memset(game->cells, 0, game->width * game->width * sizeof(s_minesweeper_cell));
        free(game->cells);

        memset(game, 0, sizeof(s_minesweeper_game));
        free(game);
    }
}
