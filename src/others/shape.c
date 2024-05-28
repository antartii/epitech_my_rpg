/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** shape
*/

#include "my_rpg.h"

sfRectangleShape *set_rectangle(
    sfIntRect bounds,
    sfVector2f pos,
    sfColor color,
    sfVector2f scale)
{
    sfRectangleShape *new_rect = sfRectangleShape_create();
    sfVector2f size = {bounds.width * scale.x, bounds.height * scale.y};

    sfRectangleShape_setSize(new_rect, size);
    sfRectangleShape_setPosition(new_rect, pos);
    sfRectangleShape_setFillColor(new_rect, (sfColor) {0, 0, 0, 0});
    sfRectangleShape_setOutlineColor(new_rect, color);
    sfRectangleShape_setOutlineThickness(new_rect, 3);
    return new_rect;
}
