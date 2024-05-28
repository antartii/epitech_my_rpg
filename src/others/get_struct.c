/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** get_struct
*/

#include "my_rpg.h"

menu_t *get_active_menu(game_data_t *game_data)
{
    if (game_data == NULL || game_data->menus == NULL)
        return NULL;
    for (int i = 0; game_data->menus[i] != NULL; i += 1) {
        if (game_data->menus[i]->visibility == ACTIVE)
            return game_data->menus[i];
    }
    return NULL;
}
