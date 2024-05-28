/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** json_find
*/

#include "my_rpg.h"

char *json_find_value(json_object_t *json_object, char const *key)
{
    if (key == NULL)
        return NULL;
    for (int i = 0; i < json_object->count; i += 1) {
        if (strcmp(json_object->keys[i], key) == 0) {
            return json_object->values[i];
        }
    }
    return NULL;
}
