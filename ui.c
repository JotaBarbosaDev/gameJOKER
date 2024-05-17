#include <gtk/gtk.h>
#include "main.h"

GtkWidget *window;
GtkWidget *login;
GtkWidget *password;
GtkWidget *fixed;

#define WIDTH 800
#define HEIGHT 600

void menu_admin();
void menu_left_admin();
void menu_admin_quests();

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

// Criar tela admin -> users
void menu_admin_users()
{
    clear_all();
    menu_left_admin();

    create_button("users_create_users", "Criar Usuario", NULL);
    create_button("users_edit_users", "Editar Usuario", NULL);
    create_button("users_delete_users", "Apagar Usuario", NULL);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

// Criar tela admin -> quests

char *pergunta_add;
char *resposta_1_add;
char *resposta_2_add;
char *resposta_3_add;
char *resposta_4_add;
unsigned long int current_resposta_certa;
int dificuldade_add;
int tema_add;
float tempo_add;
int tipo;

GtkWidget *pergunta;
GtkWidget *resposta_1;
GtkWidget *resposta_2;
GtkWidget *resposta_3;
GtkWidget *resposta_4;
GtkWidget *tempo;

void add_pergunta_func()
{
    const gchar *temp1 = gtk_entry_get_text(GTK_ENTRY(pergunta));
    pergunta_add = (char *)temp1;

    const gchar *temp2 = gtk_entry_get_text(GTK_ENTRY(resposta_1));
    resposta_1_add = (char *)temp2;

    const gchar *temp3 = gtk_entry_get_text(GTK_ENTRY(resposta_2));
    resposta_2_add = (char *)temp3;

    const gchar *temp4 = gtk_entry_get_text(GTK_ENTRY(resposta_3));
    resposta_3_add = (char *)temp4;

    const gchar *temp5 = gtk_entry_get_text(GTK_ENTRY(resposta_4));
    resposta_4_add = (char *)temp5;

    const gchar *temp6 = gtk_entry_get_text(GTK_ENTRY(tempo));
    tempo_add = atof(temp6);

    add_pergunta(pergunta_add, resposta_1_add, resposta_2_add, resposta_3_add, resposta_4_add, current_resposta_certa, dificuldade_add, 0, tempo_add, 5);
}

void set_resposta(GtkWidget *widget, gpointer resposta)
{
    current_resposta_certa = (intptr_t)resposta;
}

void set_dificuldade(GtkWidget *widget, gpointer dificuldade)
{
    dificuldade_add = (intptr_t)dificuldade;
}

void tela_create_pergunta()
{
    clear_all();

    pergunta = create_placeholder_entry("pergunta_input", "Pergunta");
    resposta_1 = create_placeholder_entry("resposta_1_input", "Resposta 1");
    resposta_2 = create_placeholder_entry("resposta_2_input", "Resposta 2");
    resposta_3 = create_placeholder_entry("resposta_3_input", "Resposta 3");
    resposta_4 = create_placeholder_entry("resposta_4_input", "Resposta 4");
    tempo = create_placeholder_entry("tempo_input", "Tempo (seg)");

    create_button("leave_creation_button", "<", menu_admin_quests);
    gtk_entry_set_width_chars(GTK_ENTRY(pergunta), 100);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_1), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_2), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_3), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_4), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(tempo), 11);
    create_label("perguntaCerta_label", "Pergunta certa: ");
    GtkWidget *but1 = create_button("respostaCerta_1", "Resposta 1", set_resposta);
    GtkWidget *but2 = create_button("respostaCerta_2", "Resposta 2", set_resposta);
    GtkWidget *but3 = create_button("respostaCerta_3", "Resposta 3", set_resposta);
    GtkWidget *but4 = create_button("respostaCerta_4", "Resposta 4", set_resposta);
    create_label("dificulde_label", "Dificuldade: ");
    GtkWidget *but5 = create_button("dificuldadeEasy", "Facil", set_dificuldade);
    GtkWidget *but6 = create_button("dificuldadeMedium", "Media", set_dificuldade);
    GtkWidget *but7 = create_button("dificuldadeHard", "Dificil", set_dificuldade);
    g_signal_connect(but1, "clicked", G_CALLBACK(set_resposta), (gpointer)0);
    g_signal_connect(but2, "clicked", G_CALLBACK(set_resposta), (gpointer)1);
    g_signal_connect(but3, "clicked", G_CALLBACK(set_resposta), (gpointer)2);
    g_signal_connect(but4, "clicked", G_CALLBACK(set_resposta), (gpointer)3);

    g_signal_connect(but5, "clicked", G_CALLBACK(set_dificuldade), (gpointer)0);
    g_signal_connect(but6, "clicked", G_CALLBACK(set_dificuldade), (gpointer)1);
    g_signal_connect(but7, "clicked", G_CALLBACK(set_dificuldade), (gpointer)2);

    create_label("tema_label", "Tema: ");
    create_button("tema_0", "Tema 0", NULL);
    create_button("tema_1", "Tema 1", NULL);
    create_button("tema_2", "Tema 2", NULL);
    create_button("tema_3", "Tema 3", NULL);
    create_button("tema_4", "Tema 4", NULL);
    create_button("tema_5", "Tema 5", NULL);
    create_button("tema_6", "Tema 6", NULL);
    create_button("tema_7", "Tema 7", NULL);
    create_button("tema_8", "Tema 8", NULL);

    create_button("pergunta_create_button", "Criar Pergunta", add_pergunta_func);
    


    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}

void menu_admin_quests()
{
    clear_all();
    menu_left_admin();

    create_button("quests_create_quest", "Criar Pergunta", tela_create_pergunta);
    create_button("quests_edit_quest", "Editar Pergunta", NULL);
    create_button("quests_delete_quest", "Apagar Pergunta", NULL);

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

void menu_left_admin()
{
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 200, HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 0, 0);

    create_label("say_JOKER_admin", "Admin");
    create_button("users_see_admin", "Usuários", menu_admin_users);
    create_button("perguntas_admin", "Questões", menu_admin_quests);
    create_button("estatisticas_admin", "Estatisticas", menu_admin_stats);

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
