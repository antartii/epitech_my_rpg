/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** get_end_pos
*/

#include "my_rpg.h"

sfVector2f get_entity_movement(entity_t *entity, game_data_t *game_data)
{
    sfVector2f movement = {0, 0};

    if (entity->is_moving.x == TRUE)
        movement.x = entity->curr_spd * game_data->settings->game_speed;
    if (entity->is_moving.y == TRUE)
        movement.y = entity->curr_spd * game_data->settings->game_speed;
    if (entity->direction.x == EAST)
        movement.x *= -1;
    if (entity->direction.y == NORTH)
        movement.y *= -1;
    return movement;
}

sfVector2f get_end_pos(
    sfVector2f start_pos,
    sfIntRect bounds,
    sfVector2f scale)
{
    sfVector2f end_pos = {0, 0};

    end_pos.x = start_pos.x + (bounds.width * scale.x);
    end_pos.y = start_pos.y + (bounds.height * scale.y);
    return end_pos;
}

int is_hovering_object(
    sfVector2f start_pos,
    sfIntRect bounds,
    sfVector2f scale,
    sfVector2i mousepos)
{
    sfVector2f end_pos = get_end_pos(start_pos, bounds, scale);
    sfVector2i is_valid = {TRUE, TRUE};

    if (mousepos.x <= start_pos.x || mousepos.x >= end_pos.x)
        is_valid.x = FALSE;
    if (mousepos.y <= start_pos.y || mousepos.y >= end_pos.y)
        is_valid.y = FALSE;
    if (is_valid.x == TRUE && is_valid.y == TRUE)
        return TRUE;
    else
        return FALSE;
}

sfVector2f
convert_start_pos(char *str_pos_x, char *str_pos_y, sfRenderWindow *window)
{
    sfVector2f start_pos = {0, 0};
    sfVector2u window_size = sfRenderWindow_getSize(window);

    if (strcmp(str_pos_x, "\"center\"") == 0)
        start_pos.x = window_size.x / 2;
    if (strcmp(str_pos_x, "\"right\"") == 0)
        start_pos.x = window_size.x;
    if (strcmp(str_pos_y, "\"center\"") == 0)
        start_pos.y = window_size.y / 2;
    if (strcmp(str_pos_y, "\"bottom\"") == 0)
        start_pos.y = window_size.y;
    return start_pos;
}

sfVector2f set_pos(sfVector2f start_pos, sfVector2f offset, sfVector2f scale)
{
    sfVector2f new_pos = start_pos;

    new_pos.x += (offset.x * scale.x);
    new_pos.y += (offset.y * scale.y);
    return new_pos;
}
