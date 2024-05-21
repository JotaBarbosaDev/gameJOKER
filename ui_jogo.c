#include "main.h"
#include "perguntas.h"
#include "user.h"

Pergunta *cur_pergunta;
JogoJoca jogo;
char cur_joca_level[10];

void game_start();

void draw_joca_level()
{
    // 10 patamares de 0,100,200,500,1000,5000,10000,20000,50000,100000
    char *niveis[] = {"0", "100", "200", "500", "1000", "5000", "10000", "20000", "50000", "100000"};

    strcpy(cur_joca_level, niveis[jogo.joca_level]);

    create_label("jocaLevel", "Prêmio:");
    create_label("current_joca_level", cur_joca_level);

    GtkWidget *label1 = create_label("jocaLevelNumber0", "0");
    GtkWidget *label2 = create_label("jocaLevelNumber1", "100");
    GtkWidget *label3 = create_label("jocaLevelNumber2", "200");
    GtkWidget *label4 = create_label("jocaLevelNumber3", "500");
    GtkWidget *label5 = create_label("jocaLevelNumber4", "1000");
    GtkWidget *label6 = create_label("jocaLevelNumber5", "5000");
    GtkWidget *label7 = create_label("jocaLevelNumber6", "10 000");
    GtkWidget *label8 = create_label("jocaLevelNumber7", "20 000");
    GtkWidget *label9 = create_label("jocaLevelNumber8", "50 000");
    GtkWidget *label10 = create_label("jocaLevelNumber9", "100 000");

    GtkWidget *arr[] = {label1, label2, label3, label4, label5, label6, label7, label8, label9, label10};

    GdkRGBA color;
    gdk_rgba_parse(&color, "#00FF00");
    gtk_widget_override_color(arr[jogo.joca_level], GTK_STATE_FLAG_NORMAL, &color);

    create_label("NumeroJocas", "Jocas:");
    char jocas[10];
    sprintf(jocas, "%d", jogo.jocas_number);
    create_label("current_jocas", jocas);
}

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
        if (jogo.joca_level < 10)
            jogo.joca_level++;
        show_victory_or_lose_screen(1);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (jogo.jocas_number > 0)
            {
                jogo.jocas_number--;
            }
            else
            {
                if (jogo.joca_level > 0)
                    jogo.joca_level--;
            }
        }
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
    {
        jogo.current_dificuldade = 1;
    }
    if (jogo.already_shown_len == 7)
    {
        jogo.current_dificuldade = 2;
    }
    if (jogo.already_shown_len == 10)
    {
        printf("Parabens, acabou o jogo no nivel %d\n", jogo.joca_level);
        jogo.ending = 1;
        exit(0);
    }

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

    draw_joca_level();

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
    jogo.ending = 0;
    jogo.joca_level = 0;
    jogo.jocas_number = 9;

    create_button("start_game", "Iniciar Jogo", game_start);
    create_button("estatisticas_game", "Estatisticas", NULL);
    create_button("logout_game", "Logout", menu_principal);

    gtk_widget_show_all(window);
    gtk_main();
}