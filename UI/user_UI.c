#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "ui.h"

void start_user_UI()
{
    clear_all();

    create_label("id_user_ui", "ID:");
    create_label("username_user_ui", "Nome:");
    create_label("numero_de_vitorias_user_ui", "Vitórias:");
    create_label("patamar_maximo_user_ui", "Patamar maximo:");
    create_label("tempo_total_user_ui", "Tempo jogado:");
    create_label("numero_de_perguntas_user_ui", "Perguntas respondidas:");
    create_label("numero_de_jogos_jogados_user_ui", "Jogos jogados:");
    create_label("numero_de_jogos_ganhos_user_ui", "Jogos ganhos:");
    create_label("numero_de_jogos_perdidos_user_ui", "Jogos perdidos:");
    create_label("numero_de_jogos_cancelados_por_falta_de_tempo_user_ui", "Perguntas erradas por falta de tempo:");
    create_label("faceis_certas_user_ui", "Faceis certas:");
    create_label("faceis_erradas_user_ui", "Faceis erradas:");
    create_label("medios_certas_user_ui", "Medios certas:");
    create_label("medios_erradas_user_ui", "Medios erradas:");
    create_label("dificeis_certas_user_ui", "Dificeis certas:");
    create_label("dificeis_erradas_user_ui", "Dificeis erradas:");

    create_button("go_left_user", "<", NULL);
    create_button("go_right_user", ">", NULL);
    


    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}



