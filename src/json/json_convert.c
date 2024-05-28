/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** json_convert
*/

#include "my_rpg.h"

int json_convert_str(char **str_adress)
{
    char *tmp = get_substr(*str_adress, 1, strlen(*str_adress) - 2);

    free(*str_adress);
    *str_adress = tmp;
    return SUCCESS;
}

sfVector2f json_convert_vector2f(char const *value)
{
    sfVector2f vector;
    json_object_t *json_object = json_object_create(value);

    vector.x = (float) atoll(json_find_value(json_object, "x"));
    vector.y = (float) atoll(json_find_value(json_object, "y"));
    json_object_destroy(json_object);
    return vector;
}

sfIntRect json_convert_intrect(char const *value)
{
    sfIntRect intrect;
    json_object_t *json_object = json_object_create(value);

    intrect.top = (float) atoll(json_find_value(json_object, "top"));
    intrect.left = (float) atoll(json_find_value(json_object, "left"));
    intrect.height = (float) atoll(json_find_value(json_object, "height"));
    intrect.width = (float) atoll(json_find_value(json_object, "width"));
    json_object_destroy(json_object);
    return intrect;
}

sfVideoMode json_convert_videomode(char const *value)
{
    sfVideoMode vm = {0, 0, 0};
    json_object_t *json_object = NULL;

    if (value == NULL)
        return vm;
    json_object = json_object_create(value);
    vm.height = atoi(json_find_value(json_object, "height"));
    vm.width = atoi(json_find_value(json_object, "width"));
    vm.bitsPerPixel = atoi(json_find_value(json_object, "bitsPerPixel"));
    json_object_destroy(json_object);
    return vm;
}
