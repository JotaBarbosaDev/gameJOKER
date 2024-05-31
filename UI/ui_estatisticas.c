#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "../estatisticas/estatisticas.h"
#include "ui.h"

void show_last_10_games()
{
    clear_all();
    JogoJoca *stack = get_stack();
    User *_cur_player;

    GtkWidget *list = create_list();

    add_array_of_elements_to_list_horizontal(list, (const gchar *[]){
                                                       "Player ID",
                                                       "Username",
                                                       "Pontuacao",
                                                       "Patamar",
                                                   },
                                             4, 10, "list_header", 100, 50);

    for (int i = 0; i < 10; i++)
    {
        if (stack[i].ending == 0)
        {
            error("This game is not finished");
            continue;
        }

        char pontuacao[10];
        char multiplicador[10];
        char player_id[10];

        sprintf(pontuacao, "%d", stack[i].pontuacao);
        sprintf(multiplicador, "%f", stack[i].multiplicador);
        sprintf(player_id, "%d", stack[i].player_id);

        _cur_player = get_users_by_id(stack[i].player_id);

        add_array_of_elements_to_list_horizontal(list, (const gchar *[]){player_id, _cur_player->username, pontuacao, niveis[stack[i].joca_level]}, 4, 10, NULL, 100, 35);
    }

    gtk_widget_show_all(window);
    gtk_main();
}