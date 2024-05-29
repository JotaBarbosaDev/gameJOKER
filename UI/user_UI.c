#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "ui.h"

int current_id = 0;
int max_id_user = 0;

void go_right_user()
{
    max_id_user = get_last_id();
    if (current_id < max_id_user)
    {
        current_id++;
        if (does_user_exist(current_id))
        {
            start_user_UI();
        }
        else
        {
            go_right_user();
        }
    }
    else
    {
        current_id = 0;
        if (does_user_exist(current_id))
        {
            start_user_UI();
        }
        else
        {
            go_right_user();
        }
        start_user_UI();
    }
}

void go_left_user()
{
    max_id_user = get_last_id();
    if (current_id > 0)
    {
        current_id--;
        if (does_user_exist(current_id))
        {
            start_user_UI();
        }
        else
        {
            go_left_user();
        }
    }
    else
    {
        current_id = max_id_user;
        if (does_user_exist(current_id))
        {
            start_user_UI();
        }
        else
        {
            go_left_user();
        }
    }
}
void start_user_UI()
{
    clear_all();

    if (does_user_exist(current_id) == 0)
    {
        error("User does not exist");
    }
    else
    {

        User *user = get_users_by_id(current_id);

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
    }
    create_label("id_user_ui", "ID:");
    create_label("username_user_ui", "Nome:");
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

    create_button("go_left_user", "<", go_left_user);
    create_button("go_right_user", ">", go_right_user);

    create_button("leave_creation_button", "<", menu_admin_quests);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}
