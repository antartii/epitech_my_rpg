/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** set_starting_screen_actions
*/

#include "my_rpg.h"

int change_game_mode(game_data_t *game_data, char const *str)
{
    if (game_data == NULL || str == NULL)
        return SUCCESS;
    if (strcmp(str, "starting") == 0)
        game_data->gamemode = STARTING;
    if (strcmp(str, "exploration") == 0)
        game_data->gamemode = EXPLORATION;
    if (strcmp(str, "fighting") == 0)
        game_data->gamemode = FIGHTING;
    return SUCCESS;
}

static int set_starting_screen_start_actions(button_t **buttons)
{
    char *startbtn = "starting_screen_start";

    add_button_action(buttons, startbtn, show_only_this_menu,
        "choose_save");
    add_button_action(buttons, startbtn, change_display, "exploration");
    add_button_action(buttons, startbtn, show_only_this_menu, "exploration");
    add_button_action(buttons, startbtn, change_game_mode, "exploration");
    return SUCCESS;
}

static int set_starting_screen_exit_actions(button_t **buttons)
{
    char *back = "settings_background";
    char *vid = "video_settings";
    char *vol = "audio_settings";
    char *setv = "settings_video";
    char *seta = "settings_audio";

    add_button_action(buttons, "starting_screen_exit", exit_the_game, NULL);
    add_button_action(buttons, "audio_button", show_only_this_menu, seta);
    add_button_action(buttons, "audio_button", change_sprite_visibility, back);
    add_button_action(buttons, "audio_button", change_sprite_visibility, vol);
    add_button_action(buttons, "video_button", show_only_this_menu, setv);
    add_button_action(buttons, "video_button", change_sprite_visibility, vid);
    add_button_action(buttons, "video_button", change_sprite_visibility, back);
    add_button_action(buttons, "check_box", check_box_action, "check_box");
    return SUCCESS;
}

static int set_starting_screen_settings_actions(button_t **buttons)
{
    char *button_key = "starting_screen_other";

    add_button_action(buttons, button_key, show_only_this_menu,
        "settings");
    add_button_action(buttons, "change_music_left", decrease_volume,
        "lmao_you_re_dumb");
    add_button_action(buttons, "change_music_right", increase_volume,
        "lmao_you_re_dumb");
    return SUCCESS;
}

static int set_return_action(button_t **buttons)
{
    add_button_action(buttons, "return_button", return_menu, NULL);
    return SUCCESS;
}

int set_starting_screen_action(button_t **buttons)
{
    set_starting_screen_start_actions(buttons);
    set_starting_screen_exit_actions(buttons);
    set_starting_screen_settings_actions(buttons);
    set_return_action(buttons);
    return SUCCESS;
}
