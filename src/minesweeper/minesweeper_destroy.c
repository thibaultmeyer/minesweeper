#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

void minesweeper_destroy(s_minesweeper_game *const game) {
    if (game == NULL) {
        return;
    }

    const int array_size = game->width * game->height;

    for (int idx = 0; idx < array_size; ++idx) {
        free(game->cells[idx]);
    }

    free(game->cells);
    free(game);
}
