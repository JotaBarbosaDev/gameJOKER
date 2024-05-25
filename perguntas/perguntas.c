#include "../main.h"
#include "../UI/ui.h"
#include "perguntas.h"

/*
get_question
save_perguntas
load_perguntas
*/

Pergunta_node *pergunta_head;
int loaded = 0;

void init_perguntas(Pergunta *p)
{
    pergunta_head = malloc(sizeof(Pergunta_node));
    pergunta_head->next = NULL;
    pergunta_head->pergunta = p;
    okay("Perguntas initialized");
    return;
}

void free_all_linked_list()
{
    Pergunta_node *temp_node = pergunta_head;
    Pergunta_node *next_node;
    while (temp_node->next != NULL)
    {
        next_node = temp_node->next;
        free_pergunta(temp_node->pergunta);
        free(temp_node);
        temp_node = next_node;
    }
    free_pergunta(temp_node->pergunta);
    free(temp_node);
    okay("Perguntas free'd");
}

void free_pergunta(Pergunta *pergunta)
{
    for (int i = 0; i < 4; i++)
    {
        free(pergunta->respostas[i]);
    }
    free(pergunta->respostas);
    free(pergunta);
}

int get_number_of_perguntas()
{
    Pergunta_node *temp_node = pergunta_head;
    int NUMBER_OF_PERGUNTAS = 1;
    while (temp_node->next != NULL)
    {
        NUMBER_OF_PERGUNTAS++;
        temp_node = temp_node->next;
    }
    return NUMBER_OF_PERGUNTAS;
}

Pergunta *create_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    // criar pergunta
    Pergunta *p = (Pergunta *)malloc(sizeof(Pergunta));
    p->pergunta = pergunta;
    p->resposta_certa = resposta_certa;
    p->dificuldade = dificuldade;
    p->id = id;
    p->tema = tema;
    p->tempo = tempo;
    p->tipo = tipo;

    // malloc memory for respostas

    p->respostas = (char **)malloc(4 * sizeof(char *));

    p->respostas[0] = (char *)malloc(strlen(resposta_1) + 1);
    strcpy(p->respostas[0], resposta_1);
    p->respostas[1] = (char *)malloc(strlen(resposta_2) + 1);
    strcpy(p->respostas[1], resposta_2);

    p->respostas[2] = (char *)malloc(strlen(resposta_3) + 1);
    strcpy(p->respostas[2], resposta_3);
    p->respostas[3] = (char *)malloc(strlen(resposta_4) + 1);
    strcpy(p->respostas[3], resposta_4);

    return p;
}

void add_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int tema, float tempo, int tipo)
{

    Pergunta_node *temp_node = pergunta_head;
    while (temp_node->next != NULL)
    {
        temp_node = temp_node->next;
    }
    int last_id = temp_node->pergunta->id + 1;

    Pergunta *p = create_pergunta(pergunta, resposta_1, resposta_2, resposta_3, resposta_4, resposta_certa, dificuldade, last_id, tema, tempo, tipo);
    // printf("ID: %d\n", last_id);
    Pergunta_node *new = malloc(sizeof(Pergunta_node));
    new->pergunta = p;
    new->next = NULL;
    temp_node->next = new;
    save_perguntas();
}

void add_pergunta_with_struct(Pergunta *p)
{
    add_pergunta(p->pergunta, p->respostas[0], p->respostas[1], p->respostas[2], p->respostas[3], p->resposta_certa, p->dificuldade, p->tema, p->tempo, p->tipo);
}

void edit_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    Pergunta *p = create_pergunta(pergunta, resposta_1, resposta_2, resposta_3, resposta_4, resposta_certa, dificuldade, id, tema, tempo, tipo);

    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        if (temp_node->pergunta->id == id)
        {
            free_pergunta(temp_node->pergunta);
            temp_node->pergunta = p;
            save_perguntas();
            return;
        }

        temp_node = temp_node->next;
    }

    if (temp_node->pergunta->id == id)
    {
        free_pergunta(temp_node->pergunta);
        temp_node->pergunta = p;
        save_perguntas();
        return;
    }

    error("Pergunta.id not found edit_pergunta");
    return;
}

