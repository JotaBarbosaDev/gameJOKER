#include "main.h"

char temas[5][20] = {"tema0", "tema1", "tema2", "tema3", "tema4"};

Pergunta_node *pergunta_head;

void init_perguntas(Pergunta *p)
{
    pergunta_head = malloc(sizeof(Pergunta_node));
    pergunta_head->next = NULL;
    pergunta_head->pergunta = p;
    return;
}

/*
1-as respostas[0,1,2,3]

2- respoastas

3-Pergunta em si
*/
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

void *add_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    Pergunta *p = create_pergunta(pergunta, resposta_1, resposta_2, resposta_3, resposta_4, resposta_certa, dificuldade, id, tema, tempo, tipo);

    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        temp_node = temp_node->next;
    }

    Pergunta_node *new = malloc(sizeof(Pergunta_node));
    new->pergunta = p;
    new->next = NULL;
    temp_node->next = new;
}

void *edit_pergunta(char *pergunta, char *resposta_1, char *resposta_2, char *resposta_3, char *resposta_4, int resposta_certa, int dificuldade, int id, int tema, float tempo, int tipo)
{
    Pergunta *p = create_pergunta(pergunta, resposta_1, resposta_2, resposta_3, resposta_4, resposta_certa, dificuldade, id, tema, tempo, tipo);

    Pergunta_node *temp_node = pergunta_head;

    while (temp_node->next != NULL)
    {
        if (temp_node->pergunta->id == id)
        {
            free_pergunta(temp_node->pergunta);
            temp_node->pergunta = p;
            return 0;
        }

        temp_node = temp_node->next;
    }

    if (temp_node->pergunta->id == id)
    {
        free_pergunta(temp_node->pergunta);
        temp_node->pergunta = p;
        return 0;
    }

    error("Pergunta.id not found edit_pergunta");
    return 0;
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
        error("O programa deve ter pelo menos 1 pergunta (LL delete_pergunta)");
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
