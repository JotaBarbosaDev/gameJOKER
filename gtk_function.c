#include <gtk/gtk.h>
#include "main.h"
#include "UI/ui.h"

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
    if (error)
    {
        error("Error: %s\n", error->message);
        g_printerr("Error: %s\n", error->message);
        g_error_free(error);
    }
    okay("CSS loaded successfully");
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
    okay("All widgets cleared successfully");
}

GtkWidget *create_button(const gchar *css_ID, const gchar *label, void *func)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(label);
    gtk_fixed_put(GTK_FIXED(fixed), button, 0, 0);
    gtk_widget_set_name(button, "button");
    if (func != NULL)
        g_signal_connect(button, "clicked", G_CALLBACK(func), NULL);
    gtk_widget_set_name(button, css_ID);

    okay("Button '%s' created successfully", label);
    return button;
}

GtkWidget *create_label(const gchar *css_ID, const gchar *label)
{
    GtkWidget *text;
    text = gtk_label_new(label);
    gtk_fixed_put(GTK_FIXED(fixed), text, 0, 0);
    gtk_widget_set_name(text, css_ID);
    okay("Label '%s' created successfully", label);
    return text;
}

GtkWidget *create_password_entry(const gchar *css_ID)
{
    GtkWidget *entry;
    entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_fixed_put(GTK_FIXED(fixed), entry, 0, 0);
    gtk_widget_set_name(entry, css_ID);
    gtk_widget_set_can_focus(entry, FALSE); // Disable autofocus
    okay("Password entry created successfully");
    return entry;
}

GtkWidget *create_password_entry_placeholder(const gchar *css_ID)
{
    GtkWidget *entry;
    entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Password");
    gtk_fixed_put(GTK_FIXED(fixed), entry, 0, 0);
    gtk_widget_set_name(entry, css_ID);
    okay("Password entry created successfully");
    return entry;
}

GtkWidget *create_entry(const gchar *css_ID)
{
    GtkWidget *entry;
    entry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry, 0, 0);
    gtk_widget_set_name(entry, css_ID);
    okay("Entry created successfully");
    return entry;
}

GtkWidget *create_placeholder_entry(const gchar *css_ID, const gchar *placeholder)
{
    GtkWidget *entry;
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder);
    gtk_fixed_put(GTK_FIXED(fixed), entry, 0, 0);
    gtk_widget_set_name(entry, css_ID);
    okay("Placeholder entry created successfully");
    return entry;
}

GtkWidget *create_list()
{
    GtkWidget *list;
    list = gtk_list_box_new();
    gtk_fixed_put(GTK_FIXED(fixed), list, 0, 0);
    return list;
}

void add_array_of_elements_to_list_horizontal(GtkWidget *list, const gchar *text[], int len, guint padding, const gchar *css_ID, guint width, guint height)
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    for (int i = 0; i < len; i++)
    {
        GtkWidget *label = gtk_label_new(text[i]);
        gtk_widget_set_name(label, css_ID);
        if (width != 0)
            gtk_widget_set_size_request(label, width, height);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, padding);
    }
    gtk_container_add(GTK_CONTAINER(list), box);
}