#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "ui.h"

void start_user_UI()
{
    clear_all();

    User *user =  get_users_by_id(0);

    create_label("id_user_ui", "ID:");
    const gchar *id = g_strdup_printf("%d", user->id);
    create_label("show_id_user_ui", id);

    create_label("username_user_ui", "Nome:");
    create_label("show_username_user_ui", user->username);

    create_label("numero_de_vitorias_user_ui", "Vitórias:");
    const gchar *vitorias = g_strdup_printf("%d", user->numero_de_vitorias);
    create_label("show_numero_de_vitorias_user_ui", vitorias);

    create_label("patamar_maximo_user_ui", "Patamar maximo:");
    const gchar *patamar = g_strdup_printf("%d", user->patamar_maximo);
    create_label("show_patamar_maximo_user_ui", patamar);

    create_label("tempo_total_user_ui", "Tempo jogado:");
    const gchar *tempo = g_strdup_printf("%d", user->tempo_total);
    create_label("show_tempo_total_user_ui", tempo);

    create_label("numero_de_perguntas_user_ui", "Perguntas respondidas:");
    const gchar *perguntas = g_strdup_printf("%d", user->numero_de_perguntas);
    create_label("show_numero_de_perguntas_user_ui", perguntas);

    create_label("numero_de_jogos_jogados_user_ui", "Jogos jogados:");
    const gchar *jogos_jogados = g_strdup_printf("%d", user->numero_de_jogos_jogados);
    create_label("show_numero_de_jogos_jogados_user_ui", jogos_jogados);

    create_label("numero_de_jogos_ganhos_user_ui", "Jogos ganhos:");
    const gchar *jogos_ganhos = g_strdup_printf("%d", user->numero_de_jogos_ganhos);
    create_label("show_numero_de_jogos_ganhos_user_ui", jogos_ganhos);

    create_label("numero_de_jogos_perdidos_user_ui", "Jogos perdidos:");
    const gchar *jogos_perdidos = g_strdup_printf("%d", user->numero_de_jogos_perdidos);
    create_label("show_numero_de_jogos_perdidos_user_ui", jogos_perdidos);

    create_label("numero_de_jogos_cancelados_por_falta_de_tempo_user_ui", "Perguntas erradas por falta de tempo:");
    const gchar *jogos_cancelados = g_strdup_printf("%d", user->numero_de_jogos_cancelados_por_falta_de_tempo);
    create_label("show_numero_de_jogos_cancelados_por_falta_de_tempo_user_ui", jogos_cancelados);

    create_label("faceis_certas_user_ui", "Faceis certas:");
    const gchar *faceis_certas = g_strdup_printf("%d", user->faceis_certas);
    create_label("show_faceis_certas_user_ui", faceis_certas);

    create_label("faceis_erradas_user_ui", "Faceis erradas:");
    const gchar *faceis_erradas = g_strdup_printf("%d", user->faceis_erradas);
    create_label("show_faceis_erradas_user_ui", faceis_erradas);

    create_label("medios_certas_user_ui", "Medios certas:");
    const gchar *medios_certas = g_strdup_printf("%d", user->medios_certas);
    create_label("show_medios_certas_user_ui", medios_certas);

    create_label("medios_erradas_user_ui", "Medios erradas:");
    const gchar *medios_erradas = g_strdup_printf("%d", user->medios_erradas);
    create_label("show_medios_erradas_user_ui", medios_erradas);

    create_label("dificeis_certas_user_ui", "Dificeis certas:");
    const gchar *dificeis_certas = g_strdup_printf("%d", user->dificeis_certas);
    create_label("show_dificeis_certas_user_ui", dificeis_certas);

    create_label("dificeis_erradas_user_ui", "Dificeis erradas:");
    const gchar *dificeis_erradas = g_strdup_printf("%d", user->dificeis_erradas);
    create_label("show_dificeis_erradas_user_ui", dificeis_erradas);

    create_button("go_left_user", "<", NULL);
    create_button("go_right_user", ">", NULL);

    create_button("leave_creation_button", "<", menu_admin_quests);
    


    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}



