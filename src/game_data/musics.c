/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** musics
*/

#include "my_rpg.h"

music_t *create_music(char const *value, char const *key)
{
    music_t *music = malloc(sizeof(music_t));
    char *audio = strdup(value);

    json_convert_str(&audio);
    music->key = strdup(key);
    music->audio = sfMusic_createFromFile(audio);
    return music;
}

music_t **generate_musics(json_object_t *json_data)
{
    music_t **musiques = NULL;
    json_object_t *json_musics = NULL;

    if (json_data == NULL)
        return NULL;
    json_musics = json_object_create(json_find_value(json_data, "audio"));
    musiques = malloc(sizeof(music_t *) * (json_musics->count + 1));
    musiques[json_musics->count] = NULL;
    for (int i = 0; i < json_musics->count; i += 1)
        musiques[i] = create_music(json_musics->values[i],
            json_musics->keys[i]);
    json_object_destroy(json_musics);
    return musiques;
}

int destroy_musics(music_t **musics)
{
    if (musics == NULL)
        return SUCCESS;
    for (int i = 0; musics[i] != NULL; i += 1) {
        free(musics[i]->key);
        sfMusic_destroy(musics[i]->audio);
    }
    free(musics);
    return SUCCESS;
}

music_t *get_music(music_t **musics, char const *name)
{
    if (name == NULL || musics == NULL)
        return NULL;
    for (int i = 0; musics[i] != NULL; i += 1) {
        if (strcmp(musics[i]->key, name) == 0)
            return musics[i];
    }
    return NULL;
}
