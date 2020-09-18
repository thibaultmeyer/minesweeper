#ifndef MINESWEEPER_GUI_H
# define MINESWEEPER_GUI_H

# include <gtk/gtk.h>

# define MINESWEEPER_GUI_APPLICATION_ID "com.github.thibaultmeyer.minesweeper"

/**
 * Callback. Configure main window when activated. Only call once.
 *
 * @param app GTK application instance
 * @param user_data Custom user data
 */
void gui_main_callback_app_activate(GtkApplication *app, gpointer user_data);

/**
 * Callback. Main window is destroyed.
 *
 * @param app GTK application instance
 * @param user_data Custom user data
 */
void gui_main_callback_window_destroy(GtkWidget *const widget, gpointer data);

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
