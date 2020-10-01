#include "gui.h"
#include "image/gui_image_tile_flag.h"
#include "image/gui_image_tile_mine.h"
#include "image/gui_image_tile_open.h"
#include "image/gui_image_tile_number_1.h"
#include "image/gui_image_tile_number_2.h"
#include "image/gui_image_tile_number_3.h"
#include "image/gui_image_tile_number_4.h"
#include "image/gui_image_tile_number_5.h"
#include "image/gui_image_tile_number_6.h"
#include "image/gui_image_tile_number_7.h"

typedef struct s_cell_tile_image_info {
    const unsigned char *payload;
    const unsigned int  *payload_size;
} s_cell_tile_image_info;

const s_cell_tile_image_info gl_cell_tile_image_info[] = {
        {.payload = gui_image_tile_open_bytes, .payload_size = &gui_image_tile_open_length},
        {.payload = gui_image_tile_number_one_bytes, .payload_size = &gui_image_tile_number_one_length},
        {.payload = gui_image_tile_number_two_bytes, .payload_size = &gui_image_tile_number_two_length},
        {.payload = gui_image_tile_number_three_bytes, .payload_size = &gui_image_tile_number_three_length},
        {.payload = gui_image_tile_number_four_bytes, .payload_size = &gui_image_tile_number_four_length},
        {.payload = gui_image_tile_number_five_bytes, .payload_size = &gui_image_tile_number_five_length},
        {.payload = gui_image_tile_number_six_bytes, .payload_size = &gui_image_tile_number_six_length},
        {.payload = gui_image_tile_number_seven_bytes, .payload_size = &gui_image_tile_number_seven_length},
};

void gui_game_callback_cell_update(s_minesweeper_game *game_instance, s_minesweeper_cell *game_cell, int x, int y) {
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
                                                                                  gl_context.cell_size,
                                                                                  gl_context.cell_size);
            GtkWidget *const image             = gtk_image_new_from_pixbuf(pixbuf_tile_close);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            g_object_unref(pixbuf_tile_close);
        } else if (game_cell->has_mine) {
            GdkPixbuf *const pixbuf_tile_close = gui_image_load_from_memory_scale(gui_image_tile_mine_bytes,
                                                                                  gui_image_tile_mine_length,
                                                                                  gl_context.cell_size,
                                                                                  gl_context.cell_size);
            GtkWidget *const image             = gtk_image_new_from_pixbuf(pixbuf_tile_close);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            g_object_unref(pixbuf_tile_close);
        } else if (game_cell->is_opened) {
            GdkPixbuf *const pixbuf_tile_close = gui_image_load_from_memory_scale(
                    gl_cell_tile_image_info[game_cell->proximity_mine_count].payload,
                    *gl_cell_tile_image_info[game_cell->proximity_mine_count].payload_size,
                    gl_context.cell_size,
                    gl_context.cell_size);
            GtkWidget *const image             = gtk_image_new_from_pixbuf(pixbuf_tile_close);
            gtk_container_add(GTK_CONTAINER(gtk_button), image);
            g_object_unref(pixbuf_tile_close);
        }
        gtk_widget_show_all(GTK_WIDGET(gl_context.gtk_window));
    }
}
