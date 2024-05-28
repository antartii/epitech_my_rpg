/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** decommand
*/

#include "my_rpg.h"

int devcommand_fullscreen(
    game_data_t *game_data, char const *state, char const *str)
{
    int *key_pressed = game_data->key_pressed;

    if (game_data == NULL || state == NULL || (str == NULL && str != NULL))
        return ERR;
    if ((key_pressed[sfKeyLControl] == TRUE ||
        key_pressed[sfKeyLControl] == TRUE) && game_data->mode == DEVMODE &&
            strcmp(state, "pressed") == 0) {
        toggle_fullscreen(game_data);
        puts("DEV COMMAND : TOGGLE FULLSCREEN");
    }
    return SUCCESS;
}

int devcommand_exit(game_data_t *game_data, char const *state, char const *str)
{
    int *key_pressed = game_data->key_pressed;

    if (game_data == NULL || state == NULL)
        return ERR;
    if ((key_pressed[sfKeyLControl] == TRUE ||
        key_pressed[sfKeyLControl] == TRUE) && game_data->mode == DEVMODE &&
        strcmp(str, "pressed") == 0) {
        game_data->is_running = FALSE;
        puts("DEV COMMAND : EXIT");
    }
    return SUCCESS;
}

int devcommand_godevmode(
    game_data_t *game_data, char const *state, char const *str)
{
    int *key_pressed = game_data->key_pressed;

    if (game_data == NULL || state == NULL || (str == NULL && str != NULL))
        return ERR;
    if ((key_pressed[sfKeyLControl] == TRUE ||
        key_pressed[sfKeyRControl] == TRUE) && key_pressed[sfKeyD] == TRUE &&
            key_pressed[sfKeyE] == TRUE && key_pressed[sfKeyV] == TRUE &&
                strcmp(state, "pressed") == 0) {
        if (game_data->mode == DEVMODE)
            game_data->mode = DEFAULT;
        else
            game_data->mode = DEVMODE;
        puts("DEV COMMAND : GO DEVMODE");
    }
    return SUCCESS;
}
