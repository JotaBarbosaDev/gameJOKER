#include <gtk/gtk.h>
#include "main.h"

GtkWidget *window;
GtkWidget *login;
GtkWidget *password;
GtkWidget *fixed;

#define WIDTH 800
#define HEIGHT 600

void menu_admin();

void login_func()
{
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(login));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(password));

    if (strcmp(login_text, "admin") == 0 && strcmp(password_text, "admin") == 0)
    {
        printf("Login efetuado com sucesso\n");
        menu_admin();
    }
    else
    {
        // create new window with error message
        GtkWidget *error_window;
        GtkWidget *error_label;
        error_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(error_window), 200, 100);
        gtk_window_set_title(GTK_WINDOW(error_window), "Error");
        error_label = gtk_label_new("Login ou senha incorretos");
        gtk_container_add(GTK_CONTAINER(error_window), error_label);
        gtk_widget_show_all(error_window);
        printf("Login ou senha incorretos\n");
    }
}

gboolean barra_left(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    // Set the color and size of the shape

    cairo_set_source_rgb(cr, 0.122, 0.267, 0.573); // to git 0-1, 0-1, 0-1 colors
    cairo_set_line_width(cr, 150);

    // Draw a rectangle shape
    cairo_rectangle(cr, 0, 0, 150, HEIGHT);
    cairo_stroke(cr);

    return FALSE;
}

void menu_left_admin()
{
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 200, HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 0, 0);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(barra_left), NULL);
}

void menu_admin()
{
    clear_all();

    create_label("adminTITLE", "ADMIN");
    menu_left_admin();
    create_label("say_JOKER_admin", "JOCA");
    create_button("users_see_admin", "Usuários", NULL);
    create_button("perguntas_admin", "Questões", NULL);

    gtk_widget_show_all(window);
    okay("UI admin loaded successfully");
    gtk_main();
}

void menu_principal()
{
    clear_all();

    create_label("jocaTITLE", "JOCA");

    login = create_placeholder_entry("login_input", "Login");

    password = create_password_entry_placeholder("password_input");

    create_button("login_button", "Entrar", login_func);

    gtk_widget_show_all(window);
    okay("UI menu loaded successfully");
    gtk_main();
}

int main_UI(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window), "Joca");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_name(window, "window");

    import_css();

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    menu_principal();

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
