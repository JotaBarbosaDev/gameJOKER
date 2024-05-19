#include "main.h"
#include "perguntas.h"
#include "user.h"

Pergunta *cur_pergunta;
JogoJoca jogo;

void game_start();

void show_victory_or_lose_screen(int victory)
{
    clear_all();
    if (victory)
    {
        create_label("jocaVitoria", "Certo!");
    }
    else
    {
        create_label("jocaDerrota", "Errado!");
    }
    g_timeout_add_seconds(1, (GSourceFunc)game_start, NULL);
    gtk_widget_show_all(window);
    gtk_main();
}

void check_resposta(GtkWidget *widget, gpointer data)
{
    long int resposta = (long int)data;
    if (resposta == cur_pergunta->resposta_certa)
    {
        show_victory_or_lose_screen(1);
    }
    else
    {
        show_victory_or_lose_screen(0);
    }
}

void game_start()
{
    cur_pergunta = get_random_pergunta();

    jogo.already_shown = realloc(jogo.already_shown, sizeof(int) * (jogo.already_shown_len + 1));
    jogo.already_shown[jogo.already_shown_len] = cur_pergunta->id;
    jogo.already_shown_len++;

    if (jogo.already_shown_len == 3)
        jogo.current_dificuldade = 1;
    if (jogo.already_shown_len == 7)
        jogo.current_dificuldade = 2;
    if (jogo.already_shown_len == 10)
        printf("Parabens, acabou o jogo\n");

    clear_all();
    create_label("jocaTITLE2", "JOCA");
    create_label("dif_indicator", dificuldades[cur_pergunta->dificuldade]);

    create_label("jocaPergunta", cur_pergunta->pergunta);

    GtkWidget *but0 = create_button("jocaResposta1Button", cur_pergunta->respostas[0], NULL);
    GtkWidget *but1 = create_button("jocaResposta2Button", cur_pergunta->respostas[1], NULL);
    GtkWidget *but2 = create_button("jocaResposta3Button", cur_pergunta->respostas[2], NULL);
    GtkWidget *but3 = create_button("jocaResposta4Button", cur_pergunta->respostas[3], NULL);

    g_signal_connect(but0, "clicked", G_CALLBACK(check_resposta), (gpointer)0);
    g_signal_connect(but1, "clicked", G_CALLBACK(check_resposta), (gpointer)1);
    g_signal_connect(but2, "clicked", G_CALLBACK(check_resposta), (gpointer)2);
    g_signal_connect(but3, "clicked", G_CALLBACK(check_resposta), (gpointer)3);

    gtk_widget_show_all(window);
    gtk_main();
}

int jogo_UI()
{
    divide_perguntas_by_difficulty();
    clear_all();
    create_label("jocaTITLE", "JOCA");

    jogo.already_shown_len = 0;
    jogo.current_pergunta = 0;
    jogo.current_dificuldade = 0;
    jogo.current_tema = 0;

    create_button("start_game", "Iniciar Jogo", game_start);
    create_button("estatisticas_game", "Estatisticas", NULL);
    create_button("logout_game", "Logout", NULL);

    gtk_widget_show_all(window);
    gtk_main();
}