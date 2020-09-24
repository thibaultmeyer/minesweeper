#ifndef MINESWEEPER_GAMELOGIC_H
# define MINESWEEPER_GAMELOGIC_H
# define ADJACENT_CELLS_MAX_COUNT 8

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

    void (*function_update_gamestate_callback)(struct s_minesweeper_game *);

    void (*function_update_cell_callback)(struct s_minesweeper_game *, struct s_minesweeper_cell *, int, int);
} s_minesweeper_game;

/**
 * Creates a new game instance. This function will return
 * NULL in case of memory allocation error.
 *
 * @param width The desired width
 * @param height The desired height
 * @param mine_count The desired number of mines
 * @param function_update_gamestate_callback Gamestate update callback
 * @param function_update_cell_callback Cell update callback
 * @return the newly created game instance
 */
s_minesweeper_game *minesweeper_create(int width,
                                       int height,
                                       int mine_count,
                                       void (*function_update_gamestate_callback)(struct s_minesweeper_game *),
                                       void (*function_update_cell_callback)(struct s_minesweeper_game *,
                                                                             struct s_minesweeper_cell *,
                                                                             int,
                                                                             int));

/**
 * Destroys the game instance.
 *
 * @param game The game instance to destroy
 */
void minesweeper_destroy(s_minesweeper_game *game);

/**
 * Retrieves the cell located at the given position.
 *
 * @param game The game instance
 * @param pos_width X (width) position
 * @param pos_height Y (height) position
 * @return the cell, otherwise, NULL
 */
s_minesweeper_cell *minesweeper_get_cell(s_minesweeper_game *game, int pos_width, int pos_height);

/**
 * Checks that all cells are open.
 *
 * @param game The game instance
 * @return 1 if all cells are open, otherwise, 0
 */
int minesweeper_is_all_cells_open(s_minesweeper_game *game);

/**
 * Adds or removes flag on the cell identified by given coordinates.
 *
 * @param game The game instance
 */
void minesweeper_toggle_flag(s_minesweeper_game *game, int pos_width, int pos_height);

/**
 * Adds or removes flag on the cell identified by given coordinates.
 *
 * @param game The game instance
 */
void minesweeper_open_cell(s_minesweeper_game *game, int pos_width, int pos_height);

/**
 * Retrieves all adjacent cells. The returned array ending with NULL value.
 * Only the first dimension must be free !
 *
 * @param game The game instance
 * @param pos_width X (width) position
 * @param pos_height Y (height) position
 * @return an array containing adjacent cells (pointer)
 */
s_minesweeper_cell **minesweeper_get_adjacent_cells(s_minesweeper_game *game, int pos_width, int pos_height);

/**
 * Dump the current game to the console.
 *
 * @param game The game instance
 */
void minesweeper_dump(s_minesweeper_game *game);

#endif //MINESWEEPER_GAMELOGIC_H
