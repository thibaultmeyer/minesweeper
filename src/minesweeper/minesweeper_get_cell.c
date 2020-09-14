#include <string.h>
#include "minesweeper.h"

s_minesweeper_cell *minesweeper_get_cell(s_minesweeper_game *game, int pos_width, int pos_height) {
    if (game == NULL || pos_width > game->width || pos_height > game->height) {
        return NULL;
    }

    return game->cells[(pos_height * game->width) + pos_width];
}
