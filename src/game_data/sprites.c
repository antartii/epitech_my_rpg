/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** sprites
*/

#include "my_rpg.h"

static int set_sprite_pos(
    sprite_t *sprite,
    json_object_t *json_sprite,
    sfRenderWindow *window)
{
    json_object_t *json_start_pos =
        json_object_create(json_find_value(json_sprite, "start_pos"));
    char *start_pos_x = json_find_value(json_start_pos, "x");
    char *start_pos_y = json_find_value(json_start_pos, "y");
    sfVector2f start_pos = {0, 0};
    sfVector2f offset = {0, 0};
    sfVector2f scale = {0, 0};

    start_pos = convert_start_pos(start_pos_x, start_pos_y, window);
    offset = json_convert_vector2f(json_find_value(json_sprite, "offset"));
    scale = json_convert_vector2f(json_find_value(json_sprite, "scale"));
    sprite->scale = scale;
    sfSprite_setPosition(sprite->object, set_pos(start_pos, offset, scale));
    json_object_destroy(json_start_pos);
    return SUCCESS;
}

static sprite_t *create_sprite(
    char const *key,
    texture_t *texture,
    sfIntRect rect,
    sfVector2f scale)
{
    sprite_t *sprite = malloc(sizeof(sprite_t));

    sprite->key = strdup(key);
    sprite->texture = texture->texture;
    sprite->frame_state = DEFAULT;
    sprite->object = sfSprite_create();
    sfSprite_setTexture(sprite->object, texture->texture, sfFalse);
    sfSprite_setTextureRect(sprite->object, rect);
    sfSprite_setScale(sprite->object, scale);
    return sprite;
}

int json_convert_boolean(char const *value)
{
    if (value == NULL)
        return ERR;
    if (strcmp(value, "true") == 0)
        return TRUE;
    if (strcmp(value, "false") == 0)
        return FALSE;
    return ERR;
}

int set_sprite(sprite_t *sprite, json_object_t *json_sprite)
{
    sfIntRect rect = {0, 0, 0, 0};

    if (sprite == NULL || json_sprite == NULL)
        return ERR;
    rect = json_convert_intrect(json_find_value(json_sprite, "texture_rect"));
    sprite->fps = atoi(json_find_value(json_sprite, "fps"));
    sprite->rect = rect;
    sprite->max_frame = atoi(json_find_value(json_sprite, "max_frame"));
    sprite->visibility = json_convert_boolean(
        json_find_value(json_sprite, "visibility"));
    return SUCCESS;
}

static sprite_t *create_sprite_from_json(
    texture_t **textures,
    json_object_t *json_sprites,
    char const *key)
{
    json_object_t *json_sprite = NULL;
    sfVector2f scale = {0, 0};
    texture_t *texture = NULL;
    sfIntRect rect = {0, 0, 0, 0};
    sprite_t *sprite = NULL;
    char *tmp = NULL;

    json_sprite = json_object_create(json_find_value(json_sprites, key));
    scale = json_convert_vector2f(json_find_value(json_sprite, "scale"));
    rect = json_convert_intrect(json_find_value(json_sprite, "texture_rect"));
    tmp = strdup(json_find_value(json_sprite, "texture"));
    json_convert_str(&tmp);
    texture = textures[find_texture_index(textures, tmp)];
    sprite = create_sprite(key, texture, rect, scale);
    set_sprite(sprite, json_sprite);
    json_object_destroy(json_sprite);
    free(tmp);
    return sprite;
}

sprite_t **generate_sprites(
    json_object_t *json_data,
    texture_t **textures,
    sfRenderWindow *window)
{
    sprite_t **sprites = NULL;
    json_object_t *json_sprites =
        json_object_create(json_find_value(json_data, SPRITES_DATA));
    json_object_t *json_sprite = NULL;

    sprites = malloc(sizeof(sprite_t *) * (json_sprites->count + 1));
    sprites[json_sprites->count] = NULL;
    for (int i = 0; i < json_sprites->count; i += 1) {
        json_sprite = json_object_create(json_find_value(
                json_sprites, json_sprites->keys[i]));
        sprites[i] = create_sprite_from_json(
                textures, json_sprites, json_sprites->keys[i]);
        set_sprite_pos(sprites[i], json_sprite, window);
        json_object_destroy(json_sprite);
    }
    json_object_destroy(json_sprites);
    return sprites;
}

static int destroy_sprite(sprite_t *sprite)
{
    free(sprite->key);
    sfSprite_destroy(sprite->object);
    free(sprite);
    return SUCCESS;
}

int destroy_sprites(sprite_t **sprites)
{
    if (sprites == NULL)
        return SUCCESS;
    for (int i = 0; sprites[i] != NULL; i += 1)
        destroy_sprite(sprites[i]);
    free(sprites);
    return SUCCESS;
}
