#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <gtk/gtk.h>
#include "../UI/ui.h"

void read_stack();
void printf_stack();
void add_jogo_to_stack(JogoJoca jogo);
void clear_stack();
JogoJoca *get_stack();


User *alloc_mem_for_sort();
User *sort_users_by_name(User *unsorted_users);


#endif