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

    create_button("button", "Back", menu_admin_estatistica);

    gtk_widget_show_all(window);
    gtk_main();
}

void last_players_played_by_date()
{
    clear_all();

    GtkWidget *list = create_list();

    add_array_of_elements_to_list_horizontal(list, (const gchar *[]){
                                                       "Player ID",
                                                       "Username",
                                                       "Nacionalidade",
                                                       "Nome Completo",
                                                       "Data de Nascimento",
                                                   },
                                             5, 10, "list_header", 100, 50);

    User *sort_date = sort_by_last_played_game();

    for (int i = 0; i < get_number_of_users(); i++)
    {
        if (sort_date[i].id == -1)
            continue;
        if (sort_date[i].last_game_date[0] == 0)
            continue;

        char player_id[10];
        char born_date[10];

        sprintf(player_id, "%d", sort_date[i].id);
        sprintf(born_date, "%d/%d/%d", sort_date[i].born_date[0], sort_date[i].born_date[1], sort_date[i].born_date[2]);

        add_array_of_elements_to_list_horizontal(list, (const gchar *[]){player_id, sort_date[i].username, sort_date[i].nacionalidade, sort_date[i].full_name, born_date}, 5, 10, NULL, 100, 35);
    }
    create_button("button", "Back", menu_admin_estatistica);

    gtk_widget_show_all(window);
    gtk_main();
}

void got_to_last_patamar()
{
    clear_all();

    GtkWidget *list = create_list();

    add_array_of_elements_to_list_horizontal(list, (const gchar *[]){
                                                       "Player ID",
                                                       "Username",
                                                       "Nacionalidade",
                                                       "Nome Completo",
                                                       "Data de Nascimento",
                                                   },
                                             5, 10, "list_header", 100, 50);

    User *all_users = get_all_users();

    for (int i = 0; i < get_number_of_users(); i++)
    {
        if (all_users[i].id == -1)
            continue;

        if (all_users[i].numero_de_vitorias == 0)
            continue;

        char player_id[10];
        char born_date[10];

        sprintf(player_id, "%d", all_users[i].id);
        sprintf(born_date, "%d/%d/%d", all_users[i].born_date[0], all_users[i].born_date[1], all_users[i].born_date[2]);

        add_array_of_elements_to_list_horizontal(list, (const gchar *[]){player_id, all_users[i].username, all_users[i].nacionalidade, all_users[i].full_name, born_date}, 5, 10, NULL, 100, 35);
    }
    create_button("button", "Back", menu_admin_estatistica);

    gtk_widget_show_all(window);
    gtk_main();
}

void got_all_jokers()
{
    clear_all();

    GtkWidget *list = create_list();

    add_array_of_elements_to_list_horizontal(list, (const gchar *[]){"Player ID", "Username", "Nacionalidade", "Nome Completo", "Data de Nascimento", "Jokers Extra 4 Vezes"},
                                             6, 10, "list_header", 100, 50);

    User *all_users = get_all_users();

    for (int i = 0; i < get_number_of_users(); i++)
    {
        if (all_users[i].id == -1)
            continue;

        if (all_users[i].got_4_jokers == 0)
            continue;

        char player_id[10];
        char born_date[10];
        char got_4_jokers[10];

        sprintf(player_id, "%d", all_users[i].id);
        sprintf(born_date, "%d/%d/%d", all_users[i].born_date[0], all_users[i].born_date[1], all_users[i].born_date[2]);
        sprintf(got_4_jokers, "%d", all_users[i].got_4_jokers);

        add_array_of_elements_to_list_horizontal(list, (const gchar *[]){player_id, all_users[i].username, all_users[i].nacionalidade, all_users[i].full_name, born_date, got_4_jokers}, 6, 10, NULL, 100, 35);
    }
    create_button("button", "Back", menu_admin_estatistica);

    gtk_widget_show_all(window);
    gtk_main();
}