#include <string.h>
#include "minesweeper.h"

void minesweeper_change_game_state(s_minesweeper_game *game, e_minesweeper_gamestate game_state) {
    if (game != NULL) {
        game->state = game_state;

        if (game->function_update_gamestate_callback != NULL) {
            game->function_update_gamestate_callback(game);
        }
    }
}
