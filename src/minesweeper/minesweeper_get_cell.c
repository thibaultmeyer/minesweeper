#include <string.h>
#include "minesweeper.h"

s_minesweeper_cell *minesweeper_get_cell(s_minesweeper_game *const game, int pos_width, int pos_height) {
    if (game == NULL || pos_width < 0 || pos_height < 0) {
        return (NULL);
    }

    const int idx = (pos_height * game->width) + pos_width;

    if (idx >= (game->width * game->height)) {
        return (NULL);
    }

    return (game->cells[idx]);
}
