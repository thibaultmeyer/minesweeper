#include "gui.h"
#include "image/gui_image_tile_close.h"

const s_game_info_difficulty gl_level_difficulty[] = {
        {.width = 8, .height = 8, .mine_count = 10, .cell_size = 48},
        {.width = 16, .height = 16, .mine_count = 40, .cell_size = 32},
        {.width = 30, .height = 16, .mine_count = 99, .cell_size = 24}
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

    // Retrieve size to use for each cells
    gl_context.cell_size = gl_level_difficulty[game_difficulty].cell_size;

    // Load empty tile picture
    GdkPixbuf *const pixbuf_tile_close = gui_image_load_from_memory_scale(gui_image_tile_close_bytes,
                                                                          gui_image_tile_close_length,
                                                                          gl_context.cell_size,
                                                                          gl_context.cell_size);

    // Prepare game board
    gl_context.minesweeper_game = minesweeper_create(gl_level_difficulty[game_difficulty].width,
                                                     gl_level_difficulty[game_difficulty].height,
                                                     gl_level_difficulty[game_difficulty].mine_count,
                                                     &gui_game_callback_game_update,
                                                     &gui_game_callback_cell_update);
    for (int idx_height = 0; idx_height < gl_context.minesweeper_game->height; ++idx_height) {
        for (int idx_width = 0; idx_width < gl_context.minesweeper_game->width; ++idx_width) {
            GtkWidget  *const gtk_button = gtk_button_new();
            s_position *const position   = g_new0(s_position, 1);

            position->x = idx_width;
            position->y = idx_height;

            GtkWidget *const image = gtk_image_new_from_pixbuf(pixbuf_tile_close);
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
    gtk_window_resize(gl_context.gtk_window, 5, 5);
    gtk_window_set_resizable(gl_context.gtk_window, FALSE);

    // Display all
    gtk_widget_show_all(GTK_WIDGET(gl_context.gtk_grid));

    // Clean
    g_object_unref(pixbuf_tile_close);
}
