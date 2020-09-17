#include <string.h>
#include "minesweeper.h"

int minesweeper_is_all_cells_open(s_minesweeper_game *const game) {
    if (game != NULL) {
        return (game->open_cell_count == (game->width * game->height) - game->mine_count);
    }

    return (0);
}
