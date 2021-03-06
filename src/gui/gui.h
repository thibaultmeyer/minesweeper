#ifndef MINESWEEPER_GUI_H
# define MINESWEEPER_GUI_H

# include <gtk/gtk.h>
# include "../minesweeper/minesweeper.h"

# define MINESWEEPER_GUI_APPLICATION_ID             "com.github.thibaultmeyer.minesweeper"
# define MINESWEEPER_GUI_HEADERBAR_BTN_IMG_HEIGHT   20
# define MINESWEEPER_GUI_HEADERBAR_BTN_IMG_WIDTH    20

typedef enum e_game_difficulty {
    GAME_DIFFICULTY_EASY   = 0,
    GAME_DIFFICULTY_NORMAL = 1,
    GAME_DIFFICULTY_HARD   = 2
} e_game_difficulty;

typedef struct s_game_info_difficulty {
    int width;
    int height;
    int mine_count;
    int cell_size;
} s_game_info_difficulty;

typedef struct s_context {
    GtkWindow          *gtk_window;
    GtkGrid            *gtk_grid_game;
    GtkLabel           *gtk_label_timer;
    GtkLabel           *gtk_label_flag_left;
    guint              gtk_timer;
    s_minesweeper_game *minesweeper_game;
    int                cell_size;
} s_context;

typedef struct s_position {
    int x;
    int y;
} s_position;

/**
 * Global context.
 */
extern s_context gl_context;

/**
 * Callback. When a cell is updated.
 *
 * @param game_instance  The current game instance
 * @param game_cell  The updated cell
 * @param x The updated cell position (X)
 * @param y The updated cell position (Y)
 */
void gui_game_callback_cell_update(s_minesweeper_game *game_instance, s_minesweeper_cell *game_cell, int x, int y);

/**
 * Callback. When gam state is updated.
 *
 * @param game_instance  The current game instance
 */
void gui_game_callback_game_update(s_minesweeper_game *game_instance);

/**
 * Callback. Update timer.
 *
 * @param user_data Data passed to the function
 * @return TRUE if callback need to be call again
 */
gboolean gui_game_callback_timer(gpointer user_data);

/**
 * Load image from memory and scale it.
 *
 * @param data Image data
 * @param length Image data length
 * @param width New image width
 * @param height New image height
 */
GdkPixbuf *gui_image_load_from_memory_scale(const unsigned char *data,
                                            unsigned int length,
                                            int width,
                                            int height);

/**
 * Callback. Configure main window when activated. Only call once.
 *
 * @param app GTK application instance
 * @param user_data Custom user data
 */
void gui_main_callback_app_activate(GtkApplication *app, gpointer user_data);

/**
 * Callback. Show About dialog.
 *
 * @param button The object that received the signal
 * @param event The current click event
 * @param position The position where click on the game
 */
gboolean gui_main_callback_click_mine(GtkWidget *button, GdkEventButton *event, s_position *position);

/**
 * Callback. Show About dialog.
 *
 * @param button The object that received the signal
 * @param window Pointer to the parent window
 */
void gui_main_callback_menu_about(GtkButton *button, gpointer window);

/**
 * Callback. Show About dialog.
 *
 * @param button The object that received the signal
 * @param game_difficulty The game difficulty
 */
void gui_main_callback_menu_new_game(GtkButton *button, e_game_difficulty game_difficulty);

/**
 * Callback. Main window is destroyed.
 *
 * @param widget Widget instance (the main Gtk window)
 * @param app Pointer to the current application
 */
void gui_main_callback_window_destroy(GtkWidget *widget, gpointer app);

/**
 * Initialize the main window.
 */
void gui_main_initialize_main_window(GtkApplication *app);

/**
 * Check if a GTK dark theme is currently in use.
 *
 * @param widget Widget instance used to determine if dark mode is enable
 * @return true if the current GTK theme is dark
 */
gboolean gui_toolbox_is_gtk_dark_theme_enabled(GtkWidget *widget);

#endif //MINESWEEPER_GUI_H
