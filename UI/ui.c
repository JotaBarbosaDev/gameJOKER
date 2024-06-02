#include <gtk/gtk.h>
#include "../main.h"
#include "ui.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "../estatisticas/estatisticas.h"

GtkWidget *window;
GtkWidget *login;
GtkWidget *password;
GtkWidget *fixed;

void create_window_login_error(GtkWidget *parent)
{
    GtkWidget *window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Error");
    gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(parent));
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);

    GtkWidget *label = gtk_label_new("Login ou senha incorretos");
    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_widget_show_all(window);
}

void login_func()
{
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(login));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(password));

    if (strcmp(login_text, "admin") == 0 && strcmp(password_text, "admin") == 0)
    {
        menu_admin();
    }
    else if (login_user((char *)login_text, (char *)password_text) == 1)
    {
        printf("Login efetuado com sucesso\n");
        jogo_UI();
    }

    else
    {
        // create new window with error message
        create_window_login_error(window);
        gtk_widget_show_all(window);
        printf("Login ou senha incorretos\n");
    }
}

GtkWidget *username_register;
GtkWidget *nacionalidade_register;
GtkWidget *password_register;
GtkWidget *full_name_register;
GtkWidget *open_calendar_register;
GtkWidget *calendar;

void register_final_button()
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_register));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_register));
    const gchar *nacionalidade = gtk_entry_get_text(GTK_ENTRY(nacionalidade_register));
    const gchar *full_name = gtk_entry_get_text(GTK_ENTRY(full_name_register));

    if (strlen(username) == 0 || strlen(password) == 0 || strlen(nacionalidade) == 0 || strlen(full_name) == 0)
    {
        error("Invalid input");
        return;
    }

    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    unsigned int born_date[3];
    born_date[0] = day;
    born_date[1] = month + 1;
    born_date[2] = year;

    register_user((char *)username, (char *)password, (char *)full_name, (char *)nacionalidade, born_date);
    menu_principal();
}

void show_calendar()
{
    calendar = gtk_calendar_new();
    gtk_fixed_put(GTK_FIXED(fixed), calendar, 302, 300);
    gtk_widget_show_all(window);
}

void register_button()
{
    clear_all();

    // create_label("register_label", "Registrar");

    username_register = create_placeholder_entry("register_username", "Username");

    password_register = create_password_entry_placeholder("register_password");

    nacionalidade_register = create_placeholder_entry("register_nacionalidade", "Nacionalidade");

    full_name_register = create_placeholder_entry("register_full_name", "Nome Completo");

    create_button("register_button1", "Registrar", register_final_button);

    open_calendar_register = create_button("open_calendar", "Data de Nascimento", show_calendar);

    create_button("back_button", "Voltar", menu_principal);

    gtk_widget_show_all(window);
    gtk_main();
}

gboolean barra_left(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    // Set the color and size of the shape
    cairo_set_source_rgb(cr, 0.122, 0.267, 0.573); // to git 0-1, 0-1, 0-1 colors
    cairo_set_line_width(cr, 150);

    // Draw a rectangle shape
    cairo_rectangle(cr, 0, 0, 150, HEIGHT);
    cairo_stroke(cr);

    // Add a right border
    cairo_set_source_rgb(cr, 0.992, 0.859, 0.322);
    cairo_set_line_width(cr, 3);
    cairo_move_to(cr, 199, 0);
    cairo_line_to(cr, 199, HEIGHT);
    cairo_stroke(cr);

    return FALSE;
}

void menu_admin_quests()
{
    clear_all();
    menu_left_admin();

    create_button("ver_perguntas", "Ver Perguntas", ver_perguntas);
    create_button("quests_create_quest", "Criar Pergunta", tela_create_pergunta);
    create_button("quests_edit_quest", "Editar e Apagar", tela_edit_pergunta);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

// Criar tela admin -> stats

void menu_admin_stats()
{
    clear_all();
    menu_left_admin();

    okay("Stats admin loaded successfully");

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void menu_principal()
{

    login_user_global = NULL;
    jogo.joca_level = 0;
    jogo.jocas_number = 3;
    jogo.current_pergunta = 0;
    jogo.current_dificuldade = 0;
    jogo.current_tema = 0;
    jogo.already_shown = NULL;
    jogo.already_shown_len = 0;
    jogo.ending = 0;

    clear_all();

    create_label("jocaTITLE", "JOCA");

    login = create_placeholder_entry("login_input", "Username");

    password = create_password_entry_placeholder("password_input");

    create_button("login_button", "Entrar", login_func);

    create_button("register_button", "Registrar", register_button);

    gtk_widget_show_all(window);
    okay("UI menu loaded successfully");
    gtk_main();
}

void serach_user_minha_nossa()
{
    ssearch_user_ui(1);
}

void menu_admin_estatistica()
{
    clear_all();
    menu_left_admin();

    create_button("last_10_games", "Ultimos 10 jogos", show_last_10_games);
    create_button("last_players_played", "Ultimos jogadores que jogaram", last_players_played_by_date);
    create_button("last_patamar", "Chegou ao ultimo patamares", got_to_last_patamar);
    create_button("jokers_extra", "Ganhou todos os Jokers", got_all_jokers);
    create_button("procurar_jogador", "Procurar Jogador", serach_user_minha_nossa);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void menu_left_admin()
{
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 200, HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 0, 0);

    create_label("say_JOKER_admin", "Admin");
    create_button("users_see_admin", "Usuários", start_user_UI);
    create_button("perguntas_admin", "Perguntas", menu_admin_quests);
    create_button("estatisticas_admin", "Estatisticas", menu_admin_estatistica);

    create_button("logout_game", "Terminar Sessão", menu_principal);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(barra_left), NULL);
}

void menu_admin()
{
    clear_all();

    menu_left_admin();

    gtk_widget_show_all(window);
    okay("UI admin loaded successfully");
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
