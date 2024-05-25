#ifndef PERGUNTAS_H
#define PERGUNTAS_H

#include <gtk/gtk.h>

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

typedef struct
{
    int pergunta_len;
    int respostas_len[4];
} RW_Pergunta;

extern char temas[9][20];
extern char dificuldades[3][20];

void init_perguntas(Pergunta *p);
void free_pergunta(Pergunta *pergunta);
Pergunta *create_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo);
void add_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int tema, float tempo, int tipo);
void add_pergunta_with_struct(Pergunta *p);
void print_pergunta();
void edit_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo);
void delete_pergunta(int id);
Pergunta **get_all_perguntas();
int get_number_of_perguntas();
void save_perguntas();
void load_perguntas();
Pergunta *get_random_pergunta();
void divide_perguntas_by_difficulty();
Pergunta *get_pergunta_by_id(int id);
int get_last_pergunta_id();

#endif