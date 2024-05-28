/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** textures
*/

#include "my_rpg.h"

static texture_t *create_texture(char *key, char *texture_path)
{
    texture_t *texture = malloc(sizeof(texture_t));

    texture->key = strdup(key);
    texture->texture_path = strdup(texture_path);
    texture->texture = sfTexture_createFromFile(texture_path, NULL);
    return texture;
}

texture_t **generate_textures(json_object_t *json_data)
{
    texture_t **textures = NULL;
    json_object_t *json_textures =
        json_object_create(json_find_value(json_data, TEXTURES_DATA));
    char *tmp = NULL;

    textures = malloc(sizeof(texture_t *) * (json_textures->count + 1));
    textures[json_textures->count] = NULL;
    for (int i = 0; i < json_textures->count; i += 1) {
        tmp = strdup(json_textures->values[i]);
        json_convert_str(&tmp);
        textures[i] = create_texture(json_textures->keys[i], tmp);
        free(tmp);
    }
    json_object_destroy(json_textures);
    return textures;
}

static int destroy_texture(texture_t *texture)
{
    free(texture->key);
    free(texture->texture_path);
    sfTexture_destroy(texture->texture);
    free(texture);
    return SUCCESS;
}

int destroy_textures(texture_t **textures)
{
    if (textures == NULL)
        return SUCCESS;
    for (int i = 0; textures[i] != NULL; i += 1)
        destroy_texture(textures[i]);
    free(textures);
    return SUCCESS;
}
