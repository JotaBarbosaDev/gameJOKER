#include "main.h"

/*
register_user
login_user
save_users
load_users


ATENCAOOO
struct do jogador deve guardar informacao de jogos jogados, pontuacao, numero de jocas
*/

// @brief Hash function to hash a string
unsigned long djb2(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}