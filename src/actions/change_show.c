/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** change_visibility
*/

#include "my_rpg.h"

int change_menu_visibility(game_data_t *game_data, char const *menu_name)
{
    menu_t *menu = NULL;

    if (game_data == NULL || menu_name == NULL)
        return ERR;
    menu = get_menu(game_data->menus, menu_name);
    if (menu == NULL)
        return ERR;
    menu->visibility = !menu->visibility;
    return SUCCESS;
}

int change_sprite_visibility(game_data_t *game_data, char const *sprite_name)
{
    sprite_t *sprite = NULL;

    if (game_data == NULL || sprite_name == NULL)
        return ERR;
    sprite = find_sprite(game_data->sprites, sprite_name);
    sprite->visibility = !(sprite->visibility);
    return SUCCESS;
}

int change_display(game_data_t *game_data, char const *display_name)
{
    if (game_data == NULL || display_name == NULL)
        return ERR;
    game_data->display_index =
        get_display_index(game_data->displays, display_name);
    return SUCCESS;
}

int change_sprite_frame(game_data_t *game_data, char const *sprite_name)
{
    sfIntRect new_rect = {0, 0, 0, 0};
    sprite_t *sprite = find_sprite(game_data->sprites, sprite_name);

    new_rect.height = sprite->rect.height;
    new_rect.width = sprite->rect.width;
    sprite->frame_state += 1;
    if (sprite->frame_state >= sprite->max_frame) {
        new_rect.left = 0;
        sprite->frame_state = 0;
    } else
        new_rect.left = (sprite->rect.width * sprite->frame_state);
    new_rect.top = sprite->rect.top;
    sprite->rect = new_rect;
    sfSprite_setTextureRect(sprite->object, new_rect);
    return SUCCESS;
}

int change_sprite_state(sprite_t *sprite, int frame_state)
{
    if (sprite == NULL || frame_state < 0)
        return ERR;
    sprite->rect.top = (sprite->rect.height * frame_state);
    sfSprite_setTextureRect(sprite->object, sprite->rect);
    return SUCCESS;
}
