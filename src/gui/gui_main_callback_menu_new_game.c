#include "gui.h"
#include "image/gui_image_tile_empty.h"

const s_game_info_difficulty gl_level_difficulty[] = {
        {8,  8,  10},
        {16, 16, 40},
        {30, 16, 99}
};

static void free_on_closure_notify(gpointer data, GClosure *closure) {
    (void) closure;  // Unused parameter

    g_free(data);
}

void gui_main_callback_menu_new_game(GtkButton *button, e_game_difficulty game_difficulty) {
    (void) button;  // Unused parameter

    // Clean
    if (gl_context.minesweeper_game != NULL) {
        minesweeper_destroy(gl_context.minesweeper_game);

        GList      *childrens = gtk_container_get_children(GTK_CONTAINER(gl_context.gtk_grid));
        for (GList *iterator  = childrens; iterator != NULL; iterator = iterator->next) {
            gtk_container_remove(GTK_CONTAINER(gl_context.gtk_grid), GTK_WIDGET(iterator->data));
        }
        g_list_free(childrens);
    }

    // Retrieve parameters
    const int width      = gl_level_difficulty[game_difficulty].width;
    const int height     = gl_level_difficulty[game_difficulty].height;
    const int mine_count = gl_level_difficulty[game_difficulty].mine_count;

    // Load empty tile picture
    GdkPixbuf *const pixbuf_tile_empty = gui_image_load_from_memory_scale(gui_image_tile_empty_bytes,
                                                                          gui_image_tile_empty_length,
                                                                          48,
                                                                          48);

    // Prepare game board
    gl_context.minesweeper_game = minesweeper_create(width, height, mine_count, NULL, &gui_game_callback_cell_update);
    for (int idx_height = 0; idx_height < gl_context.minesweeper_game->height; ++idx_height) {
        for (int idx_width = 0; idx_width < gl_context.minesweeper_game->width; ++idx_width) {
            GtkWidget  *const gtk_button = gtk_button_new();
            s_position *const position   = g_new0(s_position, 1);

            position->x = idx_width;
            position->y = idx_height;

            GtkWidget *const image = gtk_image_new_from_pixbuf(pixbuf_tile_empty);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            gtk_button_set_relief(GTK_BUTTON (gtk_button), GTK_RELIEF_NONE);
            gtk_widget_set_name(gtk_button, "mine");

            gtk_grid_attach(gl_context.gtk_grid, gtk_button, idx_width + 1, idx_height + 1, 1, 1);
            g_signal_connect_data(gtk_button,
                                  "button-release-event",
                                  G_CALLBACK(gui_main_callback_click_mine),
                                  position,
                                  free_on_closure_notify,
                                  0);
        }
    }

    // Resize window
    gtk_window_set_resizable(gl_context.gtk_window, TRUE);
    gtk_window_resize(gl_context.gtk_window, 10, 10);
    gtk_window_set_resizable(gl_context.gtk_window, FALSE);

    // Display all
    gtk_widget_show_all(GTK_WIDGET(gl_context.gtk_grid));
}
