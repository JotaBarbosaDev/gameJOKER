#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "ui.h"

void start_user_UI()
{

    gtk_widget_show_all(window);
    okay("Menu admin user loaded successfully");
    gtk_main();
}