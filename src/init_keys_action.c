/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** init_keys_action
*/

#include "my_rpg.h"

int increase_speed(game_data_t *game_data, char const *state, char const *str)
{
    if (game_data == NULL || (str == NULL && str != NULL) ||
    (state == NULL && state != NULL))
        return ERR;
    game_data->settings->game_speed += 0.1;
    return SUCCESS;
}

int decrease_speed(game_data_t *game_data, char const *state, char const *str)
{
    if (game_data == NULL || (str == NULL && str != NULL) ||
    (state == NULL && state != NULL))
        return ERR;
    if (game_data->settings->game_speed < 0.1) {
        game_data->settings->game_speed = 0.1;
        return SUCCESS;
    } else
        game_data->settings->game_speed -= 0.1;
    return SUCCESS;
}

int show_bag(game_data_t *game_data, char const *state, char const *str)
{
    if (str == NULL && str != NULL && state == NULL)
        return ERR;
    change_sprite_visibility(game_data, "bag_background");
    return SUCCESS;
}

int launch_fight(game_data_t *game_data, char const *state, char const *str)
{
    if (str == NULL && str != NULL)
        return ERR;
    if (game_data->gamemode != EXPLORATION)
        return SUCCESS;
    if (strcmp("pressed", state) == 0) {
        change_display(game_data, "fighting");
        show_only_this_menu(game_data, "fighting");
        change_game_mode(game_data, "fighting");
    }
    return SUCCESS;
}

static int launch_resume(game_data_t *game_data,
    char const *state, char const *str)
{
    if (str == NULL && str != NULL)
        return ERR;
    if (strcmp("pressed", state) == 0) {
        change_display(game_data, "starting");
        show_only_this_menu(game_data, "starting_menu");
        change_game_mode(game_data, "starting");
    }
    return SUCCESS;
}

int init_keys_action(keyevent_t **key_events)
{
    add_keyevent(key_events, devcommand_fullscreen, sfKeyA, NULL);
    add_keyevent(key_events, devcommand_exit, sfKeyQ, NULL);
    add_keyevent(key_events, devcommand_godevmode, sfKeyLControl, NULL);
    add_keyevent(key_events, devcommand_godevmode, sfKeyRControl, NULL);
    add_keyevent(key_events, devcommand_godevmode, sfKeyD, NULL);
    add_keyevent(key_events, devcommand_godevmode, sfKeyE, NULL);
    add_keyevent(key_events, devcommand_godevmode, sfKeyV, NULL);
    add_keyevent(key_events, exploration_west, sfKeyRight, NULL);
    add_keyevent(key_events, exploration_north, sfKeyUp, NULL);
    add_keyevent(key_events, exploration_south, sfKeyDown, NULL);
    add_keyevent(key_events, exploration_east, sfKeyLeft, NULL);
    add_keyevent(key_events, launch_fight, sfKeyF, "fig");
    add_keyevent(key_events, decrease_speed, sfKeyF9, "lul");
    add_keyevent(key_events, use_potion, sfKeyP, "5");
    add_keyevent(key_events, use_potion, sfKeyO, "10");
    add_keyevent(key_events, use_potion, sfKeyT, "20");
    add_keyevent(key_events, launch_resume, sfKeyEscape, "explo");
    return SUCCESS;
}
