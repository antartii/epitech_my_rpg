/*
** EPITECH PROJECT, 2024
** dev
** File description:
** grid
*/

#include "my_rpg.h"

sfVector2i update_grid_pos(entity_t *entity, map_t *active_map)
{
    sfVector2i new_gridpos = {0, 0};
    sfVector2f pos = {0, 0};

    if (entity == NULL || active_map == NULL)
        return new_gridpos;
    pos = sfSprite_getPosition(entity->sprite->object);
    new_gridpos.x = count_multiple((int) pos.x, (int)
        (active_map->scale.x * active_map->window_scale.x));
    new_gridpos.y = count_multiple((int) pos.y,
        (active_map->scale.y * active_map->window_scale.y));
    entity->grid_pos = new_gridpos;
    return new_gridpos;
}

static sfIntRect set_cell_bounds(entity_t *entity, map_t *active_map)
{
    sfIntRect cell_bounds = {0, 0, 0, 0};

    cell_bounds.left = (entity->grid_pos.x + active_map->grid_offset.x) *
        active_map->scale.x * active_map->window_scale.x;
    cell_bounds.top = (entity->grid_pos.y + active_map->grid_offset.y) *
        active_map->scale.y * active_map->window_scale.y;
    cell_bounds.width = (entity->grid_pos.x + 1 + active_map->grid_offset.x) *
        active_map->scale.x * active_map->window_scale.x;
    cell_bounds.height = (entity->grid_pos.y + 1 + active_map->grid_offset.y) *
        active_map->scale.y * active_map->window_scale.y;
    return cell_bounds;
}

sfIntRect
is_entity_grid_bounded(entity_t *entity, map_t *active_map, int offset)
{
    sfIntRect is_bounded = {0, 0, 0, 0};
    sfVector2f pos = {0, 0};
    sfFloatRect bounds = {0, 0, 0, 0};
    sfIntRect cell_bounds = {0, 0, 0, 0};

    if (entity == NULL || active_map == NULL)
        return is_bounded;
    pos = sfSprite_getPosition(entity->sprite->object);
    bounds = sfSprite_getGlobalBounds(entity->sprite->object);
    cell_bounds = set_cell_bounds(entity, active_map);
    if (pos.y <= cell_bounds.top + offset)
        is_bounded.top = TRUE;
    if (pos.x <= cell_bounds.left + offset)
        is_bounded.left = TRUE;
    if (pos.y + bounds.height >= cell_bounds.top - offset)
        is_bounded.height = TRUE;
    if (pos.x + bounds.width >= cell_bounds.left - offset)
        is_bounded.width = TRUE;
    return is_bounded;
}
