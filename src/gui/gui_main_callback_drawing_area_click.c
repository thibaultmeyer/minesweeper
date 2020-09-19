#include "gui.h"

gboolean gui_main_callback_drawing_area_click(GtkWidget *const widget,
                                              GdkEventButton *const event) {
    (void) widget;  // Unused parameter

    printf("%f %f\n", event->x, event->y);
    return (TRUE);
}
