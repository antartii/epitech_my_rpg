/*
** EPITECH PROJECT, 2024
** dev
** File description:
** fighting_action_button
*/

#include "my_rpg.h"

static int do_inv_button(game_data_t *game_data, char const *str)
{
    sprite_t *inv = find_sprite(game_data->sprites, "inv");

    if (str != NULL)
        return ERR;
    if (inv->visibility == FALSE) {
        inv->visibility = TRUE;
        return SUCCESS;
    }
    if (inv->visibility == TRUE)
        inv->visibility = FALSE;
    return SUCCESS;
}

int set_fighting_button_action(button_t **buttons)
{
    add_button_action(buttons, "flee_button", flee_button, "exploration");
    add_button_action(buttons, "backpack_button", do_inv_button, NULL);
    add_button_action(buttons, "attack_button", fight_button, "test");
    return SUCCESS;
}
