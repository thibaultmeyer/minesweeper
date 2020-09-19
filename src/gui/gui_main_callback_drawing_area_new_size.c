#include "gui.h"

void gui_main_callback_drawing_area_new_size(GtkWidget *const widget,
                                             GtkAllocation *const allocation,
                                             s_window_cfg *const win_cfg) {
    (void) widget;  // Unused parameter

    win_cfg->height = allocation->height;
    win_cfg->width  = allocation->width;
}
