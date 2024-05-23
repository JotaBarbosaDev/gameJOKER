#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"
#include "ui.h"
#include "../perguntas/perguntas.h"

// Criar tela admin -> quests

int current_pergunta_id = 0;

void edit_pergunta_func()
{
    const gchar *temp1 = gtk_entry_get_text(GTK_ENTRY(pergunta));
    pergunta_add = malloc(strlen(temp1) + 1);
    strcpy(pergunta_add, temp1);

    const gchar *temp2 = gtk_entry_get_text(GTK_ENTRY(resposta_1));
    resposta_1_add = malloc(strlen(temp2) + 1);
    strcpy(resposta_1_add, temp2);

    const gchar *temp3 = gtk_entry_get_text(GTK_ENTRY(resposta_2));
    resposta_2_add = malloc(strlen(temp3) + 1);
    strcpy(resposta_2_add, temp3);

    const gchar *temp4 = gtk_entry_get_text(GTK_ENTRY(resposta_3));
    resposta_3_add = malloc(strlen(temp4) + 1);
    strcpy(resposta_3_add, temp4);

    const gchar *temp5 = gtk_entry_get_text(GTK_ENTRY(resposta_4));
    resposta_4_add = malloc(strlen(temp5) + 1);
    strcpy(resposta_4_add, temp5);

    const gchar *temp6 = gtk_entry_get_text(GTK_ENTRY(tempo));
    tempo_add = atof(temp6);

    if (ff == 1)
    {
        resposta_3_add = malloc(4);
        strcpy(resposta_3_add, "NULL");

        resposta_4_add = malloc(4);
        strcpy(resposta_4_add, "NULL");
    }

    if (strlen(pergunta_add) == 0 || strlen(resposta_1_add) == 0 || strlen(resposta_2_add) == 0 || strlen(resposta_3_add) == 0 || strlen(resposta_4_add) == 0)
    {
        error("Campos não podem estar vazios");
        return;
    }

    if (tempo_add <= 0)
    {
        error("Tempo não pode ser menor ou igual a 0");
        return;
    }

    if (current_resposta_certa == -1)
    {
        error("Resposta certa não selecionada");
        return;
    }

    if (dificuldade_add == -1)
    {
        error("Dificuldade não selecionada");
        return;
    }

    if (tema_add == -1)
    {
        error("Tema não selecionado");
        return;
    }

    if (ff == -1)
    {
        error("Tipo não selecionado");
        return;
    }

    if (ff == 1 && current_resposta_certa > 1)
    {
        error("Resposta certa não pode ser maior que 2");
        return;
    }

    okay("Pergunta editada com sucesso");
    edit_pergunta(pergunta_add, resposta_1_add, resposta_2_add, resposta_3_add, resposta_4_add, current_resposta_certa, dificuldade_add, current_pergunta_id, tema_add, tempo_add, ff);
    clear_all_camps();
}

void set_all_camps_of_pergunta_id()
{
    Pergunta *p = get_pergunta_by_id(current_pergunta_id);

    gtk_entry_set_text(GTK_ENTRY(pergunta), p->pergunta);
    gtk_entry_set_text(GTK_ENTRY(resposta_1), p->respostas[0]);
    gtk_entry_set_text(GTK_ENTRY(resposta_2), p->respostas[1]);
    gtk_entry_set_text(GTK_ENTRY(resposta_3), p->respostas[2]);
    gtk_entry_set_text(GTK_ENTRY(resposta_4), p->respostas[3]);
    gtk_entry_set_text(GTK_ENTRY(tempo), g_strdup_printf("%f", p->tempo));

    current_resposta_certa = p->resposta_certa;
    dificuldade_add = p->dificuldade;
    tema_add = p->tema;
    tempo_add = p->tempo;
    ff = p->tipo;

    set_dificuldade(NULL, (gpointer)dificuldade_add, NULL);
    set_tema(NULL, (gpointer)tema_add, NULL);
    set_tipo(NULL, (gpointer)ff, NULL);
    set_resposta(NULL, (gpointer)current_resposta_certa);
}

void go_left_edit()
{
    if (current_pergunta_id == 0)
    {
        error("Não há mais perguntas para editar");
        return;
    }
    current_pergunta_id--;
    set_all_camps_of_pergunta_id();
}

void go_right_edit()
{
    if (current_pergunta_id == get_number_of_perguntas() - 1)
    {
        error("Não há mais perguntas para editar");
        return;
    }
    current_pergunta_id++;
    set_all_camps_of_pergunta_id();
}

