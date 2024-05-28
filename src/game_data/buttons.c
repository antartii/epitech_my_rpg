/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** buttons
*/

#include "my_rpg.h"

static int set_button_pos(
    button_t *button,
    json_object_t *json_button,
    sfRenderWindow *window)
{
    json_object_t *json_start_pos =
        json_object_create(json_find_value(json_button, "start_pos"));
    char *start_pos_x = json_find_value(json_start_pos, "x");
    char *start_pos_y = json_find_value(json_start_pos, "y");
    sfVector2f start_pos = {0, 0};
    sfVector2f offset = {0, 0};
    sfVector2f scale = {0, 0};

    start_pos = convert_start_pos(start_pos_x, start_pos_y, window);
    offset = json_convert_vector2f(json_find_value(json_button, "pos"));
    scale = json_convert_vector2f(json_find_value(json_button, "scale"));
    button->pos = set_pos(start_pos, offset, scale);
    json_object_destroy(json_start_pos);
    return SUCCESS;
}

static button_t
*create_button(char const *key, json_object_t *json_object)
{
    sfVector2f scale = json_convert_vector2f(
        json_find_value(json_object, "scale"));
    int state = atoi(json_find_value(json_object, "base state"));
    sfIntRect bounds = json_convert_intrect(
        json_find_value(json_object, "bounds"));
    button_t *button = malloc(sizeof(button_t));

    button->key = strdup(key);
    button->scale = scale;
    button->bounds = bounds;
    button->state = state;
    button->actions = NULL;
    button->actions_value = NULL;
    button->action_count = 0;
    return button;
}

button_t **generate_buttons(json_object_t *data, game_data_t *game_data)
{
    button_t **buttons = NULL;
    json_object_t *json = json_object_create(json_find_value(data, "buttons"));
    json_object_t *json_button = NULL;
    char *tmp_sprite = NULL;

    buttons = malloc(sizeof(button_t *) * (json->count + 1));
    buttons[json->count] = NULL;
    for (int i = 0; i < json->count; i += 1) {
        json_button = json_object_create(json_find_value(json, json->keys[i]));
        buttons[i] = create_button(json->keys[i], json_button);
        tmp_sprite = strdup(json_find_value(json_button, "sprite"));
        json_convert_str(&tmp_sprite);
        buttons[i]->sprite = find_sprite(game_data->sprites, tmp_sprite);
        free(tmp_sprite);
        set_button_pos(buttons[i], json_button, game_data->window->w);
        json_object_destroy(json_button);
    }
    json_object_destroy(json);
    return buttons;
}

static int destroy_button(button_t *button)
{
    if (button == NULL)
        return SUCCESS;
    if (button->actions != NULL)
        free(button->actions);
    if (button->actions_value != NULL) {
        for (int i = 0; i < button->action_count; i += 1)
            free(button->actions_value[i]);
        free(button->actions_value);
    }
    free(button->key);
    free(button);
    return SUCCESS;
}

int destroy_buttons(button_t **buttons)
{
    if (buttons == NULL)
        return SUCCESS;
    for (int i = 0; buttons[i] != NULL; i += 1)
        destroy_button(buttons[i]);
    free(buttons);
    return SUCCESS;
}
