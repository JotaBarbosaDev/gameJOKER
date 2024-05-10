#include "main.h"

Perguntas perguntas_struct;
char temas[5][20] = {"tema0", "tema1", "tema2", "tema3", "tema4"};

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
    // realloc memory for perguntas
    if (perguntas_struct.size == 0)
    {
        perguntas_struct.perguntas = (Pergunta *)malloc(sizeof(Pergunta));
    }
    else
    {
        perguntas_struct.perguntas = (Pergunta *)realloc(perguntas_struct.perguntas, (perguntas_struct.size + 1) * sizeof(Pergunta));
    }

    perguntas_struct.perguntas[perguntas_struct.size] = *p; // set pergunta na memoria

    perguntas_struct.size++; // incrementar o tamanho
}

void print_pergunta()
{
    for (int i = 0; i < perguntas_struct.size; i++)
    {
        printf("Pergunta: %s\n", perguntas_struct.perguntas[i].pergunta);
        printf("Respostas: %s %s %s %s\n", perguntas_struct.perguntas[i].respostas[0], perguntas_struct.perguntas[i].respostas[1], perguntas_struct.perguntas[i].respostas[2], perguntas_struct.perguntas[i].respostas[3]);
        printf("Resposta certa: %d\n", perguntas_struct.perguntas[i].resposta_certa);
        printf("Dificuldade: %d\n", perguntas_struct.perguntas[i].dificuldade);
        printf("ID: %d\n", perguntas_struct.perguntas[i].id);
        printf("Tema: %d\n", perguntas_struct.perguntas[i].tema);
        printf("Tempo: %f\n", perguntas_struct.perguntas[i].tempo);
        printf("Tipo: %d\n", perguntas_struct.perguntas[i].tipo);
        printf("\n\n");
    }
}
