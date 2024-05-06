#include <gtk/gtk.h>
#define WIDTH 800
#define HEIGHT 400

void tt(GtkWidget *widget, gpointer data)
{
    g_print("Clicou\n");
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
    gtk_window_set_title(GTK_WINDOW(window), "Bibioteca");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    GtkWidget *text;
    text = gtk_label_new("Texto");
    gtk_fixed_put(GTK_FIXED(fixed), text, 10, 10);

    GtkWidget *button;
    button = gtk_button_new_with_label("butaoum1");
    g_signal_connect(button, "clicked", G_CALLBACK(tt), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button, 50, 70);

    GtkWidget *button2;
    button2 = gtk_button_new_with_label("butaoum2");
    g_signal_connect(button2, "clicked", G_CALLBACK(tt), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 50, 100);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}