/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** fullscreen
*/

#include "my_rpg.h"

int toggle_fullscreen(game_data_t *game_data)
{
    sfRenderWindow *new_window = NULL;

    if (game_data->is_fullscreen == FALSE) {
        game_data->is_fullscreen = TRUE;
        new_window = sfRenderWindow_create(game_data->window->vm,
            game_data->window->title, sfFullscreen, NULL);
    } else {
        game_data->is_fullscreen = FALSE;
        new_window = sfRenderWindow_create(game_data->window->vm,
            game_data->window->title, sfDefaultStyle, NULL);
    }
    sfRenderWindow_close(game_data->window->w);
    sfRenderWindow_destroy(game_data->window->w);
    game_data->window->w = new_window;
    sfRenderWindow_setMouseCursorVisible(game_data->window->w, sfFalse);
    return SUCCESS;
}
