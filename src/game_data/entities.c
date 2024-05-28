/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** entities
*/

#include "my_rpg.h"

entity_t *get_entity(entity_t **entities, char const *name)
{
    if (name == NULL || entities == NULL)
        return NULL;
    for (int i = 0; entities[i] != NULL; i += 1) {
        if (strcmp(entities[i]->name, name) == 0)
            return entities[i];
    }
    return NULL;
}

entity_t *init_entity(char const *name, sprite_t *sprite)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->name = strdup(name);
    entity->xp = 0;
    entity->xp_to_next_level = 1000;
    entity->lvl = 1;
    entity->status = NULL;
    entity->sprite = sprite;
    entity->is_moving.x = FALSE;
    entity->is_moving.y = FALSE;
    entity->grid_pos = (sfVector2i) {0, 0};
    return entity;
}

static int set_entity(entity_t *entity, json_object_t *json_entity)
{
    if (entity == NULL || json_entity == NULL)
        return ERR;
    entity->base_atk = atoi(json_find_value(json_entity, "atk"));
    entity->base_def = atoi(json_find_value(json_entity, "def"));
    entity->base_hp = atoi(json_find_value(json_entity, "hp"));
    entity->base_luck = atoi(json_find_value(json_entity, "luck"));
    entity->base_spd = atoi(json_find_value(json_entity, "speed"));
    entity->curr_atk = entity->base_atk;
    entity->curr_def = entity->base_def;
    entity->curr_hp = entity->base_hp;
    entity->curr_luck = entity->base_luck;
    entity->curr_spd = entity->base_spd;
    return SUCCESS;
}

entity_t *create_entity(json_object_t *json_entities, char const *key,
    sprite_t **sprites)
{
    entity_t *entity = NULL;
    json_object_t *json_entity = json_object_create(
        json_find_value(json_entities, key));
    char *tmp = strdup(json_find_value(json_entity, "sprite"));
    sprite_t *sprite = NULL;

    json_convert_str(&tmp);
    sprite = find_sprite(sprites, tmp);
    entity = init_entity(key, sprite);
    set_entity(entity, json_entity);
    return entity;
}

entity_t **generate_entities(json_object_t *json_data, game_data_t *game_data)
{
    entity_t **entities = NULL;
    json_object_t *json_entities = json_object_create(
        json_find_value(json_data, "entities"));
    char *key = NULL;
    sprite_t **sprites = game_data->sprites;

    entities = malloc(sizeof(entity_t *) * (json_entities->count + 1));
    entities[json_entities->count] = NULL;
    for (int i = 0; i < json_entities->count; i += 1) {
        key = json_entities->keys[i];
        entities[i] = create_entity(json_entities, key, sprites);
    }
    return entities;
}

int destroy_entities(entity_t **entities)
{
    if (entities == NULL)
        return SUCCESS;
    for (int i = 0; entities[i] != NULL; i += 1) {
        if (entities[i]->status)
            free(entities[i]->status);
        free(entities[i]->name);
        free(entities[i]);
    }
    free(entities);
    return SUCCESS;
}
