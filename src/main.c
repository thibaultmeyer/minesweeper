#include <string.h>
#include "minesweeper/minesweeper.h"

int main(void) {
    s_minesweeper_game *const game = minesweeper_create(32, 16, 40, NULL, NULL);
    minesweeper_dump(game);
    minesweeper_open_cell(game, 5, 6);
    minesweeper_destroy(game);

    return (0);
}
