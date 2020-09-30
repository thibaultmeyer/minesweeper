#include "gui.h"

void gui_game_callback_game_update(struct s_minesweeper_game *game_instance) {
    if (game_instance->state == GAME_STATE_GAME_OVER) {
        GList      *childrens = gtk_container_get_children(GTK_CONTAINER(gl_context.gtk_grid));
        for (GList *iterator  = childrens; iterator != NULL; iterator = iterator->next) {
            gtk_widget_set_sensitive(GTK_WIDGET(iterator->data), FALSE);
        }
        g_list_free(childrens);
    }
}
