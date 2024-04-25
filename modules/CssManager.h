//
// Created by diablo on 04.04.24.
//

#ifndef TEST_CSSMANAGER_H
#define TEST_CSSMANAGER_H

#include <gtk/gtk.h>
#include <string>

class CssManager {
public:
    CssManager();
    ~CssManager();
    void loadFromFile(const gchar *filename);
    void loadFromData(const gchar *data);
    void loadFromHex(unsigned char* hex, unsigned int hex_len);
private:
    GtkCssProvider *provider;
    GtkStyleContext *context;
};

#endif //TEST_CSSMANAGER_H