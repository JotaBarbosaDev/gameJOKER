#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <gtk/gtk.h>
#include "../UI/ui.h"

typedef struct
{
    JogoJoca jogo;
    struct Tree_Node *left;
    struct Tree_Node *right;
} Tree_Node;

void read_stack();
void printf_stack();
void add_jogo_to_stack(JogoJoca jogo);
void clear_stack();
JogoJoca *get_stack();

User *alloc_mem_for_sort();
User *sort_users_by_name(User *unsorted_users);
User *sort_by_last_played_game();
User *search_binary_by_username(User *users, int l, int r, char *x);
void insert_tree_based_on_game_points(JogoJoca jogo);
void read_all_of_the_tree_from_bin_file();
void print_tree(Tree_Node *root);
void show_tree_stats();
JogoJoca *get_closest_jogo_from_tree(int pontuacao);

extern Tree_Node *tree_root;

#endif