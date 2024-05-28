#include "main.h"
#include "user/user.h"
#include "perguntas/perguntas.h"
#include "UI/ui.h"
#include <stdio.h>

// todo:
/*
-perguntas em listas ligadas
-em ficheiro bin deve guardar perguntas/jogadores/jogos


materias para usar
linked list     :D
stacks          ->ultimos jogos jogados

binary search
insertion sort    //usar os 2 para ordenar as jogos por jogadores e encontrar jogadores com binary search

trees             //usar para ordernar jogos por pontuacao e encontrar jogos com mais ou menos q x pontos
binary tree search     //fzr representacao grafica de jogos sistema de pontos:D

hash tables      //encontrar / salvar jogadores




//maiisisisis
fix no mac das merdas
resize em tudo q é merda
*/

char temas[9][20] = {"Geografia", "Historia", "Ciencia", "Desporto", "Arte", "Tecnologia", "Matematica", "Literatura", "Geral"};
char dificuldades[3][20] = {"Facil", "Medio", "Dificil"};

int getRandomNumber(int x)
{
    return rand() % (x + 1);
}

int test_hash()
{
    unsigned long simple_hash = djb2("ola");
    printf("HASH -> %lu\n", simple_hash); //->193501537

    unsigned long simple_hash2 = djb2("ola2defr");
    printf("HASH -> %lu\n", simple_hash2); // ->7572758759602260

    unsigned long simple_hash3 = djb2("wfehiuwrhfiuerhf");
    printf("HASH -> %lu\n", simple_hash3); // -> 14512354368336641287

    if (simple_hash == 193501537)
    {
        okay("Hash function1 working");
    }
    else
    {
        error("Hash function not working");
        return -1;
    }

    if (simple_hash2 == 7572758759602260)
    {
        okay("Hash function2 working");
    }
    else
    {
        error("Hash function2 not working");
        return -1;
    }

    if (simple_hash3 == 14512354368336641287UL) // UL -> unsigned long
    {
        okay("Hash function3 working");
    }
    else
    {
        error("Hash function3 not working");
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (test_hash() == -1)
    {
        return -1;
    }

    load_users();
    print_users();

    return 0;
    load_perguntas();

    printf("START\n");
    info("Starting Joca");
    main_UI(argc, argv);
    return 0;
}
