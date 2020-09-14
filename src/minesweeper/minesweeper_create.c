#include "minesweeper.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

s_minesweeper_game *minesweeper_create(int width, int height, int mine_count) {
    // Prepares the random number generator
    srand(time(NULL) + getpid());

    // Instantiates variables. If malloc() fail: free all allocated memory!
    s_minesweeper_game *const game = malloc(sizeof(s_minesweeper_game));
    if (game == NULL) {
        return NULL;
    }
    memset(game, 0, sizeof(s_minesweeper_game));

    const int array_size = width * height;
    game->cells = malloc(array_size * sizeof(s_minesweeper_cell));
    if (game->cells == NULL) {
        free(game);
        return NULL;
    }
    memset(game->cells, 0, array_size * sizeof(s_minesweeper_cell));
    for (int idx = 0; idx < array_size; ++idx) {
        game->cells[idx] = malloc(sizeof(s_minesweeper_cell));
        memset(game->cells[idx], 0, sizeof(s_minesweeper_cell));

        if (game->cells[idx] == NULL) {
            for (; idx >= 0; --idx) {
                free(game->cells[idx]);
            }

            free(game->cells);
            free(game);
            return NULL;
        }
    }

    // Prepares game
    game->state  = GAME_STATE_PENDING;
    game->width  = width;
    game->height = height;

    // Randomly place mines and increment the mine counter
    while (game->mine_count < mine_count) {
        const int pos_width  = rand() % game->width;
        const int pos_height = rand() % game->height;
        s_minesweeper_cell *const cell = minesweeper_get_cell(game, pos_width, pos_height);

        // Set as mine if possible
        if (cell->has_mine == 0) {
            cell->has_mine = 1;
            game->mine_count += 1;
        }
    }

    return 0;
}
