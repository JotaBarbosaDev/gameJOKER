#include "main.h"
#include "user.h"

/*
register_user
login_user
save_users
load_users
get_all_users
get_users_by_id

ATENCAOOO
struct do jogador deve guardar informacao de jogos jogados, pontuacao, numero de jocas
*/

// @brief Hash function to hash a string
User *users;
int number_of_users = 0;

User *login_user_global;

unsigned long djb2(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

int get_last_id()
{
    if (number_of_users == 0)
    {
        return 0;
    }
    return users[number_of_users - 1].id;
}

int get_user_by_username(char *username)
{
    for (int i = 0; i < number_of_users; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void register_user(char *username, char *password)
{
    if (get_user_by_username(username) == 1 || strlen(username) == 0 || strlen(password) == 0 || strlen(username) > 100 || strlen(password) > 100 || strcmp(username, "admin") == 0 || strcmp(password, "admin") == 0)
    {
        error("User already exists or your input is invalid");
        return;
    }
    User *u = (User *)malloc(sizeof(User));
    strcpy(u->username, username);
    u->password = djb2(password);
    u->id = get_last_id() + 1;
    u->numero_de_vitorias = 0;
    u->patamar_maximo = 0;
    u->tempo_total = 0;
    u->numero_de_perguntas = 0;
    u->numero_de_jogos_jogados = 0;
    u->numero_de_jogos_ganhos = 0;
    u->numero_de_jogos_perdidos = 0;
    u->numero_de_jogos_cancelados_por_falta_de_tempo = 0;
    u->faceis_certas = 0;
    u->faceis_erradas = 0;
    u->medios_certas = 0;
    u->medios_erradas = 0;
    u->dificeis_certas = 0;
    u->dificeis_erradas = 0;

    okay("User created");

    if (users == NULL)
    {
        users = malloc(sizeof(User));
    }
    else
    {
        users = realloc(users, sizeof(User) * (sizeof(users) + 1));
    }

    users[number_of_users] = *u;
    number_of_users++;
    free(u);
    save_users();
    return;
}

int login_user(char *username, char *password)
{
    unsigned long hash = djb2(password);
    for (int i = 0; i < number_of_users; i++)
    {
        if (strcmp(users[i].username, username) == 0 && users[i].password == hash)
        {
            okay("User logged in");
            login_user_global = &users[i];
            return 1;
        }
    }
    error("User not found");
    return 0;
}

void save_users()
{
    FILE *f = fopen("users.bin", "wb");
    if (f == NULL)
    {
        error("Error opening file");
        return;
    }

    fwrite(&number_of_users, sizeof(int), 1, f);
    fwrite(users, sizeof(User), number_of_users, f);
    fclose(f);
    okay("Users saved");
}

void load_users()
{
    FILE *f = fopen("users.bin", "rb");
    if (f == NULL)
    {
        error("Error opening file");
        return;
    }

    fread(&number_of_users, sizeof(int), 1, f);
    users = malloc(sizeof(User) * number_of_users);
    fread(users, sizeof(User), number_of_users, f);
    fclose(f);
    okay("Users loaded");
}

User *get_all_users()
{
    return users;
}

User *get_users_by_id(int id)
{
    for (int i = 0; i < number_of_users; i++)
    {
        if (users[i].id == id)
        {
            return &users[i];
        }
    }
    return NULL;
}

int does_user_exist(int id)
{
    for (int i = 0; i < number_of_users; i++)
    {
        if (users[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

void delete_user_by_id(int id)
{
    if (does_user_exist(id) == 0)
    {
        error("User does not exist");
        return;
    }

    for (int i = 0; i < number_of_users; i++)
    {
        if (users[i].id == id)
        {
            for (int j = i; j < number_of_users - 1; j++)
            {
                users[j] = users[j + 1];
            }
            number_of_users--;
            users = realloc(users, sizeof(User) * number_of_users);
        }
    }
}

void print_users()
{
    for (int i = 0; i < number_of_users; i++)
    {
        printf("Username -> %s\n", users[i].username);
        printf("Password -> %lu\n", users[i].password);
        printf("ID -> %d\n", users[i].id);
        printf("Numero de vitorias -> %d\n", users[i].numero_de_vitorias);
        printf("Patamar maximo -> %d\n", users[i].patamar_maximo);
        printf("Tempo total -> %d\n", users[i].tempo_total);
        printf("Numero de perguntas -> %d\n", users[i].numero_de_perguntas);
        printf("Numero de jogos jogados -> %d\n", users[i].numero_de_jogos_jogados);
        printf("Numero de jogos ganhos -> %d\n", users[i].numero_de_jogos_ganhos);
        printf("Numero de jogos perdidos -> %d\n", users[i].numero_de_jogos_perdidos);
        printf("Numero de jogos cancelados por falta de tempo -> %d\n", users[i].numero_de_jogos_cancelados_por_falta_de_tempo);
        printf("Faceis certas -> %d\n", users[i].faceis_certas);
        printf("Faceis erradas -> %d\n", users[i].faceis_erradas);
        printf("Medios certas -> %d\n", users[i].medios_certas);
        printf("Medios erradas -> %d\n", users[i].medios_erradas);
        printf("Dificeis certas -> %d\n", users[i].dificeis_certas);
        printf("Dificeis erradas -> %d\n", users[i].dificeis_erradas);
        printf("\n\n");
    }
}

void free_all_users()
{
    free(users);
}