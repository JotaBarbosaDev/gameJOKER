#include "main.h"
#include <stdio.h>

// todo:
/*
-perguntas em listas ligadas
-em ficheiro bin deve guardar perguntas/jogadores/jogos


materias para usar
linked list     :D
stacks
filas
binary search
insertion sort
trees
*/

int main(int argc, char *argv[])
{
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
    }

    printf("START\n");
    info("Starting Joca");
    main_UI(argc, argv);
    return 0;
}