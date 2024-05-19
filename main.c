#include "main.h"
#include "user.h"
#include "perguntas.h"
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
}

int main(int argc, char *argv[])
{
    if (test_hash() == -1)
    {
        return -1;
    }

    load_users();
    // print_users();

    Pergunta *per = create_pergunta("Qual é a capital de Portugal", "Lisboa", "Porto", "Coimbra", "Faro", 0, 0, 0, 0, 10.0, 0);
    init_perguntas(per);
    add_pergunta("Qual é a capital de Espanha", "Madrid", "Barcelona", "Sevilha", "Valencia", 0, 0, 1, 0, 10.0);
    add_pergunta("Qual é a capital de França", "Paris", "Marselha", "Lyon", "Toulouse", 0, 0, 2, 0, 10.0);
    add_pergunta("Qual é a capital de Inglaterra", "Londres", "Manchester", "Liverpool", "Birmingham", 0, 0, 2, 0, 10.0);
    add_pergunta("Qual é a capital de Alemanha", "Berlim", "Munique", "Hamburgo", "Colónia", 0, 0, 0, 0, 10.0);
    add_pergunta("Qual é a capital de Itália", "Roma", "Milão", "Nápoles", "Turim", 0, 0, 3, 0, 10.0);
    add_pergunta("Qual é a capital de Rússia", "Moscou", "São Petersburgo", "Novosibirsk", "Ecaterimburgo", 0, 0, 5, 0, 10.0);
    add_pergunta("Qual é a capital de China", "Pequim", "Xangai", "Cantão", "Shenzhen", 0, 0, 4, 0, 10.0);
    add_pergunta("Qual é a capital de Japão", "Tóquio", "Osaka", "Nagoya", "Sapporo", 0, 0, 5, 0, 10.0);
    save_perguntas();

    load_perguntas();

    // Pergunta **perguntas_get = get_all_perguntas();
    // int number_perguntas = get_number_of_perguntas();
    // for (int i = 0; i < number_perguntas; i++)
    // {
    //     printf("Pergunta -> %s\n\n", perguntas_get[i]->pergunta);
    //     printf("Resposta 1 -> %s\n", perguntas_get[i]->respostas[0]);
    //     printf("Resposta 2 -> %s\n", perguntas_get[i]->respostas[1]);
    //     printf("Resposta 3 -> %s\n", perguntas_get[i]->respostas[2]);
    //     printf("Resposta 4 -> %s\n", perguntas_get[i]->respostas[3]);
    //     printf("Resposta certa -> %d\n", perguntas_get[i]->resposta_certa);
    //     printf("Dificuldade -> %d\n", perguntas_get[i]->dificuldade);
    //     printf("ID -> %d\n", perguntas_get[i]->id);
    //     printf("Tema -> %d\n", perguntas_get[i]->tema);
    //     printf("Tempo -> %f\n", perguntas_get[i]->tempo);
    //     printf("Tipo -> %d\n", perguntas_get[i]->tipo);
    //     printf("\n\n");
    // }

    printf("START\n");
    info("Starting Joca");
    main_UI(argc, argv);
    return 0;
}
