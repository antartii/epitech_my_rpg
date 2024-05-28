/*
** EPITECH PROJECT, 2024
** dev
** File description:
** map
*/

#include "my_rpg.h"

static sfIntRect set_rect_from_scale(sfVector2i scale)
{
    sfIntRect rect = {0, 0, 0, 0};

    rect.height = scale.y;
    rect.width = scale.x;
    return rect;
}

sfIntRect get_map_rect(map_t *map, int i, int j, char **s)
{
    sfIntRect rect = set_rect_from_scale(map->scale);

    if (map->map[i][j] != 0) {
        if ((j == 0 || map->map[i][j - 1] == 0))
            rect.left = 0;
        if ((j != 0 && map->map[i][j - 1] != 0) &&
            (j != (int) strlen(s[i]) - 1 || map->map[i][j + 1] != 0))
            rect.left = map->scale.x;
        if ((j == (int) strlen(s[i]) - 1 || map->map[i][j + 1] == 0))
            rect.left = 2 * map->scale.x;
        if ((s[i + 1] == NULL || map->map[i + 1][j] == 0))
            rect.top = 2 * map->scale.y;
        if ((i == 0 || map->map[i - 1][j] == 0))
            rect.top = 0;
        if ((i != 0 && map->map[i - 1][j] != 0) &&
            (s[i + 1] != NULL && map->map[i + 1][j] != 0))
        rect.top = map->scale.y;
    }
    return rect;
}

static sfSprite *set_map_tile(int map_value, texture_t *texture,
    texture_t *empty_texture, sfIntRect rect)
{
    sfSprite *sprite = NULL;

    sprite = sfSprite_create();
    if (map_value == 0)
        sfSprite_setTexture(sprite, empty_texture->texture, sfTrue);
    else
        sfSprite_setTexture(sprite, texture->texture, sfFalse);
    sfSprite_setTextureRect(sprite, rect);
    return sprite;
}

static texture_t *set_map_texture(texture_t **textures,
    json_object_t *json_map, char const *name)
{
    char *tmp2 = strdup(json_find_value(json_map, name));
    texture_t *texture = NULL;

    json_convert_str(&tmp2);
    texture = textures[find_texture_index(textures, tmp2)];
    free(tmp2);
    return texture;
}

static char **set_splited_map(json_object_t *json_map)
{
    char *tmp = strdup(json_find_value(json_map, "file"));
    char *raw_map = NULL;
    char **splited_map = NULL;

    json_convert_str(&tmp);
    raw_map = get_file_content(tmp);
    splited_map = my_split_string(raw_map, "\n");
    free(raw_map);
    free(tmp);
    return splited_map;
}

static sfSprite ***init_map_tiles(char **splited_map)
{
    sfSprite ***tiles = NULL;

    tiles = malloc(sizeof(sfSprite **) *
        (ptr_array_len((void **) splited_map) + 1));
    tiles[ptr_array_len((void **) splited_map)] = NULL;
    return tiles;
}

static int generate_tiles(char **splited_map,
    map_t *map, texture_t *texture, texture_t *empty_texture)
{
    sfIntRect rect = {0, 0, 0, 0};

    for (int i = 0; splited_map[i] != NULL; i += 1) {
        map->tiles[i] = malloc(sizeof(sfSprite *) *
            (strlen(splited_map[i]) + 1));
        map->tiles[i][strlen(splited_map[i])] = NULL;
        for (int j = 0; j < (int) (strlen(splited_map[i])); j += 1) {
            rect = get_map_rect(map, i, j, splited_map);
            map->tiles[i][j] = set_map_tile(map->map[i][j], texture,
                empty_texture, rect);
            sfSprite_setPosition(map->tiles[i][j], (sfVector2f) {map->scale.x *
                j * map->window_scale.x, map->scale.y * i *
                map->window_scale.y});
            sfSprite_setScale(map->tiles[i][j], map->window_scale);
        }
    }
    return SUCCESS;
}

map_t *create_map(json_object_t *json_map, texture_t **textures)
{
    map_t *map = malloc(sizeof(map_t));
    char **splited_map = set_splited_map(json_map);
    texture_t *texture = set_map_texture(textures, json_map,
        "texture");
    texture_t *empty_texture = set_map_texture(textures, json_map,
        "empty_texture");

    set_map(map, splited_map, json_map);
    map->tiles = init_map_tiles(splited_map);
    generate_tiles(splited_map, map, texture, empty_texture);
    free_ptr_array((void **) splited_map);
    return map;
}

map_t **generate_maps(json_object_t *json_data, texture_t **textures)
{
    map_t **maps = NULL;
    json_object_t *json_maps = json_object_create(
        json_find_value(json_data, "maps"));
    json_object_t *json_map = NULL;

    maps = malloc(sizeof(map_t *) * (json_maps->count + 1));
    maps[json_maps->count] = NULL;
    for (int i = 0; i < json_maps->count; i += 1) {
        json_map = json_object_create(json_find_value(json_maps,
            json_maps->keys[i]));
        maps[i] = create_map(json_map, textures);
        json_object_destroy(json_map);
    }
    json_object_destroy(json_maps);
    return maps;
}

int destroy_maps(map_t **maps)
{
    if (maps == NULL)
        return SUCCESS;
    for (int i = 0; maps[i] != NULL; i += 1) {
        free_ptr_array((void **) maps[i]->map);
        free(maps[i]->line_width);
    }
    free(maps);
    return SUCCESS;
}
