#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "minesweeper.h"

void minesweeper_dump(s_minesweeper_game *const game) {
    if (game != NULL) {
        for (int pos_height = 0; pos_height < game->height; ++pos_height) {
            for (int pos_width = 0; pos_width < game->width; ++pos_width) {
                const s_minesweeper_cell *cell = minesweeper_get_cell(game, pos_width, pos_height);

                if (cell->has_flag) {
                    write(STDOUT_FILENO, "F", 1);
                } else if (cell->has_mine) {
                    write(STDOUT_FILENO, "M", 1);
                } else {
                    const unsigned char number = '0' + (char) cell->proximity_mine_count;
                    write(STDOUT_FILENO, &number, 1);
                }
            }
            write(STDOUT_FILENO, "\n", 1);
        }
    }
}
