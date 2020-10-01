#include "gui.h"
#include "image/gui_image_about_dark.h"
#include "image/gui_image_about_light.h"
#include "image/gui_image_newgame_dark.h"
#include "image/gui_image_newgame_light.h"
#include "../version.h"

void gui_main_initialize_main_window(GtkApplication *const app) {

    // Create the main window
    gl_context.gtk_window = GTK_WINDOW(gtk_application_window_new(app));
    gtk_application_add_window(app, gl_context.gtk_window);

    gtk_window_set_title(gl_context.gtk_window, MINESWEEPER_APPNAME);
    g_signal_connect(gl_context.gtk_window, "destroy", G_CALLBACK(gui_main_callback_window_destroy), app);

    // Check dark theme
    gboolean is_dark_theme_enabled = gui_toolbox_is_gtk_dark_theme_enabled();

    // Create header bar
    GtkHeaderBar *const header_bar = GTK_HEADER_BAR(gtk_header_bar_new());
    gtk_widget_show(GTK_WIDGET(header_bar));
    gtk_header_bar_set_title(header_bar, MINESWEEPER_APPNAME);
    gtk_header_bar_set_show_close_button(header_bar, TRUE);
    gtk_window_set_titlebar(gl_context.gtk_window, GTK_WIDGET(header_bar));

    // Button "New Game"
    GtkWidget *button = gtk_menu_button_new();
    GdkPixbuf *pixbuf = is_dark_theme_enabled ? gui_image_load_from_memory_scale(gui_image_newgame_light_bytes,
                                                                                 gui_image_newgame_light_length,
                                                                                 MINESWEEPER_GUI_HEADERBAR_BTN_IMG_WIDTH,
                                                                                 MINESWEEPER_GUI_HEADERBAR_BTN_IMG_HEIGHT)
                                              : gui_image_load_from_memory_scale(gui_image_newgame_dark_bytes,
                                                                                 gui_image_newgame_dark_length,
                                                                                 MINESWEEPER_GUI_HEADERBAR_BTN_IMG_WIDTH,
                                                                                 MINESWEEPER_GUI_HEADERBAR_BTN_IMG_HEIGHT);
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
    g_signal_connect(menu_new_game_item,
                     "activate",
                     G_CALLBACK(gui_main_callback_menu_new_game),
                     (void *) GAME_DIFFICULTY_EASY);

    // Menu "New Game": Add "normal" option
    menu_new_game_item = gtk_menu_item_new_with_label("Normal");
    gtk_container_add(GTK_CONTAINER(menu_new_game), menu_new_game_item);
    gtk_menu_attach(GTK_MENU(menu_new_game), menu_new_game_item, 0, 1, 1, 2);
    g_signal_connect(menu_new_game_item,
                     "activate",
                     G_CALLBACK(gui_main_callback_menu_new_game),
                     (void *) GAME_DIFFICULTY_NORMAL);
    GtkWidget *menu_to_activate_at_run = menu_new_game_item;

    // Menu "New Game": Add "hard" option
    menu_new_game_item = gtk_menu_item_new_with_label("Hard");
    gtk_container_add(GTK_CONTAINER(menu_new_game), menu_new_game_item);
    gtk_menu_attach(GTK_MENU(menu_new_game), menu_new_game_item, 0, 1, 2, 3);
    g_signal_connect(menu_new_game_item,
                     "activate",
                     G_CALLBACK(gui_main_callback_menu_new_game),
                     (void *) GAME_DIFFICULTY_HARD);

    // Menu "New Game": Display
    gtk_widget_show_all(menu_new_game);

    // Button "About"
    button = gtk_button_new();
    pixbuf = is_dark_theme_enabled ? gui_image_load_from_memory_scale(gui_image_about_light_bytes,
                                                                      gui_image_about_light_length,
                                                                      MINESWEEPER_GUI_HEADERBAR_BTN_IMG_WIDTH,
                                                                      MINESWEEPER_GUI_HEADERBAR_BTN_IMG_HEIGHT)
                                   : gui_image_load_from_memory_scale(gui_image_about_dark_bytes,
                                                                      gui_image_about_dark_length,
                                                                      MINESWEEPER_GUI_HEADERBAR_BTN_IMG_WIDTH,
                                                                      MINESWEEPER_GUI_HEADERBAR_BTN_IMG_HEIGHT);
    image  = gtk_image_new_from_pixbuf(pixbuf);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_set_tooltip_text(button, "About");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), button);
    g_signal_connect(button, "clicked", G_CALLBACK(gui_main_callback_menu_about), gl_context.gtk_window);

    // Create vertical box
    GtkWidget *const gtk_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(gl_context.gtk_window), gtk_vbox);

    // Create HUD
    GtkWidget *const gtk_vbox_hud = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(gtk_vbox_hud, 0, 60);
    gtk_widget_set_name(gtk_vbox_hud, "hud");
    gtk_box_pack_start(GTK_BOX(gtk_vbox), gtk_vbox_hud, FALSE, FALSE, 0);

    GtkWidget *const gtk_label_timer = gtk_label_new("000");
    gtk_widget_set_name(gtk_label_timer, "label");
    gtk_box_pack_start(GTK_BOX(gtk_vbox_hud), gtk_label_timer, FALSE, FALSE, 20);
    gl_context.gtk_label_timer = GTK_LABEL(gtk_label_timer);

    GtkWidget *const gtk_label_mine_count = gtk_label_new("000");
    gtk_widget_set_name(gtk_label_mine_count, "label");
    gtk_box_pack_end(GTK_BOX(gtk_vbox_hud), gtk_label_mine_count, FALSE, FALSE, 20);
    gl_context.gtk_label_flag_left = GTK_LABEL(gtk_label_mine_count);

    // Create Game grid
    GtkWidget *const gtk_grid_game = gtk_grid_new();
    gtk_widget_set_name(gtk_grid_game, "board");
    gtk_box_pack_start(GTK_BOX(gtk_vbox), gtk_grid_game, FALSE, FALSE, 0);
    gl_context.gtk_grid_game = GTK_GRID(gtk_grid_game);

    // Style
    GdkDisplay     *const display  = gdk_display_get_default();
    GdkScreen      *const screen   = gdk_display_get_default_screen(display);
    GtkCssProvider *const provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(
            provider,
            "#hud{background-color:#4a742c;} #board{background-color:#313131;padding:0;margin:0;} #mine{padding:0;}"
            "#label{color:white;font-size:12pt;font-weight:bold;}",
            -1,
            NULL
    );
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);

    // Show
    gtk_widget_show_all(GTK_WIDGET(gl_context.gtk_window));
    gtk_menu_item_activate(GTK_MENU_ITEM(menu_to_activate_at_run));
}
