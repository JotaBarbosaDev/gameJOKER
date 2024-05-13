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

int main_UI(int argc, char *argv[]);

// MAIN
#define okay(msg, ...) printf("\033[1;32m[ + ]\033[0m " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("\033[1;31m[ - ]\033[0m " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("\033[1;34m[ i ]\033[0m " msg "\n", ##__VA_ARGS__)

// Perguntas
typedef struct
{
    char *pergunta;
    char **respostas;
    int resposta_certa;
    int dificuldade; // 0-facil 1-medio 2-dificil
    int id;
    int tema;
    float tempo;
    int tipo; // 0-normal 1-imagens 2-50/50
} Pergunta;

typedef struct Pergunta_node
{
    Pergunta *pergunta;
    struct Pergunta_node *next;
} Pergunta_node;

extern char temas[5][20];

void init_perguntas(Pergunta *p);
void free_pergunta(Pergunta *pergunta);
Pergunta *create_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo);
void *add_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo);
void print_pergunta();
void *edit_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo);
void delete_pergunta(int id);
Pergunta **get_all_perguntas();
int get_number_of_perguntas();

#endif