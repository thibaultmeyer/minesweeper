#ifndef MINESWEEPER_GAMELOGIC_H
# define MINESWEEPER_GAMELOGIC_H

typedef enum e_minesweeper_gamestate {
    GAME_STATE_PENDING   = 0,
    GAME_STATE_PLAYING   = 1,
    GAME_STATE_WIN       = 2,
    GAME_STATE_GAME_OVER = 3,
} e_minesweeper_gamestate;

typedef struct s_minesweeper_cell {
    int is_opened;
    int has_flag;
    int has_mine;
    int proximity_mine_count;
} s_minesweeper_cell;

typedef struct s_minesweeper_game {
    int                     width;
    int                     height;
    int                     mine_count;
    int                     flag_count;
    int                     open_cell_count;
    s_minesweeper_cell      **cells;
    e_minesweeper_gamestate state;

    void (*function_update_cell_callback)(int, int);
} s_minesweeper_game;

typedef struct s_minesweeper_adjacent_pos_modifier {
    int mod_width;
    int mod_height;
} s_minesweeper_adjacent_pos_modifier;

/**
 * Creates a new game instance. This function will return
 * NULL in case of memory allocation error.
 *
 * @param width The desired width
 * @param height The desired height
 * @param mine_count The desired number of mines
 * @return the newly created game instance
 */
s_minesweeper_game *minesweeper_create(int width, int height, int mine_count);

/**
 * Destroys the game instance.
 *
 * @param game The game instance to destroy
 */
void minesweeper_destroy(s_minesweeper_game *game);

/**
 * Retrieves the cell located at the given position.
 * @param game The game instance
 * @param pos_width X (width) position
 * @param pos_height Y (height) position
 * @return the cell, otherwise, NULL
 */
s_minesweeper_cell *minesweeper_get_cell(s_minesweeper_game *game, int pos_width, int pos_height);

#endif //MINESWEEPER_GAMELOGIC_H
