#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "../UI/ui.h"
#include "estatisticas.h"

#define STACK_LENGTH 10
JogoJoca main_stack[STACK_LENGTH];

void read_stack()
{
    FILE *file = fopen("BIN/stack.bin", "rb");

    if (file == NULL)
    {
        error("Error opening file");
        return;
    }

    fread(&main_stack, sizeof(JogoJoca), STACK_LENGTH, file);
    fclose(file);
    okay("Stack loaded");
}

void write_stack()
{
    FILE *file = fopen("BIN/stack.bin", "wb");

    if (file == NULL)
    {
        error("Error opening file");
        return;
    }

    fwrite(&main_stack, sizeof(JogoJoca), STACK_LENGTH, file);
    fclose(file);
    okay("Stack Written");
}

void clear_stack()
{
    for (int i = 0; i < STACK_LENGTH; i++)
    {
        main_stack[i].current_pergunta = 0;
        main_stack[i].current_dificuldade = 0;
        main_stack[i].current_tema = 0;
        main_stack[i].already_shown = 0;
        main_stack[i].already_shown_len = 0;
        main_stack[i].ending = 0;
        main_stack[i].joca_level = 0;
        main_stack[i].jocas_number = 0;
        main_stack[i].pontuacao = 0;
        main_stack[i].multiplicador = 0;
        main_stack[i].ff = 0;
        main_stack[i].ff_certas = 0;
        main_stack[i].player_id = -1;
    }
    write_stack();
}

void add_jogo_to_stack(JogoJoca jogo)
{
    if (jogo.ending == 0)
        error("Jogo not played");

    for (int i = 0; i < STACK_LENGTH - 1; i++)
    {
        main_stack[i] = main_stack[i + 1];
    }

    main_stack[9] = jogo;

    write_stack();
}

void printf_stack()
{
    for (int i = 0; i < STACK_LENGTH; i++)
    {
        if (main_stack[i].ending == 0)
        {
            info("Jogo %d not played", i);
            continue;
        }
        printf("Jogo %d\n", i);
        printf("Current pergunta: %d\n", main_stack[i].current_pergunta);
        printf("Current dificuldade: %d\n", main_stack[i].current_dificuldade);
        printf("Current tema: %d\n", main_stack[i].current_tema);
        printf("Ending: %d\n", main_stack[i].ending);
        printf("Joca level: %d\n", main_stack[i].joca_level);
        printf("Jocas number: %d\n", main_stack[i].jocas_number);
        printf("Pontuacao: %d\n", main_stack[i].pontuacao);
        printf("Multiplicador: %f\n", main_stack[i].multiplicador);
        printf("FF: %d\n", main_stack[i].ff);
        printf("FF certas: %d\n", main_stack[i].ff_certas);
        printf("Player id: %d\n", main_stack[i].player_id);
        printf("\n\n\n");
    }
}