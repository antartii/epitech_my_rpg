/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** init_buttons_action
*/

#include "my_rpg.h"

int init_buttons_action(button_t **buttons)
{
    set_starting_screen_action(buttons);
    set_fighting_button_action(buttons);
    return SUCCESS;
}
