/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** check_box
*/

#include "my_rpg.h"

int check_box_action(game_data_t *game_data, char const *check_box_name)
{
    sprite_t *sprite = NULL;
    menu_t *active_menu = NULL;

    if (game_data == NULL || check_box_name == NULL)
        return ERR;
    sprite = find_sprite(game_data->sprites, check_box_name);
    active_menu = get_active_menu(game_data);
    if (sprite->rect.top == 0)
        change_sprite_state(sprite, 1);
    else
        change_sprite_state(sprite, 0);
    if (strcmp(active_menu->key, "settings_video") == 0)
        toggle_fullscreen(game_data);
    return SUCCESS;
}
