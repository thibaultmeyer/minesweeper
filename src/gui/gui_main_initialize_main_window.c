#include "gui.h"
#include "image/gui_image_about_dark.h"
#include "image/gui_image_about_light.h"
#include "image/gui_image_newgame_dark.h"
#include "image/gui_image_newgame_light.h"
#include "../version.h"

void gui_main_initialize_main_window(GtkApplication *const app) {

    // Create the main window
    GtkWindow *const gtk_window = GTK_WINDOW(gtk_application_window_new(app));
    gtk_application_add_window(app, gtk_window);

    gtk_window_set_title(gtk_window, MINESWEEPER_APPNAME);
    gtk_window_set_default_size(gtk_window, 640, 480);
    gtk_window_set_resizable(gtk_window, FALSE);

    g_signal_connect(gtk_window, "destroy", G_CALLBACK(gui_main_callback_window_destroy), app);

    // Check dark theme
    gboolean is_dark_theme_enabled = gui_toolbox_is_gtk_dark_theme_enabled();

    // Create header bar
    GtkHeaderBar *const header_bar = GTK_HEADER_BAR(gtk_header_bar_new());
    gtk_widget_show(GTK_WIDGET(header_bar));
    gtk_header_bar_set_title(header_bar, MINESWEEPER_APPNAME);
    gtk_header_bar_set_show_close_button(header_bar, TRUE);
    gtk_window_set_titlebar(gtk_window, GTK_WIDGET(header_bar));

    // Button "New Game"
    GtkWidget *button = gtk_menu_button_new();
    GdkPixbuf *pixbuf = is_dark_theme_enabled ? gui_image_load_from_memory_scale(gui_image_newgame_light_bytes,
                                                                                 gui_image_newgame_light_length,
                                                                                 20,
                                                                                 20)
                                              : gui_image_load_from_memory_scale(gui_image_newgame_dark_bytes,
                                                                                 gui_image_newgame_dark_length,
                                                                                 20,
                                                                                 20);
    GtkWidget *image  = gtk_image_new_from_pixbuf(pixbuf);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_set_tooltip_text(button, "New Game");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), button);

    // Menu "New Game"
    GtkWidget *menu_new_game = gtk_menu_new();
    gtk_menu_button_set_popup(GTK_MENU_BUTTON(button), menu_new_game);

    // Menu "New Game": Add "easy" option
    GtkWidget *menu_new_game_item = gtk_menu_item_new_with_label("Easy");
    gtk_container_add(GTK_CONTAINER(menu_new_game), menu_new_game_item);
    gtk_menu_attach(GTK_MENU(menu_new_game), menu_new_game_item, 0, 1, 0, 1);
    //g_signal_connect(menu_item_state_load, "activate", G_CALLBACK(), NULL);

    // Menu "New Game": Add "normal" option
    menu_new_game_item = gtk_menu_item_new_with_label("Normal");
    gtk_container_add(GTK_CONTAINER(menu_new_game), menu_new_game_item);
    gtk_menu_attach(GTK_MENU(menu_new_game), menu_new_game_item, 0, 1, 1, 2);
    //g_signal_connect(menu_item_state_load, "activate", G_CALLBACK(), NULL);

    // Menu "New Game": Add "hard" option
    menu_new_game_item = gtk_menu_item_new_with_label("Hard");
    gtk_container_add(GTK_CONTAINER(menu_new_game), menu_new_game_item);
    gtk_menu_attach(GTK_MENU(menu_new_game), menu_new_game_item, 0, 1, 2, 3);
    //g_signal_connect(menu_item_state_load, "activate", G_CALLBACK(), NULL);

    // Menu "New Game": Display
    gtk_widget_show_all(menu_new_game);

    // Button "About"
    button = gtk_button_new();
    pixbuf = is_dark_theme_enabled ? gui_image_load_from_memory_scale(gui_image_about_light_bytes,
                                                                      gui_image_about_light_length,
                                                                      20,
                                                                      20)
                                   : gui_image_load_from_memory_scale(gui_image_about_dark_bytes,
                                                                      gui_image_about_dark_length,
                                                                      20,
                                                                      20);
    image  = gtk_image_new_from_pixbuf(pixbuf);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_set_tooltip_text(button, "About");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), button);
    g_signal_connect(button, "clicked", G_CALLBACK(gui_main_callback_menu_about), gtk_window);

    // Create grid
    GtkWidget *const gtk_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(gtk_window), gtk_grid);

    // Show
    gtk_widget_show_all(GTK_WIDGET(gtk_window));
}
