#ifndef MINESWEEPER_GUI_H
# define MINESWEEPER_GUI_H

# include <gtk/gtk.h>

# define MINESWEEPER_GUI_APPLICATION_ID "com.github.thibaultmeyer.minesweeper"

typedef enum e_game_difficulty {
    GAME_DIFFICULTY_EASY   = 0,
    GAME_DIFFICULTY_NORMAL = 1,
    GAME_DIFFICULTY_HARD   = 2
} e_game_difficulty;

typedef struct s_gui_components {
    GtkWidget *gtk_window;
    GtkWidget *gtk_header_bar;
    guint     gtk_timer_cpu;
    guint     gtk_timer_counter;
} s_gui_components;

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
 * @param app GTK application instance
 * @param window Pointer to the parent window
 */
void gui_main_callback_menu_about(GtkApplication *app, gpointer window);

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
 * @return true if the current GTK theme is dark
 */
gboolean gui_toolbox_is_gtk_dark_theme_enabled(void);

#endif //MINESWEEPER_GUI_H
