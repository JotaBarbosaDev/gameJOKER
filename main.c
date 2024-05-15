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
*/

/*
todo:
    perguntas.c
        get_question
        save_perguntas
        load_perguntas


*/

int main(int argc, char *argv[])
{
    unsigned long simple_ash = djb2("ola");
    printf("HASH -> %lu\n", simple_ash);

    unsigned long simple_ash2 = djb2("ola2defr");
    printf("HASH -> %lu\n", simple_ash2);

    unsigned long simple_ash3 = djb2("wfehiuwrhfiuerhf");
    printf("HASH -> %lu\n", simple_ash3);

    Pergunta *per = create_pergunta("1", "Lisboa", "Porto", "Coimbra", "Faro", 0, 1, 1, 3, 10.0, 0);
    init_perguntas(per);

    add_pergunta("2", "Lisboa2", "Porto2", "Coimbra2", "Faro2", 5, 6, 2, 8, 20.0, 1);
    add_pergunta("3", "Lisboa3", "Porto3", "Coimbra3", "Faro3", 9, 10, 3, 12, 40.0, 2);
    add_pergunta("4", "Lisboa4", "Porto4", "Coimbra4", "Faro4", 9, 10, 4, 12, 40.0, 2);

    edit_pergunta("4", "Lisboa4", "Porto4", "Coimbra4", "Faro4", 13, 14, 4, 15, 50.0, 3);

    delete_pergunta(4);
    delete_pergunta(1);
    delete_pergunta(2);

    add_pergunta("5", "5", "5", "5", "5", 0, 1, 5, 0, 10, 0);
    // print_pergunta();

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

    printf("START\n");
    info("Starting Joca");
    main_UI(argc, argv);
    return 0;
}