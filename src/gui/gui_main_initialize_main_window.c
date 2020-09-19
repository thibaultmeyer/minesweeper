#include "gui.h"
#include "../version.h"

void gui_main_initialize_main_window(GtkApplication *const app) {

    // Create header bar
    GtkHeaderBar *const header_bar = GTK_HEADER_BAR(gtk_header_bar_new());
    gtk_widget_show(GTK_WIDGET(header_bar));
    gtk_header_bar_set_title(header_bar, MINESWEEPER_APPNAME);
    gtk_header_bar_set_show_close_button(header_bar, TRUE);

    // Create the main window
    GtkWindow *const gtk_window = GTK_WINDOW(gtk_application_window_new(app));
    gtk_application_add_window(app, gtk_window);

    gtk_window_set_title(gtk_window, MINESWEEPER_APPNAME);
    gtk_window_set_default_size(gtk_window, 640, 480);
    gtk_window_set_titlebar(gtk_window, GTK_WIDGET(header_bar));
    gtk_window_set_resizable(gtk_window, FALSE);

    g_signal_connect(gtk_window, "destroy", G_CALLBACK(gui_main_callback_window_destroy), app);

    // Create drawing area
    GtkWidget *const gtk_drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(gtk_window), gtk_drawing_area);
    s_window_cfg *const win_cfg = malloc(sizeof(s_window_cfg));
    g_signal_connect(gtk_drawing_area, "size-allocate", G_CALLBACK(gui_main_callback_drawing_area_new_size), win_cfg);
    g_signal_connect(gtk_drawing_area, "draw", G_CALLBACK(gui_main_callback_drawing_area_draw), win_cfg);
    g_signal_connect (gtk_drawing_area, "button-press-event", G_CALLBACK(gui_main_callback_drawing_area_click), NULL);
    g_signal_connect (gtk_drawing_area, "button-release-event", G_CALLBACK(gui_main_callback_drawing_area_click), NULL);
    g_signal_connect (gtk_drawing_area, "motion-notify-event", G_CALLBACK(gui_main_callback_drawing_area_click), NULL);
    g_timeout_add(33, G_SOURCE_FUNC(gui_main_callback_timeout_render), gtk_drawing_area);

    gtk_widget_set_events(gtk_drawing_area, GDK_EXPOSURE_MASK
                                            | GDK_LEAVE_NOTIFY_MASK
                                            | GDK_BUTTON_PRESS_MASK
                                            | GDK_BUTTON_RELEASE_MASK
                                            | GDK_POINTER_MOTION_MASK
                                            | GDK_POINTER_MOTION_HINT_MASK);

    // Show window
    gtk_widget_show_all(GTK_WIDGET(gtk_window));
}
