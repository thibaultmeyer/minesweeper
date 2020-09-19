#include "gui.h"

gboolean gui_main_callback_timeout_render(GtkWidget *const drawing_area) {
    gtk_widget_queue_draw_area(drawing_area, 0, 0, 10, 10);
    return (TRUE);
}
