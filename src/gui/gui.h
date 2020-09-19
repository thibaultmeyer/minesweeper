#ifndef MINESWEEPER_GUI_H
# define MINESWEEPER_GUI_H

# include <gtk/gtk.h>

# define MINESWEEPER_GUI_APPLICATION_ID "com.github.thibaultmeyer.minesweeper"

typedef struct s_window_cfg {
    int width;
    int height;
} s_window_cfg;

/**
 * Callback. Configure main window when activated. Only call once.
 *
 * @param app GTK application instance
 * @param user_data Custom user data
 */
void gui_main_callback_app_activate(GtkApplication *app, gpointer user_data);

/**
 * Callback. Drawing area "click".
 *
 * @param widget Widget instance
 * @param event Current event
 */
gboolean gui_main_callback_drawing_area_click(GtkWidget *widget, GdkEventButton *event);

/**
 * Callback. Drawing area "draw".
 *
 * @param widget Widget instance
 * @param cairo Cairo instance
 * @param win_cfg Windows configuration instance
 */
gboolean gui_main_callback_drawing_area_draw(GtkWidget *widget, cairo_t *cairo, s_window_cfg *win_cfg);

/**
 * Callback. Drawing area dimension changed.
 *
 * @param widget Widget instance
 * @param allocation Allocation information
 * @param win_cfg Windows configuration instance
 */
void gui_main_callback_drawing_area_new_size(GtkWidget *widget, GtkAllocation *allocation, s_window_cfg *win_cfg);

/**
 * Callback. Force render screen.
 *
 * @param data Custom user data
 * @return
 */
gboolean gui_main_callback_timeout_render(GtkWidget *drawing_area);

/**
 * Callback. Main window is destroyed.
 *
 * @param widget Widget instance
 * @param app Pointer to the Gtk application
 */
void gui_main_callback_window_destroy(GtkWidget *widget, gpointer app);

/**
 * Initialize the main window.
 *
 * @param app Instance to the Gtk application instance
 */
void gui_main_initialize_main_window(GtkApplication *app);

/**
 * Check if a GTK dark theme is currently in use.
 *
 * @return true if the current GTK theme is dark
 */
gboolean gui_toolbox_is_gtk_dark_theme_enabled(void);

#endif //MINESWEEPER_GUI_H
