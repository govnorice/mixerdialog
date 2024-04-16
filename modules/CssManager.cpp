//
// Created by diablo on 04.04.24.
//

#include "CssManager.h"

CssManager::CssManager() {
    provider = gtk_css_provider_new();
    context = gtk_style_context_new();
}
CssManager::~CssManager() {
    g_object_unref(provider);
    g_object_unref(context);
}

// Load styles from a file
void CssManager::loadFromFile(const gchar *filename) {
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(filename), nullptr);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}
// Load styles from a string
void CssManager::loadFromData(const gchar *data) {
    gtk_css_provider_load_from_data(provider, data, -1, nullptr);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}