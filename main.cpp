#include <iostream>
#include <unistd.h>
#include <gtk/gtk.h>
#include <string>

// Modules
#include "modules/CssManager.h"
#include "modules/MixerManager.h"

// Images
#include "images/images.h"

#include "style.hex"

const char *homeDir = getenv("HOME");

using namespace std;

GtkWidget *volume_bar;
MixerManager mixerManager;

void on_window_closed() {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    // Установка временной локали "C" для использования точки в качестве разделителя
    setlocale(LC_NUMERIC, "C");

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Volume");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DIALOG);

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_data(*imageData_volume, GDK_COLORSPACE_RGB, TRUE, 8, IMAGE_WIDTH - 50, IMAGE_HEIGHT, 3 * IMAGE_HEIGHT, NULL, NULL);
    GdkPixbuf *resized_pixbuf = gdk_pixbuf_scale_simple(image_pixbuf, 90, 90, GDK_INTERP_BILINEAR);

    GtkWidget *image = gtk_image_new_from_pixbuf(resized_pixbuf);

    volume_bar = gtk_level_bar_new_for_interval(0.0, 1.0);

    if (argc >= 3) {
        string option1 = argv[1];
        string option2 = argv[2];
        if (option1 == "increase") {
            mixerManager.increase_volume(stof(option2));
            gtk_level_bar_set_value(GTK_LEVEL_BAR(volume_bar), mixerManager.get_volume());
        } else if (option1 == "decrease") {
            mixerManager.decrease_volume(stof(option2));
            gtk_level_bar_set_value(GTK_LEVEL_BAR(volume_bar), mixerManager.get_volume());
        } else {
        }
    } else {
        cerr << "2 arguments are required" << endl;
        return 1;
    }

    gtk_box_pack_start(GTK_BOX(box1), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), volume_bar, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), box1);

    //CSS
    CssManager cssManager;

    string path = string(homeDir) + "/.config/mixerdialog/style.css";

    cssManager.loadFromHex(style_css, style_css_len);
    cssManager.loadFromFile(path.c_str());

    gtk_widget_show_all(window);

    g_timeout_add(500, GSourceFunc(on_window_closed), NULL);

    gtk_main();

    return 0;
}
