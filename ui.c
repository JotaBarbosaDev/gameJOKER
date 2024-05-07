#include <gtk/gtk.h>
#include "main.h"

GtkWidget *window;
GtkWidget *login;
GtkWidget *password;
GtkWidget *fixed;

#define WIDTH 800
#define HEIGHT 400

void menu_admin();

void login_func()
{
    const u_char *login_text = gtk_entry_get_text(GTK_ENTRY(login));
    const u_char *password_text = gtk_entry_get_text(GTK_ENTRY(password));

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

void menu_admin()
{
    clear_all();

    create_label("adminTITLE", "ADMIN");

    gtk_widget_show_all(window);
    gtk_main();
}

void menu_principal()
{
    clear_all();

    create_label("jocaTITLE", "JOCA");

    login = create_entry("login_input");

    password = create_password_entry("password_input");

    create_label("login_label", "Login:");
    create_label("password_label", "Senha:");

    create_button("login_button", "Entrar", login_func);

    gtk_widget_show_all(window);
    gtk_main();
}

int main_UI(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
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
