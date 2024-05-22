#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"
#include "ui.h"
#include "../perguntas/perguntas.h"

int current_pergunta = 0;

void go_left_pergunta()
{
    current_pergunta--;
    if (current_pergunta < 0)
    {
        current_pergunta = get_number_of_perguntas() - 1;
    }
    ver_perguntas();
}

void go_right_pergunta()
{
    current_pergunta++;
    if (current_pergunta >= get_number_of_perguntas())
    {
        current_pergunta = 0;
    }
    ver_perguntas();
}

void ver_perguntas()
{
    clear_all();

    Pergunta **perguntas_get = get_all_perguntas();
    int number_perguntas = get_number_of_perguntas();
    int ff = 0;
    GtkWidget *label = create_label("pergunta_ver", perguntas_get[current_pergunta]->pergunta);
    GtkWidget *label1 = create_label("resposta1_ver", perguntas_get[current_pergunta]->respostas[0]);
    GtkWidget *label2 = create_label("resposta2_ver", perguntas_get[current_pergunta]->respostas[1]);
    GtkWidget *label3;
    GtkWidget *label4;
    if (strcmp(perguntas_get[current_pergunta]->respostas[2], "NULL") != 0)
    {
        label3 = create_label("resposta3_ver", perguntas_get[current_pergunta]->respostas[2]);
    }
    else
    {
        ff = 1;
    }
    if (strcmp(perguntas_get[current_pergunta]->respostas[3], "NULL") != 0)
    {
        label4 = create_label("resposta4_ver", perguntas_get[current_pergunta]->respostas[3]);
    }
    else
    {
        ff = 1;
    }
    GtkWidget *label8 = create_label("dificuldade_ver", dificuldades[perguntas_get[current_pergunta]->dificuldade]);
    GtkWidget *label10 = create_label("tema_ver", temas[perguntas_get[current_pergunta]->tema]);

    char id_str[10];
    sprintf(id_str, "%d", perguntas_get[current_pergunta]->id);
    GtkWidget *label12 = create_label("id_ver", id_str);

    GtkWidget *arr_respostas[4] = {label1, label2, label3, label4};
    GdkRGBA color;
    gdk_rgba_parse(&color, "#00FF00"); // Change the color code to the desired color
    if (ff == 1 && perguntas_get[current_pergunta]->resposta_certa > 1)
    {
        error("Resposta certa não pode ser maior que 2");
        return;
    }
    gtk_widget_override_color(arr_respostas[perguntas_get[current_pergunta]->resposta_certa], GTK_STATE_FLAG_NORMAL, &color);

    create_button("go_left_pergunta", "<", go_left_pergunta);
    create_button("go_right_pergunta", ">", go_right_pergunta);
    create_button("leave_creation_button", "<", menu_admin_quests);

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}