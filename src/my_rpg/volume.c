/*
** EPITECH PROJECT, 2024
** dev
** File description:
** volume
*/

#include "my_rpg.h"

int decrease_volume(
    game_data_t *game_data,
    char const *music_name)
{
    music_t *music = NULL;
    float curr_volume = 0;

    if (game_data == NULL || music_name == NULL)
        return ERR;
    music = get_music(game_data->musics, music_name);
    curr_volume = sfMusic_getVolume(music->audio);
    if (curr_volume - 10 <= 0)
        sfMusic_pause(music->audio);
    else
        sfMusic_setVolume(music->audio, curr_volume - 10);
    return SUCCESS;
}

int increase_volume(
    game_data_t *game_data,
    char const *music_name)
{
    music_t *music = NULL;
    float curr_volume = 0;

    if (game_data == NULL || music_name == NULL)
        return ERR;
    music = get_music(game_data->musics, music_name);
    curr_volume = sfMusic_getVolume(music->audio);
    if (sfMusic_getStatus(music->audio) == sfPaused)
        sfMusic_play(music->audio);
    else
        sfMusic_setVolume(music->audio, curr_volume + 10);
    return SUCCESS;
}
