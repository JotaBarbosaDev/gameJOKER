// main.h
#include <gtk/gtk.h>
#include <cairo.h>
#ifndef UI_H
#define UI_H

// create_pergunta.c
void tela_create_pergunta();

void menu_admin();
void menu_left_admin();
void menu_admin_quests();
void ver_perguntas();
void tela_edit_user();
void tela_create_user();
void tela_delete_user();

// UI
extern GtkWidget *fixed;

void import_css();
void clear_all();
GtkWidget *create_button(const gchar *css_ID, const gchar *label, void *func);
GtkWidget *create_label(const gchar *css_ID, const gchar *label);
GtkWidget *create_password_entry(const gchar *css_ID);
GtkWidget *create_entry(const gchar *css_ID);
GtkWidget *create_placeholder_entry(const gchar *css_ID, const gchar *placeholder);
GtkWidget *create_password_entry_placeholder(const gchar *css_ID);

typedef struct
{
    int current_pergunta;
    int current_dificuldade;
    int current_tema;
    int *already_shown;
    int already_shown_len;
    int ending;
    int joca_level;
    int jocas_number;
    int pontuacao;
    float multiplicador;
} JogoJoca;

int main_UI(int argc, char *argv[]);
int jogo_UI();
void menu_principal();
extern GtkWidget *window;
extern JogoJoca jogo;

#endif