#include "../main.h"
#include "../perguntas/perguntas.h"
#include "../user/user.h"
#include "../UI/ui.h"
#include "estatisticas.h"

#define STACK_LENGTH 10
JogoJoca main_stack[STACK_LENGTH];

Tree_Node *tree_root = NULL;

void read_stack()
{
    FILE *file = fopen("BIN/stack.bin", "rb");

    if (file == NULL)
    {
        error("Error opening file");
        return;
    }

    fread(&main_stack, sizeof(JogoJoca), STACK_LENGTH, file);
    fclose(file);
    okay("Stack loaded");
}

void write_stack()
{
    FILE *file = fopen("BIN/stack.bin", "wb");

    if (file == NULL)
    {
        error("Error opening file");
        return;
    }

    fwrite(&main_stack, sizeof(JogoJoca), STACK_LENGTH, file);
    fclose(file);
    okay("Stack Written");
}

void clear_stack()
{
    for (int i = 0; i < STACK_LENGTH; i++)
    {
        main_stack[i].current_pergunta = 0;
        main_stack[i].current_dificuldade = 0;
        main_stack[i].current_tema = 0;
        main_stack[i].already_shown = 0;
        main_stack[i].already_shown_len = 0;
        main_stack[i].ending = 0;
        main_stack[i].joca_level = 0;
        main_stack[i].jocas_number = 0;
        main_stack[i].pontuacao = 0;
        main_stack[i].multiplicador = 0;
        main_stack[i].ff = 0;
        main_stack[i].ff_certas = 0;
        main_stack[i].player_id = -1;
    }
    write_stack();
}

void add_jogo_to_stack(JogoJoca jogo)
{
    if (jogo.ending == 0)
        error("Jogo not played");

    for (int i = 0; i < STACK_LENGTH - 1; i++)
    {
        main_stack[i] = main_stack[i + 1];
    }

    main_stack[9] = jogo;

    write_stack();
}

void printf_stack()
{
    for (int i = 0; i < STACK_LENGTH; i++)
    {
        if (main_stack[i].ending == 0)
        {
            info("Jogo %d not played", i);
            continue;
        }
        printf("Jogo %d\n", i);
        printf("Current pergunta: %d\n", main_stack[i].current_pergunta);
        printf("Current dificuldade: %d\n", main_stack[i].current_dificuldade);
        printf("Current tema: %d\n", main_stack[i].current_tema);
        printf("Ending: %d\n", main_stack[i].ending);
        printf("Joca level: %d\n", main_stack[i].joca_level);
        printf("Jocas number: %d\n", main_stack[i].jocas_number);
        printf("Pontuacao: %d\n", main_stack[i].pontuacao);
        printf("Multiplicador: %f\n", main_stack[i].multiplicador);
        printf("FF: %d\n", main_stack[i].ff);
        printf("FF certas: %d\n", main_stack[i].ff_certas);
        printf("Player id: %d\n", main_stack[i].player_id);
        printf("\n\n\n");
    }
}

JogoJoca *get_stack()
{
    return main_stack;
}

User *alloc_mem_for_sort()
{
    int number_of_users = get_number_of_users();
    User *users = get_all_users();
    User *unsorted_users = malloc(sizeof(User) * number_of_users);

    for (int i = 0; i < number_of_users; i++)
    {
        unsorted_users[i] = users[i];
    }

    return unsorted_users;
}

// insertion sort
User *sort_users_by_name(User *unsorted_users)
{
    int number_of_users = get_number_of_users();

    for (int i = 1; i < number_of_users; i++)
    {
        User key = unsorted_users[i];
        int j = i - 1;

        while (j >= 0 && strcmp(unsorted_users[j].username, key.username) > 0)
        {
            unsorted_users[j + 1] = unsorted_users[j];
            j = j - 1;
        }
        unsorted_users[j + 1] = key;
    }

    return unsorted_users;
}

