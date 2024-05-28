/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** music_actions
*/

#include "my_rpg.h"

int play_music(game_data_t *game_data, char const *name)
{
    music_t *music = NULL;

    if (game_data == NULL || name == NULL)
        return ERR;
    music = get_music(game_data->musics, name);
    if (music == NULL)
        return ERR;
    sfMusic_play(music->audio);
    return SUCCESS;
}
