#include <string.h>
#include "minesweeper/minesweeper.h"

int main(void) {
    s_minesweeper_game *const game = minesweeper_create(16, 16, 40, NULL, NULL);
    minesweeper_destroy(game);

    return (0);
}
