#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "ui.h"

Pergunta *cur_pergunta;
JogoJoca jogo;
char cur_joca_level[10];
char *niveis[] = {"0", "100", "200", "500", "1000", "5000", "10000", "20000", "50000", "100000"};
GtkWidget *tempo_label;
float cur_tempo;
JogoJoca save_jogos[2048];

typedef struct timeout_struct
{
    guint timeout;
    GSource *source;
    int exists;
} timeout_struct;

timeout_struct timeout_arr[21];
#define timeout_arr_len 21

void game_start();

void free_timeout_arr()
{
    for (int i = 0; i < timeout_arr_len; i++)
    {
        if (timeout_arr[i].exists == 1)
        {
            g_source_remove(timeout_arr[i].timeout);
            timeout_arr[i].exists = 0;
        }
    }
}

void set_pontuation(int win)
{
    if (win)
    {
        jogo.pontuacao += 100 * jogo.multiplicador;
        jogo.multiplicador += 0.5;
    }
    else
    {
        if (jogo.pontuacao < 200)
            jogo.pontuacao = 0;
        else
            jogo.pontuacao -= 200;
        jogo.multiplicador = 1.0;
    }
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

void pergunta_certa()
{
    set_pontuation(1);
    if (jogo.joca_level < 10)
        jogo.joca_level++;
    show_victory_or_lose_screen(1);
}

void pergunta_certa_ff()
{
    jogo.ff_certas++;
    if (jogo.ff_certas == 6)
    {
        jogo.jocas_number++;
        jogo.ff_certas = 0;
    }
    printf("FF CERTAS %d\n", jogo.ff_certas);
    show_victory_or_lose_screen(1);
}

void pergunta_errada_ff()
{
    show_victory_or_lose_screen(0);
}

void pergunta_errada()
{
    set_pontuation(0);
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

void check_resposta(GtkWidget *widget, gpointer data)
{
    free_timeout_arr();

    long int resposta = (long int)data;
    if (resposta == cur_pergunta->resposta_certa)
    {
        if (jogo.ff == 1)
        {
            pergunta_certa_ff();
            return;
        }
        pergunta_certa();
    }
    else
    {
        if (jogo.ff == 1)
        {
            pergunta_errada_ff();
            return;
        }
        pergunta_errada();
    }
}

void show_seconds_label(int show_time)
{
    char tempo[10];
    sprintf(tempo, "%.1f", cur_tempo - show_time);
    gtk_label_set_text(GTK_LABEL(tempo_label), tempo);
}

void count_tempo_for_pergunta()
{
    cur_tempo = cur_pergunta->tempo;
    show_seconds_label(cur_tempo);

    for (int i = 0; i < timeout_arr_len; i++)
    {
        timeout_arr[i].exists = 0;
    }

    for (long int i = 0; i < cur_tempo; i++)
    {
        timeout_arr[i].timeout = (g_timeout_add_seconds(i, (GSourceFunc)show_seconds_label, (gpointer)i));
        timeout_arr[i].source = g_main_context_find_source_by_id(NULL, timeout_arr[i].timeout);
        timeout_arr[i].exists = 1;
    }

    timeout_arr[timeout_arr_len - 1].timeout = (g_timeout_add_seconds(cur_tempo, (GSourceFunc)pergunta_errada, NULL));
    timeout_arr[timeout_arr_len - 1].source = g_main_context_find_source_by_id(NULL, timeout_arr[timeout_arr_len - 1].timeout);
    timeout_arr[timeout_arr_len - 1].exists = 1;
}

void draw_joca_level()
{
    // 10 patamares de 0,100,200,500,1000,5000,10000,20000,50000,100000

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

    create_label("Multiplicador", "Multiplicador:");
    char multiplicador[10];
    sprintf(multiplicador, "%.1f", jogo.multiplicador);
    create_label("current_multiplicador", multiplicador);

    create_label("Pontuacao", "Pontuação:");
    char pontuacao[10];
    sprintf(pontuacao, "%d", jogo.pontuacao);
    create_label("current_pontuacao", pontuacao);

    GtkWidget *label11 = create_label("joca_tempo", "Tempo:");
    // create a thread
    tempo_label = create_label("current_tempo", "0");
    count_tempo_for_pergunta();
}

void ending_screen()
{
    // add jogo com stack
    clear_all();
    create_label("jocaEND2", "Parabéns, acabou o jogo!");
    create_label("jocaEND3", "Obrigado por jogar!");
    create_label("jocaEND4", "Pontuação final:");
    char jocas[10];
    sprintf(jocas, "%s", niveis[jogo.joca_level]);
    create_label("jocaEND5", jocas);
    create_button("jocaEND6", "Logout", menu_principal);
    create_button("jocaEND7", "Recomeçar", jogo_UI);
    create_button("jocaEND8", "Sair", exit);
    gtk_widget_show_all(window);
    gtk_main();
}

void game_start()
{

    /*
    50/50
    1,2,3->facil

    4,5,6,7,8,9,10,11,12,13,14,15,16,17,18->50/50

    19,20,21,22->media

    23,24,25,26,27,28,29,30,31,32,33,34,35,36,37->50/50

    38,39,40->dificil
    */
    cur_pergunta = get_random_pergunta();

    jogo.already_shown = realloc(jogo.already_shown, sizeof(int) * (jogo.already_shown_len + 1));
    jogo.already_shown[jogo.already_shown_len] = cur_pergunta->id;
    jogo.already_shown_len++;

    if (jogo.already_shown_len == 3)
    {
        jogo.ff_certas = 0;
        jogo.ff = 1;
    }
    else if (jogo.already_shown_len == 18)
    {
        jogo.ff = 0;
        jogo.current_dificuldade = 1; // passa para medio
        jogo.multiplicador += 1;
    }
    else if (jogo.already_shown_len == 22)
    {
        jogo.ff_certas = 0;
        jogo.ff = 1;
    }
    else if (jogo.already_shown_len == 37)
    {
        jogo.ff = 0;
        jogo.current_dificuldade = 2; // passa para dificil
        jogo.multiplicador += 2.5;
    }
    else if (jogo.already_shown_len == 41)
    {
        printf("Parabens, acabou o jogo no nivel %d\n", jogo.joca_level);
        ending_screen();
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

void jogo_UI()
{
    divide_perguntas_by_difficulty();
    print_all_pergutas_by_difficulty_and_50_50();
    clear_all();
    create_label("jocaTITLE", "JOCA");

    jogo.already_shown_len = 0;
    jogo.current_pergunta = 0;
    jogo.current_dificuldade = 0;
    jogo.current_tema = 0;
    jogo.ending = 0;
    jogo.joca_level = 0;
    jogo.jocas_number = 9;
    jogo.pontuacao = 0;
    jogo.multiplicador = 1.0;
    jogo.ff = 0;

    create_button("start_game", "Iniciar Jogo", game_start);
    create_button("estatisticas_game", "Estatisticas", NULL);
    create_button("logout_game", "Logout", menu_principal);

    gtk_widget_show_all(window);
    gtk_main();
}