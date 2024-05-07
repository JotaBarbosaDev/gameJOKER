#include <gtk/gtk.h>
#include "main.h"

void import_css()
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *css_style_file = "css/style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(css_style_file), &error);

    g_object_unref(provider);
}

void clear_all()
{
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(fixed));
    for (iter = children; iter != NULL; iter = g_list_next(iter))
    {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

GtkWidget *create_button(const gchar *css_ID, const gchar *label, void *func)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(label);
    gtk_fixed_put(GTK_FIXED(fixed), button, 0, 0);
    gtk_widget_set_name(button, "button");
    g_signal_connect(button, "clicked", G_CALLBACK(func), NULL);
    gtk_widget_set_name(button, css_ID);
    return button;
}

GtkWidget *create_label(const gchar *css_ID, const gchar *label)
{
    GtkWidget *text;
    text = gtk_label_new(label);
    gtk_fixed_put(GTK_FIXED(fixed), text, 0, 0);
    gtk_widget_set_name(text, css_ID);
    return text;
}

GtkWidget *create_password_entry(const gchar *css_ID)
{
    GtkWidget *entry;
    entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_fixed_put(GTK_FIXED(fixed), entry, 0, 0);
    gtk_widget_set_name(entry, css_ID);
    return entry;
}

GtkWidget *create_entry(const gchar *css_ID)
{
    GtkWidget *entry;
    entry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry, 0, 0);
    gtk_widget_set_name(entry, css_ID);
    return entry;
}