#include "main.h"
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
binary tree search

hash tables      //encontrar / salvar jogadores



falta jogo.c, onde mantemos as informacoes do jogo tipo tempo, perguntas, respostas, pontuacao, numero de jocas, etc
*/

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
}

int main(int argc, char *argv[])
{
    if (test_hash() == -1)
    {
        return -1;
    }

    // Pergunta *per = create_pergunta("1rg", "Lisboa", "Porto", "Coimbra", "Faro", 0, 1, 1, 3, 10.0, 0);
    // init_perguntas(per);
    // add_pergunta("2egre", "Lisboa2", "Porto2", "Coimbra2", "Faro2", 5, 6, 2, 8, 20.0, 1);
    // add_pergunta("3grehgeg", "Lisboa3", "Porto3", "Coimbra3", "Faro3", 9, 10, 3, 12, 40.0, 2);
    // add_pergunta("4reger", "Lisboa4", "Porto4", "Coimbra4", "Faro4", 9, 10, 4, 12, 40.0, 2);
    // add_pergunta("5thrh", "5fkopr", "5ijrejg", "5voper", "5dwedn", 0, 1, 5, 0, 10, 0);
    // add_pergunta("6hrt", "6rif", "6", "6", "6vreçkg", 0, 1, 6, 0, 10, 0);
    // add_pergunta("7erhe4g", "7reg", "7erg", "7wrg", "7erg", 0, 1, 7, 0, 10, 0);
    // add_pergunta("8g4trg", "8tgrt", "8rth", "8", "8rth", 0, 1, 8, 0, 10, 0);
    // add_pergunta("9grtg", "9kjhghk", "9909", "9TRIGOOOOO", "9dewf", 0, 1, 9, 0, 11, 0);
    // save_perguntas();

    load_perguntas();

    Pergunta **perguntas_get = get_all_perguntas();
    int number_perguntas = get_number_of_perguntas();
    for (int i = 0; i < number_perguntas; i++)
    {
        printf("Pergunta -> %s\n\n", perguntas_get[i]->pergunta);
        printf("Resposta 1 -> %s\n", perguntas_get[i]->respostas[0]);
        printf("Resposta 2 -> %s\n", perguntas_get[i]->respostas[1]);
        printf("Resposta 3 -> %s\n", perguntas_get[i]->respostas[2]);
        printf("Resposta 4 -> %s\n", perguntas_get[i]->respostas[3]);
        printf("Resposta certa -> %d\n", perguntas_get[i]->resposta_certa);
        printf("Dificuldade -> %d\n", perguntas_get[i]->dificuldade);
        printf("ID -> %d\n", perguntas_get[i]->id);
        printf("Tema -> %d\n", perguntas_get[i]->tema);
        printf("Tempo -> %f\n", perguntas_get[i]->tempo);
        printf("Tipo -> %d\n", perguntas_get[i]->tipo);
        printf("\n\n");
    }

    // printf("START\n");
    // info("Starting Joca");
    // main_UI(argc, argv);
    return 0;
}