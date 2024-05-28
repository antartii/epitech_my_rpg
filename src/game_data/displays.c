/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** displays
*/

#include "my_rpg.h"

static display_t *create_display(
    char const *key,
    json_object_t *json_displays,
    sprite_t **sprites)
{
    display_t *display = NULL;
    char **display_array = NULL;
    int count = 0;
    char *tmp = NULL;

    display = malloc(sizeof(display_t));
    display->key = strdup(key);
    display_array = json_array_create(json_find_value(json_displays, key));
    count = ptr_array_len((void **) display_array);
    display->sprites = malloc(sizeof(sprite_t *) * (count + 1));
    display->sprites[count] = NULL;
    for (int i = 0; i < count; i += 1) {
        tmp = strdup(display_array[i]);
        json_convert_str(&tmp);
        display->sprites[i] = find_sprite(sprites, tmp);
        free(tmp);
    }
    free_ptr_array((void **) display_array);
    return display;
}

display_t **generate_displays(json_object_t *json_data, sprite_t **sprites)
{
    display_t **displays = NULL;
    json_object_t *json_displays =
        json_object_create(json_find_value(json_data, "displays"));
    char *key = NULL;

    displays = malloc(sizeof(display_t *) * (json_displays->count + 1));
    displays[json_displays->count] = NULL;
    for (int i = 0; i < json_displays->count; i += 1) {
        key = json_displays->keys[i];
        displays[i] = create_display(key, json_displays, sprites);
    }
    json_object_destroy(json_displays);
    return displays;
}

static int destroy_display(display_t *display)
{
    if (display == NULL)
        return SUCCESS;
    free(display->key);
    free(display);
    return SUCCESS;
}

int destroy_displays(display_t **displays)
{
    if (displays == NULL)
        return SUCCESS;
    for (int i = 0; displays[i] != NULL; i += 1)
        destroy_display(displays[i]);
    free(displays);
    return SUCCESS;
}
