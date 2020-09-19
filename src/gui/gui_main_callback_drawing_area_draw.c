#include "gui.h"

gboolean gui_main_callback_drawing_area_draw(GtkWidget *const widget,
                                             cairo_t *const cairo,
                                             s_window_cfg *const win_cfg) {

    cairo_rectangle(cairo, 0, 0, win_cfg->width, win_cfg->height);
    cairo_fill(cairo);

    cairo_set_source_rgb(cairo, 255, 255, 255);
    cairo_rectangle(cairo, 0, 0, win_cfg->width, 5);
    cairo_rectangle(cairo, 0, 0, 5, win_cfg->height);
    cairo_fill(cairo);






    GdkPixbuf *pix;
    GError *err = NULL;
    /* Create pixbuf */
    pix = gdk_pixbuf_new_from_file("C:\\Users\\thiba\\Desktop\\009.png", &err);
    if(err)
    {
        printf("Error : %s\n", err->message);
        g_error_free(err);
        return FALSE;
    }

    for (int idx_height = 0; idx_height < win_cfg->height; idx_height += 48) {
        for (int idx_width = 0; idx_width < win_cfg->width; idx_width += 48) {
            gdk_cairo_set_source_pixbuf(cairo, pix, idx_width, idx_height);
            cairo_paint(cairo);
        }
    }

    g_object_unref(pix);

    printf("COUCOU\n");

    return (TRUE);
}