void delete_pergunta(int id) // FALTA DAR FREE
{
    Pergunta_node *temp_node = pergunta_head;
    Pergunta_node *depois;
    Pergunta_node *antes;

    while (temp_node->next != NULL)
    {
        if (temp_node->pergunta->id == id)
        {
            depois = temp_node->next;
            break;
        }
        antes = temp_node;
        temp_node = temp_node->next;
    }

    if (temp_node == pergunta_head && temp_node->next == NULL)
    {
        error("O programa deve ter pelo menos 1 pergunta (LL delete_pergunta)"); // da para fzr de outra maneira :D
        return;
    }

    if (temp_node == pergunta_head)
    {
        pergunta_head = depois;
    }
    else if (temp_node->next == NULL)
    {
        antes->next = NULL;
    }
    else
    {
        antes->next = depois;
    }
    free_pergunta(temp_node->pergunta); // free a pergunta
    free(temp_node);                    // free ao nodo da pergunta
    save_perguntas();
    free_all_linked_list();
    load_perguntas();
}

Pergunta **get_all_perguntas()
{
    int NUMBER_OF_PERGUNTAS = get_number_of_perguntas();
    Pergunta **ret = malloc(sizeof(Pergunta *) * NUMBER_OF_PERGUNTAS);

    Pergunta_node *temp_node = pergunta_head;
    int i = 0;
    while (temp_node->next != NULL)
    {
        ret[i] = temp_node->pergunta;
        i++;
        temp_node = temp_node->next;
    }
    ret[i] = temp_node->pergunta;

    return ret;
}

void print_pergunta()
{
    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        printf("Pergunta: %s\n", temp_node->pergunta->pergunta);
        printf("Respostas: %s %s %s %s\n", temp_node->pergunta->respostas[0], temp_node->pergunta->respostas[1], temp_node->pergunta->respostas[2], temp_node->pergunta->respostas[3]);
        printf("Resposta certa: %d\n", temp_node->pergunta->resposta_certa);
        printf("Dificuldade: %d\n", temp_node->pergunta->dificuldade);
        printf("ID: %d\n", temp_node->pergunta->id);
        printf("Tema: %d\n", temp_node->pergunta->tema);
        printf("Tempo: %f\n", temp_node->pergunta->tempo);
        printf("Tipo: %d\n", temp_node->pergunta->tipo);
        printf("\n\n");
        temp_node = temp_node->next;
    }
    printf("Pergunta: %s\n", temp_node->pergunta->pergunta);
    printf("Respostas: %s %s %s %s\n", temp_node->pergunta->respostas[0], temp_node->pergunta->respostas[1], temp_node->pergunta->respostas[2], temp_node->pergunta->respostas[3]);
    printf("Resposta certa: %d\n", temp_node->pergunta->resposta_certa);
    printf("Dificuldade: %d\n", temp_node->pergunta->dificuldade);
    printf("ID: %d\n", temp_node->pergunta->id);
    printf("Tema: %d\n", temp_node->pergunta->tema);
    printf("Tempo: %f\n", temp_node->pergunta->tempo);
    printf("Tipo: %d\n", temp_node->pergunta->tipo);
    printf("\n\n");
}

void load_perguntas()
{
    loaded = 0;
    okay("Loading perguntas");
    // abrir,verificar se existe,ler,guardar na lista
    FILE *f = fopen("perguntas.bin", "rb");

    if (f == NULL)
    {
        error("Error opening file");
        return;
    }

    okay("File opened");
    Pergunta *p = malloc(sizeof(Pergunta));

    if (p == NULL)
    {
        error("Error allocating memory");
        return;
    }

    int is_first_time = 0;
    while (fread(p, sizeof(Pergunta), 1, f))
    {
        RW_Pergunta rw_pergunta;
        fread(&rw_pergunta, sizeof(RW_Pergunta), 1, f);

        p->pergunta = malloc(rw_pergunta.pergunta_len);

        fread(p->pergunta, sizeof(char), rw_pergunta.pergunta_len, f);

        p->respostas = (char **)malloc(4 * sizeof(char *));

        for (int i = 0; i <= 3; i++)
        {
            p->respostas[i] = malloc(rw_pergunta.respostas_len[i]);
            fread(p->respostas[i], sizeof(char), rw_pergunta.respostas_len[i], f);
        }

        if (is_first_time == 0)
        {
            init_perguntas(create_pergunta(p->pergunta, p->respostas[0], p->respostas[1], p->respostas[2], p->respostas[3], p->resposta_certa, p->dificuldade, p->id, p->tema, p->tempo, p->tipo));
            is_first_time = 1;
        }
        else
        {
            add_pergunta_with_struct(create_pergunta(p->pergunta, p->respostas[0], p->respostas[1], p->respostas[2], p->respostas[3], p->resposta_certa, p->dificuldade, p->id, p->tema, p->tempo, p->tipo));
        }
    }
    loaded = 1;
    free(p);
    fclose(f);
    okay("Perguntas loaded");
}