void tela_edit_pergunta()
{
    current_resposta_certa = -1;
    dificuldade_add = -1;
    tema_add = -1;
    tempo_add = -1;
    tipo = -1;
    ff = -1;

    clear_all();

    pergunta = create_placeholder_entry("pergunta_input", "Pergunta");
    resposta_1 = create_placeholder_entry("resposta_1_input", "Resposta 1");
    resposta_2 = create_placeholder_entry("resposta_2_input", "Resposta 2");
    resposta_3 = create_placeholder_entry("resposta_3_input", "Resposta 3");
    resposta_4 = create_placeholder_entry("resposta_4_input", "Resposta 4");
    tempo = create_placeholder_entry("tempo_input", "Tempo (seg)");

    create_button("leave_creation_button", "<", menu_admin_quests);
    gtk_entry_set_width_chars(GTK_ENTRY(pergunta), 100);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_1), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_2), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_3), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(resposta_4), 48);
    gtk_entry_set_width_chars(GTK_ENTRY(tempo), 11);
    create_label("perguntaCerta_label", "Pergunta certa: ");
    GtkWidget *but1 = create_button("respostaCerta_1", "Resposta 1", set_resposta);
    GtkWidget *but2 = create_button("respostaCerta_2", "Resposta 2", set_resposta);
    GtkWidget *but3 = create_button("respostaCerta_3", "Resposta 3", set_resposta);
    GtkWidget *but4 = create_button("respostaCerta_4", "Resposta 4", set_resposta);
    array_resposta[0] = resposta_1;
    array_resposta[1] = resposta_2;
    array_resposta[2] = resposta_3;
    array_resposta[3] = resposta_4;
    create_label("dificulde_label", "Dificuldade: ");
    GtkWidget *but5 = create_button("dificuldadeEasy", "Facil", set_dificuldade);
    GtkWidget *but6 = create_button("dificuldadeMedium", "Media", set_dificuldade);
    GtkWidget *but7 = create_button("dificuldadeHard", "Dificil", set_dificuldade);
    g_signal_connect(but1, "clicked", G_CALLBACK(set_resposta), (gpointer)0);
    g_signal_connect(but2, "clicked", G_CALLBACK(set_resposta), (gpointer)1);
    g_signal_connect(but3, "clicked", G_CALLBACK(set_resposta), (gpointer)2);
    g_signal_connect(but4, "clicked", G_CALLBACK(set_resposta), (gpointer)3);

    array_dificuldade[0] = but5;
    array_dificuldade[1] = but6;
    array_dificuldade[2] = but7;
    g_signal_connect(but5, "clicked", G_CALLBACK(set_dificuldade), (gpointer)0);
    g_signal_connect(but6, "clicked", G_CALLBACK(set_dificuldade), (gpointer)1);
    g_signal_connect(but7, "clicked", G_CALLBACK(set_dificuldade), (gpointer)2);

    create_label("tema_label", "Tema: ");
    GtkWidget *but8 = create_button("tema_0", temas[0], NULL);
    GtkWidget *but9 = create_button("tema_2", temas[1], NULL);
    GtkWidget *but10 = create_button("tema_1", temas[2], NULL);
    GtkWidget *but11 = create_button("tema_3", temas[3], NULL);
    GtkWidget *but12 = create_button("tema_4", temas[4], NULL);
    GtkWidget *but13 = create_button("tema_5", temas[5], NULL);
    GtkWidget *but14 = create_button("tema_6", temas[6], NULL);
    GtkWidget *but15 = create_button("tema_7", temas[7], NULL);
    GtkWidget *but16 = create_button("tema_8", temas[8], NULL);

    g_signal_connect(but8, "clicked", G_CALLBACK(set_tema), (gpointer)0);
    g_signal_connect(but9, "clicked", G_CALLBACK(set_tema), (gpointer)1);
    g_signal_connect(but10, "clicked", G_CALLBACK(set_tema), (gpointer)2);
    g_signal_connect(but11, "clicked", G_CALLBACK(set_tema), (gpointer)3);
    g_signal_connect(but12, "clicked", G_CALLBACK(set_tema), (gpointer)4);
    g_signal_connect(but13, "clicked", G_CALLBACK(set_tema), (gpointer)5);
    g_signal_connect(but14, "clicked", G_CALLBACK(set_tema), (gpointer)6);
    g_signal_connect(but15, "clicked", G_CALLBACK(set_tema), (gpointer)7);
    g_signal_connect(but16, "clicked", G_CALLBACK(set_tema), (gpointer)8);

    array_tema[0] = but8;
    array_tema[1] = but9;
    array_tema[2] = but10;
    array_tema[3] = but11;
    array_tema[4] = but12;
    array_tema[5] = but13;
    array_tema[6] = but14;
    array_tema[7] = but15;
    array_tema[8] = but16;

    create_label("tipo_label", "Tipo: ");
    GtkWidget *but17 = create_button("type_normal", "Normal", NULL);
    GtkWidget *but18 = create_button("type_ff", "50/50", NULL);

    g_signal_connect(but17, "clicked", G_CALLBACK(set_tipo), (gpointer)0);
    g_signal_connect(but18, "clicked", G_CALLBACK(set_tipo), (gpointer)1);

    array_tipo[0] = but17;
    array_tipo[1] = but18;

    create_button("pergunta_create_button", "Editar Pergunta", edit_pergunta_func);

    create_button("go_left_edit", "<", go_left_edit);
    create_button("go_right_edit", ">", go_right_edit);
    set_all_camps_of_pergunta_id();

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}