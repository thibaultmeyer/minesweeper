#include "gui.h"

void gui_game_callback_game_update(struct s_minesweeper_game *game_instance) {
    if (game_instance->state == GAME_STATE_GAME_OVER) {
        GList      *childrens = gtk_container_get_children(GTK_CONTAINER(gl_context.gtk_grid_game));
        for (GList *iterator  = childrens; iterator != NULL; iterator = iterator->next) {
            gtk_widget_set_sensitive(GTK_WIDGET(iterator->data), FALSE);
        }
        g_list_free(childrens);

        g_source_remove(gl_context.gtk_timer);
        gl_context.gtk_timer = 0;

        GtkWidget *error_msg_dialog = gtk_message_dialog_new(GTK_WINDOW(gl_context.gtk_window),
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_CLOSE,
                                                  "Game Over");
        gtk_dialog_run(GTK_DIALOG(error_msg_dialog));
        gtk_widget_destroy(error_msg_dialog);
    } else if (game_instance->state != GAME_STATE_PLAYING) {
        g_source_remove(gl_context.gtk_timer);
        gl_context.gtk_timer = 0;
    } else {
        gl_context.gtk_timer = g_timeout_add(1000, G_SOURCE_FUNC(gui_game_callback_timer), game_instance);
    }
}
