#ifndef USER_H
#define USER_H

#include <gtk/gtk.h>

typedef struct
{
    char username[100];
    unsigned long password;
    int id;
    int numero_de_vitorias;
    int patamar_maximo;
    int tempo_total;
    int numero_de_perguntas;
    int numero_de_jogos_jogados;
    int numero_de_jogos_ganhos;
    int numero_de_jogos_perdidos;
    int numero_de_jogos_cancelados_por_falta_de_tempo;
    int faceis_certas;
    int faceis_erradas;
    int medios_certas;
    int medios_erradas;
    int dificeis_certas;
    int dificeis_erradas;
} User;

extern User *login_user_global;

// @brief Hash function to hash a string https://theartincode.stanis.me/008-djb2/
unsigned long djb2(const char *str);
void register_user(char *username, char *password);
int login_user(char *username, char *password);
void save_users();
void load_users();
User *get_all_users();
User *get_users_by_id(int id);
void print_users();
void free_all_users();
void delete_user_by_id(int id);

#endif