#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

typedef struct s_minesweeper_adjacent_pos_modifier {
    int mod_width;
    int mod_height;
} s_minesweeper_adjacent_pos_modifier;

const s_minesweeper_adjacent_pos_modifier gl_adjacent_pos_modifier[ADJACENT_CELLS_MAX_COUNT] = {
        {.mod_width = 0, .mod_height = -1},
        {.mod_width = 1, .mod_height = -1},
        {.mod_width = 1, .mod_height = 0},
        {.mod_width = 1, .mod_height = 1},
        {.mod_width = 0, .mod_height = 1},
        {.mod_width = -1, .mod_height = 1},
        {.mod_width = -1, .mod_height = 0},
        {.mod_width = -1, .mod_height = -1}
};

s_minesweeper_cell **minesweeper_get_adjacent_cells(s_minesweeper_game *const game, int pos_width, int pos_height) {
    if (game != NULL) {
        s_minesweeper_cell **const adjacent_cells = malloc(ADJACENT_CELLS_MAX_COUNT * sizeof(s_minesweeper_cell *) + 1);
        memset(adjacent_cells, 0, ADJACENT_CELLS_MAX_COUNT * sizeof(s_minesweeper_cell *) + 1);

        int      idx_found = 0;
        for (int idx_iter  = 0; idx_iter < ADJACENT_CELLS_MAX_COUNT; ++idx_iter) {
            const struct s_minesweeper_adjacent_pos_modifier modifier = gl_adjacent_pos_modifier[idx_iter];
            s_minesweeper_cell *const cell = minesweeper_get_cell(game,
                                                                  pos_width + modifier.mod_width,
                                                                  pos_height + modifier.mod_height);
            if (cell != NULL) {
                adjacent_cells[idx_found] = cell;
                idx_found += 1;
            }
        }

        return (adjacent_cells);
    }

    return (NULL);
}
