/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** window
*/

#include "my_rpg.h"

window_t *generate_window(json_object_t *json_data)
{
    window_t *window = NULL;
    json_object_t *json_window =
        json_object_create(json_find_value(json_data, WINDOW_DATA));

    window = malloc(sizeof(window_t));
    window->title = strdup(json_find_value(json_window, WINDOW_TITLE));
    window->style = atoi(json_find_value(json_window, WINDOW_STYLE));
    window->vm =
        json_convert_videomode(json_find_value(json_window, WINDOW_VM));
    window->w =
        sfRenderWindow_create(window->vm, window->title, window->style, NULL);
    json_object_destroy(json_window);
    sfRenderWindow_setMouseCursorVisible(window->w, sfFalse);
    return window;
}

int destroy_window(window_t *window)
{
    free(window->title);
    sfRenderWindow_destroy(window->w);
    free(window);
    return SUCCESS;
}
