// main.h
#include <gtk/gtk.h>
#include <cairo.h>
#ifndef MAIN_H
#define MAIN_H

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
} JogoJoca;

int main_UI(int argc, char *argv[]);
int jogo_UI();
void menu_principal();
extern GtkWidget *window;
extern JogoJoca jogo;

// MAIN
#define okay(msg, ...) printf("\033[1;32m[ + ]\033[0m " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("\033[1;31m[ - ]\033[0m " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("\033[1;34m[ i ]\033[0m " msg "\n", ##__VA_ARGS__)
int getRandomNumber(int x);

#endif