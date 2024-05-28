/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** find_struct
*/

#include "my_rpg.h"

int find_texture_index(texture_t **textures, char const *key)
{
    if (textures == NULL || key == NULL)
        return 0;
    for (int i = 0; textures[i]->key != NULL; i += 1) {
        if (strcmp(textures[i]->key, key) == 0)
            return i;
    }
    return 0;
}

sprite_t *find_sprite(sprite_t **sprites, char const *key)
{
    if (sprites == NULL)
        return NULL;
    for (int i = 0; sprites[i]->key != NULL; i += 1) {
        if (strcmp(sprites[i]->key, key) == 0)
            return sprites[i];
    }
    return NULL;
}

button_t *find_button(button_t **buttons, char const *key)
{
    for (int i = 0; buttons[i] != NULL; i += 1) {
        if (strcmp(buttons[i]->key, key) == 0)
            return buttons[i];
    }
    return NULL;
}

int get_display_index(display_t **displays, char const *key)
{
    if (displays == NULL || key == NULL)
        return 0;
    for (int i = 0; displays[i] != NULL; i += 1) {
        if (strcmp(displays[i]->key, key) == 0)
            return i;
    }
    return 0;
}

menu_t *get_menu(menu_t **menus, char const *key)
{
    if (menus == NULL || key == NULL)
        return NULL;
    for (int i = 0; menus[i] != NULL; i += 1) {
        if (strcmp(menus[i]->key, key) == 0)
            return menus[i];
    }
    return NULL;
}
