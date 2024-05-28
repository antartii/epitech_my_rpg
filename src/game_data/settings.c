/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** settings
*/

#include "my_rpg.h"

settings_t *set_settings(json_object_t *json_data)
{
    json_object_t *json_settings = NULL;
    settings_t *settings = NULL;

    if (json_data == NULL)
        return NULL;
    json_settings = json_object_create(
        json_find_value(json_data, "game_settings"));
    settings = malloc(sizeof(settings_t));
    settings->game_speed = atof(json_find_value(
        json_settings, "game_speed"));
    settings->clock = sfClock_create();
    settings->time = sfTime_Zero;
    settings->time_since_last_update = sfTime_Zero;
    settings->framerate = 10;
    json_object_destroy(json_settings);
    return settings;
}
