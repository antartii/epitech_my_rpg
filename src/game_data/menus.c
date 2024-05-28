/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** menus
*/

#include "my_rpg.h"

menu_t
*create_menu(json_object_t *json_menus, char const *key, button_t **buttons)
{
    menu_t *menu = NULL;
    char **buttons_array = json_array_create(json_find_value(json_menus, key));
    char *tmp = NULL;
    int buttons_len = ptr_array_len((void **) buttons_array);

    menu = malloc(sizeof(menu_t));
    menu->key = strdup(key);
    menu->buttons = malloc(sizeof(button_t *) * (buttons_len + 1));
    menu->buttons[buttons_len] = NULL;
    menu->visibility = HIDDEN;
    for (int i = 0; i < buttons_len; i += 1) {
        tmp = strdup(buttons_array[i]);
        json_convert_str(&tmp);
        menu->buttons[i] = find_button(buttons, tmp);
        free(tmp);
        free(buttons_array[i]);
    }
    free(buttons_array);
    return menu;
}

menu_t **generate_menus(json_object_t *json_data, button_t **buttons)
{
    menu_t **menus = NULL;
    json_object_t *json_menus =
        json_object_create(json_find_value(json_data, "menu"));

    menus = malloc(sizeof(menu_t *) * (json_menus->count + 1));
    menus[json_menus->count] = NULL;
    for (int i = 0; i < json_menus->count; i += 1)
        menus[i] = create_menu(json_menus, json_menus->keys[i], buttons);
    json_object_destroy(json_menus);
    return menus;
}

static int destroy_menu(menu_t *menu)
{
    if (menu == NULL)
        return SUCCESS;
    free(menu->buttons);
    free(menu->key);
    free(menu);
    return SUCCESS;
}

int destroy_menus(menu_t **menus)
{
    if (menus == NULL)
        return SUCCESS;
    for (int i = 0; menus[i] != NULL; i += 1)
        destroy_menu(menus[i]);
    free(menus);
    return SUCCESS;
}
