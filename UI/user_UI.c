#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "../estatisticas/estatisticas.h"
#include "ui.h"

int user_index = 0;

User *sorted_array = NULL;
int cur_number_of_users = -1;

void go_right_user()
{
    if (user_index == cur_number_of_users - 1)
    {
        user_index = 0;
    }
    else
    {
        user_index++;
    }

    start_user_UI();
}

void go_left_user()
{
    if (user_index == 0)
    {
        user_index = cur_number_of_users - 1;
    }
    else
    {
        user_index--;
    }

    start_user_UI();
}

void delete_user_UI_but()
{
    User *user = &sorted_array[user_index];

    if (!does_user_exist(user->id))
    {
        error("User does not exist");
        return;
    }

    delete_user_by_id(user->id);
    start_user_UI();
}

void start_user_UI()
{

    if (sorted_array == NULL)
    {
        cur_number_of_users = get_number_of_users();

        sorted_array = alloc_mem_for_sort();
        sorted_array = sort_users_by_name(sorted_array);
        if (cur_number_of_users == -1)
        {
            error("Error loading users user_UI.c");
            return;
        }
    }

    clear_all();

    User *user = &sorted_array[user_index];

    if (!does_user_exist(user->id))
    {
        error("User does not exist");
        user_index = 0;
        free(sorted_array);
        sorted_array = NULL;
        menu_admin_estatistica();
        return;
    }

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

    create_button("delete_user_button", "Delete", delete_user_UI_but);

    create_button("go_left_user", "<", go_left_user);
    create_button("go_right_user", ">", go_right_user);

    create_button("leave_creation_button", "Voltar", menu_admin_quests);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}
