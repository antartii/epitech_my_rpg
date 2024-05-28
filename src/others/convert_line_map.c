/*
** EPITECH PROJECT, 2024
** dev
** File description:
** convert_line_map
*/

#include "my_rpg.h"

int *convert_line_map(char const *line_map)
{
    int *line = NULL;

    if (line_map == NULL)
        return NULL;
    line = malloc(sizeof(int) * strlen(line_map));
    for (int i = 0; i < (int) strlen(line_map); i += 1)
        line[i] = line_map[i] - '0';
    return line;
}

int **set_map(map_t *map, char **splited_map, json_object_t *json_map)
{
    sfVector2f scale = {0, 0};

    map->map = malloc(sizeof(int *) *
        (ptr_array_len((void **) splited_map) + 1));
    map->map[ptr_array_len((void **) splited_map)] = NULL;
    map->line_width = malloc(sizeof(int) *
        (ptr_array_len((void **) splited_map) + 1));
    for (int i = 0; splited_map[i] != NULL; i += 1) {
        map->map[i] = convert_line_map(splited_map[i]);
        map->line_width[i] = strlen(splited_map[i]);
    }
    map->window_scale = json_convert_vector2f(
        json_find_value(json_map, "window_scale"));
    scale = json_convert_vector2f(json_find_value(json_map, "scale"));
    map->scale.x = (int) scale.x;
    map->scale.y = (int) scale.y;
    map->height = ptr_array_len((void **) splited_map);
    map->grid_offset = (sfVector2i) {0, 0};
    return SUCCESS;
}