void write_to_file(FILE *f, Pergunta_node *temp_node, RW_Pergunta rw_pergunta)
{
    fwrite(temp_node->pergunta, sizeof(Pergunta), 1, f);

    rw_pergunta.pergunta_len = strlen(temp_node->pergunta->pergunta) + 1;

    for (int i = 0; i <= 3; i++)
    {
        rw_pergunta.respostas_len[i] = strlen(temp_node->pergunta->respostas[i]) + 1;
    }

    fwrite(&rw_pergunta, sizeof(RW_Pergunta), 1, f);

    fwrite(temp_node->pergunta->pergunta, sizeof(char), rw_pergunta.pergunta_len, f);
    for (int i = 0; i < 4; i++)
    {
        fwrite(temp_node->pergunta->respostas[i], sizeof(char), strlen(temp_node->pergunta->respostas[i]) + 1, f);
    }
}

void save_perguntas()
{
    if (loaded == 0)
    {
        return;
    }
    FILE *f = fopen("perguntas.bin", "wb");

    if (f == NULL)
    {
        error("Error opening file");
        return;
    }

    Pergunta_node *temp_node = pergunta_head;
    RW_Pergunta rw_pergunta;
    while (temp_node->next != NULL)
    {
        write_to_file(f, temp_node, rw_pergunta);
        temp_node = temp_node->next;
    }

    write_to_file(f, temp_node, rw_pergunta);
    okay("Perguntas saved");
    fclose(f);
}

Pergunta **perguntas_faceis;
int number_of_perguntas_faceis;
Pergunta **perguntas_medias;
int number_of_perguntas_medias;
Pergunta **perguntas_dificeis;
int number_of_perguntas_dificeis;

void divide_perguntas_by_difficulty()
{
    Pergunta **perguntas = get_all_perguntas();
    int NUMBER_OF_PERGUNTAS = get_number_of_perguntas();

    for (int i = 0; i < NUMBER_OF_PERGUNTAS; i++)
    {
        if (perguntas[i]->dificuldade == 0)
        {
            number_of_perguntas_faceis++;
            perguntas_faceis = realloc(perguntas_faceis, sizeof(Pergunta *) * number_of_perguntas_faceis);
            perguntas_faceis[number_of_perguntas_faceis - 1] = perguntas[i];
        }
        else if (perguntas[i]->dificuldade == 1)
        {
            number_of_perguntas_medias++;
            perguntas_medias = realloc(perguntas_medias, sizeof(Pergunta *) * number_of_perguntas_medias);
            perguntas_medias[number_of_perguntas_medias - 1] = perguntas[i];
        }
        else if (perguntas[i]->dificuldade == 2)
        {
            number_of_perguntas_dificeis++;
            perguntas_dificeis = realloc(perguntas_dificeis, sizeof(Pergunta *) * number_of_perguntas_dificeis);
            perguntas_dificeis[number_of_perguntas_dificeis - 1] = perguntas[i];
        }
    }
}

Pergunta *get_random_pergunta2()
{
    if (jogo.current_dificuldade == 0)
    {
        int random = rand() % number_of_perguntas_faceis;
        return perguntas_faceis[random];
    }
    else if (jogo.current_dificuldade == 1)
    {
        int random = rand() % number_of_perguntas_medias;
        return perguntas_medias[random];
    }
    else if (jogo.current_dificuldade == 2)
    {
        int random = rand() % number_of_perguntas_dificeis;
        return perguntas_dificeis[random];
    }
    else
    {
        error("Dificuldade not found");
        return NULL;
    }
}

int find_pergunta_in_already_shown(Pergunta *per)
{
    for (int i = 0; i < jogo.already_shown_len; i++)
    {
        if (jogo.already_shown[i] == per->id)
        {
            return 1;
        }
    }
    return 0;
}

Pergunta *get_random_pergunta()
{
    Pergunta *per = get_random_pergunta2();
    while (find_pergunta_in_already_shown(per) == 1)
    {
        per = get_random_pergunta2();
    }

    for (int i = 0; i < jogo.already_shown_len; i++)
    {
        printf("ALREADY ID: %d\n", jogo.already_shown[i]);
    }
    printf("FOUND ID: %d\n", per->id);

    return per;
}

Pergunta *get_pergunta_by_id(int id)
{
    Pergunta_node *temp_node = pergunta_head;

    while (temp_node != NULL)
    {
        if (temp_node->pergunta->id == id)
        {
            return temp_node->pergunta;
        }

        temp_node = temp_node->next;
    }

    if (temp_node->pergunta->id == id)
        return temp_node->pergunta;

    return NULL; // Question with the given ID not found
}

int get_last_pergunta_id()
{
    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        temp_node = temp_node->next;
    }

    return temp_node->pergunta->id;
}