/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** exit_action
*/

#include "my_rpg.h"

int exit_the_game(game_data_t *game_data, char const *str)
{
    if (game_data == NULL || str != NULL)
        return ERR;
    game_data->is_running = FALSE;
    return SUCCESS;
}
