/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** json_object
*/

#include "my_rpg.h"

json_object_t *json_object_create(char const *json)
{
    json_object_t *json_object = malloc(sizeof(json_object_t));
    char *raw_json = json_convert_to_line(json);

    json_object->count = json_count_values(raw_json);
    json_object->keys = json_get_strkeys(raw_json);
    json_object->values = json_get_strvalues(raw_json);
    json_object->types =
        malloc(sizeof(json_type_t) * (json_object->count + 1));
    for (int i = 0; i < json_object->count; i += 1)
        json_object->types[i] = json_get_value_type(json_object->values[i]);
    free(raw_json);
    return json_object;
}

int json_object_destroy(json_object_t *json_object)
{
    for (int i = 0; i < json_object->count; i += 1) {
        if (json_object->keys != NULL)
            free(json_object->keys[i]);
        free(json_object->values[i]);
    }
    free(json_object->values);
    free(json_object->keys);
    free(json_object->types);
    return 0;
}
