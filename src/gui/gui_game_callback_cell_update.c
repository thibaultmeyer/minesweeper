#include "gui.h"
#include "image/gui_image_tile_flag.h"
#include "image/gui_image_tile_mine.h"
#include "image/gui_image_tile_open.h"

void gui_game_callback_cell_update(struct s_minesweeper_game *game_instance,
                                   struct s_minesweeper_cell *game_cell,
                                   int x,
                                   int y) {
    (void) game_instance;  // Unused parameter

    GtkWidget *const gtk_button = gtk_grid_get_child_at(gl_context.gtk_grid, x + 1, y + 1);

    if (gtk_button != NULL) {
        GList      *childrens = gtk_container_get_children(GTK_CONTAINER(gtk_button));
        for (GList *iterator  = childrens; iterator != NULL; iterator = iterator->next) {
            gtk_container_remove(GTK_CONTAINER(gl_context.gtk_grid), GTK_WIDGET(iterator->data));
            gtk_widget_destroy(GTK_WIDGET(iterator->data));
        }
        g_list_free(childrens);

        if (game_cell->has_flag) {
            GdkPixbuf *const pixbuf_tile_close = gui_image_load_from_memory_scale(gui_image_tile_flag_bytes,
                                                                                  gui_image_tile_flag_length,
                                                                                  48,
                                                                                  48);
            GtkWidget *const image = gtk_image_new_from_pixbuf(pixbuf_tile_close);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            g_object_unref(pixbuf_tile_close);
        } else if (game_cell->has_mine) {
            GdkPixbuf *const pixbuf_tile_close = gui_image_load_from_memory_scale(gui_image_tile_mine_bytes,
                                                                                  gui_image_tile_mine_length,
                                                                                  48,
                                                                                  48);
            GtkWidget *const image = gtk_image_new_from_pixbuf(pixbuf_tile_close);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            g_object_unref(pixbuf_tile_close);
        } else if (game_cell->is_opened) {


            GdkPixbuf *const pixbuf_tile_close = gui_image_load_from_memory_scale(gui_image_tile_open_bytes,
                                                                                  gui_image_tile_open_length,
                                                                                  48,
                                                                                  48);
            GtkWidget *const image = gtk_image_new_from_pixbuf(pixbuf_tile_close);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            g_object_unref(pixbuf_tile_close);
        }
        gtk_widget_show_all(GTK_WIDGET(gl_context.gtk_window));
    }
}
