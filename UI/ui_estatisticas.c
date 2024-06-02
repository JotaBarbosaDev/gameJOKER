#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "../estatisticas/estatisticas.h"
#include "ui.h"

void ssearch_user_ui();

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
GtkWidget *search_user_input;
GtkWidget *search_user_button;
void search_user_function()
{
    // get inout from search_user_input

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(search_user_input));

    User *all_users_get = alloc_mem_for_sort();
    all_users_get = sort_users_by_name(all_users_get);

    User *user = search_binary_by_username(all_users_get, 0, get_number_of_users(), (char *)username);

    if (user == NULL)
    {
        error("User not found");
        return;
    }

    clear_all();

    const gchar *id = g_strdup_printf("%d", user->id);
    create_label("show_id_user_ui", id);

    create_label("show_username_user_ui", user->username);

    const gchar *vitorias = g_strdup_printf("%d", user->numero_de_vitorias);
    create_label("show_numero_de_vitorias_user_ui", vitorias);

    create_label("show_patamar_maximo_user_ui", niveis[user->patamar_maximo]);

    const gchar *jocas_ganhos = g_strdup_printf("%d", user->jocas_ganhos);
    create_label("show_tempo_total_user_ui", jocas_ganhos);

    const gchar *perguntas = g_strdup_printf("%d", user->numero_de_perguntas);
    create_label("show_numero_de_perguntas_user_ui", perguntas);

    const gchar *jogos_jogados = g_strdup_printf("%d", user->numero_de_jogos_jogados);
    create_label("show_numero_de_jogos_jogados_user_ui", jogos_jogados);

    const gchar *pontuacao_maxima = g_strdup_printf("%d", user->pontuacao_maxima);
    create_label("show_numero_de_jogos_ganhos_user_ui", pontuacao_maxima);

    const gchar *pontuacao_total = g_strdup_printf("%d", user->pontuacao_total);
    create_label("show_numero_de_jogos_perdidos_user_ui", pontuacao_total);

    const gchar *jogos_cancelados = g_strdup_printf("%d", user->numero_de_jogos_cancelados_por_falta_de_tempo);
    create_label("show_numero_de_jogos_cancelados_por_falta_de_tempo_user_ui", jogos_cancelados);

    const gchar *faceis_certas = g_strdup_printf("%d", user->faceis_certas);
    create_label("show_faceis_certas_user_ui", faceis_certas);

    const gchar *faceis_erradas = g_strdup_printf("%d", user->faceis_erradas);
    create_label("show_faceis_erradas_user_ui", faceis_erradas);

    const gchar *medios_certas = g_strdup_printf("%d", user->medios_certas);
    create_label("show_medios_certas_user_ui", medios_certas);

    const gchar *medios_erradas = g_strdup_printf("%d", user->medios_erradas);
    create_label("show_medios_erradas_user_ui", medios_erradas);

    const gchar *dificeis_certas = g_strdup_printf("%d", user->dificeis_certas);
    create_label("show_dificeis_certas_user_ui", dificeis_certas);

    const gchar *dificeis_erradas = g_strdup_printf("%d", user->dificeis_erradas);
    create_label("show_dificeis_erradas_user_ui", dificeis_erradas);

    // daqui
    const gchar *last_game_date;
    if (user->last_game_date[1] > 9)
    {
        last_game_date = g_strdup_printf("%d/%d/%d %d:%d", user->last_game_date[0], user->last_game_date[1], user->last_game_date[2], user->last_game_date[3], user->last_game_date[4]);
    }
    else
    {
        last_game_date = g_strdup_printf("%d/0%d/%d %d:%d", user->last_game_date[0], user->last_game_date[1], user->last_game_date[2], user->last_game_date[3], user->last_game_date[4]);
    }
    create_label("show_last_game_date_user_ui", last_game_date);

    const gchar *born_date;
    if (user->born_date[1] > 9)
    {
        born_date = g_strdup_printf("%d/%d/%d", user->born_date[0], user->born_date[1], user->born_date[2]);
    }
    else
    {
        born_date = g_strdup_printf("%d/0%d/%d", user->born_date[0], user->born_date[1], user->born_date[2]);
    }
    create_label("show_born_date_user_ui", born_date);

    create_label("show_nacionalidade_user_ui", user->nacionalidade);
    create_label("show_full_name_user_ui", user->full_name);

    // labels
    create_label("id_user_ui", "ID:");

    create_label("full_name_user_ui", "Nome completo:");
    create_label("last_game_date_user_ui", "Ultimo jogo:");

    create_label("numero_de_vitorias_user_ui", "Vitórias:");
    create_label("patamar_maximo_user_ui", "Patamar maximo:");
    create_label("tempo_total_user_ui", "Jocas ganhos:");
    create_label("numero_de_perguntas_user_ui", "Perguntas respondidas:");
    create_label("numero_de_jogos_jogados_user_ui", "Jogos jogados:");
    create_label("numero_de_jogos_ganhos_user_ui", "Pontuação Maxima:");
    create_label("numero_de_jogos_perdidos_user_ui", "Pontuação Total:");
    create_label("numero_de_jogos_cancelados_por_falta_de_tempo_user_ui", "Perguntas erradas por falta de tempo:");
    create_label("faceis_certas_user_ui", "Faceis certas:");
    create_label("faceis_erradas_user_ui", "Faceis erradas:");
    create_label("medios_certas_user_ui", "Medios certas:");
    create_label("medios_erradas_user_ui", "Medios erradas:");
    create_label("dificeis_certas_user_ui", "Dificeis certas:");
    create_label("dificeis_erradas_user_ui", "Dificeis erradas:");

    ssearch_user_ui(0);
}

void ssearch_user_ui(int clear)
{
    if (clear)
        clear_all();

    search_user_input = create_entry("search_input");
    search_user_button = create_button("search_button", "Search", search_user_function);

    create_button("button", "Back", menu_admin_estatistica);

    gtk_widget_show_all(window);
    gtk_main();
}

GtkWidget *pontuacao_input;

void search_binary_tree()
{
    const gchar *pontuacao = gtk_entry_get_text(GTK_ENTRY(pontuacao_input));

    if (strlen(pontuacao) == 0)
    {
        error("Invalid input");
        return;
    }

    int pontuacao_int = atoi(pontuacao);

    JogoJoca *jogo = get_closest_jogo_from_tree(pontuacao_int);

    if (jogo == NULL)
    {
        error("Jogo not found");
        return;
    }

    const gchar *pont_show = g_strdup_printf("%d", jogo->pontuacao);

    // show all stats from jogo

    clear_all();

    create_label("label_arvore_found", "O jogo mais proximo encontrado foi:");
    create_label("show_pontuacao", pont_show);

    pontuacao_input = create_entry("search_input_bin_tree");

    GtkWidget *search_button = create_button("search_button_bin_tree", "Search", search_binary_tree);

    gtk_widget_show_all(window);
    gtk_main();
}

void show_tree_stats()
{
    clear_all();

    pontuacao_input = create_entry("search_input_bin_tree");

    GtkWidget *search_button = create_button("search_button_bin_tree", "Search", search_binary_tree);

    gtk_widget_show_all(window);
    gtk_main();
}