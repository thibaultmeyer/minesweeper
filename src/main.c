#include "minesweeper/minesweeper.h"

int main(void) {
    s_minesweeper_game *game = minesweeper_create(10, 20, 30);
    minesweeper_destroy(game);

    return (0);
}
