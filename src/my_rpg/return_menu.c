/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** return_menu
*/

#include "my_rpg.h"

int return_menu(game_data_t *game_data, char const *str)
{
    menu_t *menu = NULL;

    if (game_data == NULL || game_data->menus == NULL || str != NULL)
        return ERR;
    menu = get_active_menu(game_data);
    if (strcmp(menu->key, "choose_save") == 0 ||
        strcmp(menu->key, "settings") == 0)
        show_only_this_menu(game_data, "starting_menu");
    if (strcmp(menu->key, "settings_audio") == 0 ||
        strcmp(menu->key, "settings_video") == 0) {
        show_only_this_menu(game_data, "settings");
        if (strcmp(menu->key, "settings_video") == 0)
            change_sprite_visibility(game_data, "video_settings");
        if (strcmp(menu->key, "settings_audio") == 0)
            change_sprite_visibility(game_data, "audio_settings");
        change_sprite_visibility(game_data, "settings_background");
    }
    return SUCCESS;
}
