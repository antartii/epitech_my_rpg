/*
** EPITECH PROJECT, 2024
** dev
** File description:
** devmode_draw
*/

#include "my_rpg.h"

sfColor get_devmode_color(map_t *map, int i, int j)
{
    sfColor color = sfGreen;

    if (map->map[i + map->grid_offset.y][j + map->grid_offset.x] <= 0)
        color = sfRed;
        else
    color = sfGreen;
    return color;
}

int set_devmode_map(map_t *map, sfRenderWindow *window, int i, int j)
{
    sfRectangleShape *map_tile = NULL;
    sfColor color;
    sfVector2f pos = {0, 0};
    sfIntRect bounds = {0, 0, 0, 0};

    if (i >= 0 && j >= 0 && i < map->height && j < map->line_width[i]) {
        color = get_devmode_color(map, i, j);
        pos.x = j * (map->scale.x * map->window_scale.x);
        pos.y = i * (map->scale.y * map->window_scale.y);
        bounds.width = (int) map->scale.x;
        bounds.height = (int) map->scale.y;
        map_tile = set_rectangle(bounds, pos, color, map->window_scale);
        sfRenderWindow_drawRectangleShape(window, map_tile, NULL);
        sfRectangleShape_destroy(map_tile);
    }
    return SUCCESS;
}
