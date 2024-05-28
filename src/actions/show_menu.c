/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** show_menu
*/

#include "my_rpg.h"

int hide_menu(game_data_t *game_data, char const *menu_name)
{
    menu_t *menu = NULL;

    if (game_data == NULL || game_data->menus == NULL || menu_name == NULL)
        return ERR;
    menu = get_menu(game_data->menus, menu_name);
    if (menu == NULL)
        return ERR;
    for (int i = 0; menu->buttons[i] != NULL; i += 1)
        menu->buttons[i]->sprite->visibility = HIDDEN;
    menu->visibility = HIDDEN;
    return SUCCESS;
}

int show_menu(game_data_t *game_data, char const *menu_name)
{
    menu_t *menu = NULL;

    if (game_data == NULL || menu_name == NULL)
        return ERR;
    menu = get_menu(game_data->menus, menu_name);
    if (menu == NULL)
        return ERR;
    for (int i = 0; menu->buttons[i] != NULL; i += 1) {
        menu->buttons[i]->sprite->visibility = ACTIVE;
        change_button_state(menu->buttons[i]->sprite, DEFAULT);
    }
    menu->visibility = ACTIVE;
    return SUCCESS;
}

int show_only_this_menu(game_data_t *game_data, char const *menu_name)
{
    if (game_data == NULL || game_data->menus == NULL)
        return ERR;
    for (int i = 0; game_data->menus[i] != NULL; i += 1) {
        if (strcmp(game_data->menus[i]->key, menu_name) == 0)
            game_data->menus[i]->visibility = ACTIVE;
        else {
            hide_menu(game_data, game_data->menus[i]->key);
            game_data->menus[i]->visibility = HIDDEN;
        }
    }
    show_menu(game_data, menu_name);
    return SUCCESS;
}
