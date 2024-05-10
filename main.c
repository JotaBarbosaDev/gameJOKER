#include "main.h"
#include <stdio.h>

// todo:
/*
-perguntas em listas ligadas
-em ficheiro bin deve guardar perguntas/jogadores/jogos


materias para usar
linked list
stacks
filas
binary search
insertion sort
*/

int main(int argc, char *argv[])
{
    perguntas_struct.size = 0;

    add_pergunta("Qual é a capital de Portugal?", "Lisboa", "Porto", "Coimbra", "Faro", 0, 1, 1, 1, 10.0, 0);
    add_pergunta("Qual é a capital de Espanha?", "Madrid", "Barcelona", "Sevilha", "Valencia", 0, 1, 2, 1, 10.0, 0);
    add_pergunta("Qual é a capital de França?", "Paris", "Marselha", "Lyon", "Toulouse", 0, 1, 3, 1, 10.0, 0);

    print_pergunta();

    printf("START\n");
    info("Starting Joca");
    main_UI(argc, argv);
    return 0;
}