int check_two_dates(int date1[5], int date2[5])
{
    if (date1[0] > date2[0])
    {
        return 1;
    }
    else if (date1[0] < date2[0])
    {
        return -1;
    }
    else
    {
        if (date1[1] > date2[1])
        {
            return 1;
        }
        else if (date1[1] < date2[1])
        {
            return -1;
        }
        else
        {
            if (date1[2] > date2[2])
            {
                return 1;
            }
            else if (date1[2] < date2[2])
            {
                return -1;
            }
            else
            {
                if (date1[3] > date2[3])
                {
                    return 1;
                }
                else if (date1[3] < date2[3])
                {
                    return -1;
                }
                else
                {
                    if (date1[4] > date2[4])
                    {
                        return 1;
                    }
                    else if (date1[4] < date2[4])
                    {
                        return -1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
    }
}

User *sort_by_last_played_game()
{
    User *unsorted_users = alloc_mem_for_sort();
    int number_of_users = get_number_of_users();

    for (int i = 1; i < number_of_users; i++)
    {
        User key = unsorted_users[i];
        int j = i - 1;

        while (j >= 0 && check_two_dates(key.last_game_date, unsorted_users[j].last_game_date) == 1)
        {
            unsorted_users[j + 1] = unsorted_users[j];
            j = j - 1;
        }
        unsorted_users[j + 1] = key;
    }

    return unsorted_users;
}

User *search_binary_by_username(User *users, int l, int r, char *x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (strcmp(users[mid].username, x) == 0)
            return &users[mid];

        if (strcmp(users[mid].username, x) > 0)
            return search_binary_by_username(users, l, mid - 1, x);

        return search_binary_by_username(users, mid + 1, r, x);
    }

    return NULL;
}

void write_all_of_the_tree_to_bin_file(Tree_Node *root, FILE *file)
{

    if (root != NULL)
    {
        write_all_of_the_tree_to_bin_file((Tree_Node *)root->left, file);
        fwrite(&root->jogo, sizeof(JogoJoca), 1, file);
        write_all_of_the_tree_to_bin_file((Tree_Node *)root->right, file);
    }
}

void write_tree_to_bin_file(Tree_Node *root)
{
    FILE *file = fopen("BIN/tree.bin", "wb");

    if (file == NULL)
    {
        error("Error opening file");
        return;
    }

    write_all_of_the_tree_to_bin_file(root, file);
    fclose(file);
}

void read_all_of_the_tree_from_bin_file()
{
    FILE *file = fopen("BIN/tree.bin", "rb");

    if (file == NULL)
    {
        error("Error opening file");
        return;
    }

    Tree_Node *root = NULL;
    JogoJoca jogo;

    while (fread(&jogo, sizeof(JogoJoca), 1, file))
    {
        insert_tree_based_on_game_points(jogo);
    }

    fclose(file);
}

void insert_tree_based_on_game_points(JogoJoca jogo)
{
    Tree_Node *new_node = malloc(sizeof(Tree_Node));
    new_node->jogo = jogo;
    new_node->left = NULL;
    new_node->right = NULL;

    if (tree_root == NULL)
    {
        tree_root = new_node;
        okay("Jogo added to the root");
        write_tree_to_bin_file(tree_root);
        return;
    }

    Tree_Node *current = tree_root;
    Tree_Node *parent = NULL;

    while (1)
    {
        parent = current;

        if (jogo.pontuacao < current->jogo.pontuacao)
        {
            current = (Tree_Node *)current->left;

            if (current == NULL)
            {
                parent->left = (struct Tree_Node *)new_node;
                okay("Jogo added to the left");
                write_tree_to_bin_file(tree_root);
                return;
            }
        }
        else if (jogo.pontuacao > current->jogo.pontuacao)
        {
            current = (Tree_Node *)current->right;

            if (current == NULL)
            {
                parent->right = (struct Tree_Node *)new_node;
                okay("Jogo added to the right");
                write_tree_to_bin_file(tree_root);
                return;
            }
        }
        else
        {
            info("Jogo with the same pontuacao already exists");
            return;
        }
    }
}

void print_tree(Tree_Node *root)
{
    if (root != NULL)
    {
        print_tree((Tree_Node *)root->left);
        printf("Pontuacao: %d\n", root->jogo.pontuacao);
        print_tree((Tree_Node *)root->right);
    }
}

JogoJoca *get_closest_jogo_from_tree(int pontuacao)
{
    Tree_Node *current = tree_root;
    Tree_Node *closest = NULL;
    int diff = INT_MAX;

    while (current != NULL)
    {
        if (current->jogo.pontuacao == pontuacao)
        {
            closest = current;
            break;
        }
        else
        {
            if (diff > abs(current->jogo.pontuacao - pontuacao))
            {
                diff = abs(current->jogo.pontuacao - pontuacao);
                closest = current;
            }

            if (pontuacao < current->jogo.pontuacao)
            {
                current = (Tree_Node *)current->left;
            }
            else
            {
                current = (Tree_Node *)current->right;
            }
        }
    }

    return &closest->jogo;
}