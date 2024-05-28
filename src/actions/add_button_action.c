/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** add_button_action
*/

#include "my_rpg.h"

int no_action(game_data_t *game_data, char const *str)
{
    if (game_data == NULL || str == NULL)
        return ERR;
    puts("this button has no actions set !");
    return SUCCESS;
}

int debug_action(game_data_t *game_data, char const *str)
{
    if (game_data == NULL || str == NULL)
        return ERR;
    puts("this is a debug button : ");
    puts(str);
    return SUCCESS;
}

static int
append_button_action(button_t *button, action_t action, char const *str)
{
    action_t *actions = NULL;
    char **action_value = NULL;

    actions = malloc(sizeof(action_t) * (button->action_count + 1));
    action_value = malloc(sizeof(char *) * (button->action_count + 1));
    for (int i = 0; i < button->action_count; i += 1) {
        actions[i] = button->actions[i];
        if (str == NULL)
            action_value[i] = NULL;
        else
            action_value[i] = strdup(button->actions_value[i]);
    }
    actions[button->action_count] = action;
    action_value[button->action_count] = strdup(str);
    free(button->actions);
    free(button->actions_value);
    button->actions = actions;
    button->actions_value = action_value;
    return SUCCESS;
}

int add_button_action(
    button_t **buttons,
    char const *key,
    action_t action,
    char const *str)
{
    button_t *button = find_button(buttons, key);

    if (button == NULL)
        return ERR;
    if (button->actions == NULL) {
        button->actions = malloc(sizeof(action_t));
        button->actions_value = malloc(sizeof(char *));
        button->actions[0] = action;
        if (str == NULL)
            button->actions_value[0] = NULL;
        else
            button->actions_value[0] = strdup(str);
    } else
        append_button_action(button, action, str);
    button->action_count += 1;
    return SUCCESS;
}
