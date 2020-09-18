#include "gui.h"

gboolean gui_toolbox_is_gtk_dark_theme_enabled(void) {
    GtkSettings *const settings = gtk_settings_get_default();
    gchar       *const value    = NULL;

    g_object_get(settings, "gtk-theme-name", &value, NULL);
    const gboolean res = g_strrstr(value, "dark") != NULL;

    g_object_unref(settings);
    g_free(value);

    return (res);
}
