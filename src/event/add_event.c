/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** add_event
*/

#include "my_rpg.h"

static int add_key_event_first(char const *str, keyevent_t ***events,
    key_action_t action, sfKeyCode keycode)
{
    (*events)[keycode]->actions = malloc(sizeof(action_t));
    (*events)[keycode]->actions_value = malloc(sizeof(char *) * 2);
    (*events)[keycode]->actions[0] = action;
    if (str == NULL)
        (*events)[keycode]->actions_value[0] = NULL;
    else
        (*events)[keycode]->actions_value[0] = strdup(str);
    (*events)[keycode]->actions_value[1] = NULL;
    return SUCCESS;
}

action_t *get_action_copy(int count, keyevent_t **events,
    sfKeyCode keycode, key_action_t action)
{
    key_action_t *actions = NULL;

    actions = malloc(sizeof(action_t) * (count + 1));
    for (int i = 0; i < count; i += 1)
        actions[i] = events[keycode]->actions[i];
    actions[count] = action;
    return 0;
}

int add_keyevent(keyevent_t **events, key_action_t action,
    sfKeyCode keycode, char const *str)
{
    key_action_t *actions = NULL;
    int count = events[keycode]->count;

    if (events[keycode]->actions == NULL)
        add_key_event_first(str, &events, action, keycode);
    else {
        events = realloc(events[keycode]->actions_value, count + 2);
        if (str == NULL)
            events[keycode]->actions_value[count] = NULL;
        else
            events[keycode]->actions_value[count] = strdup(str);
        events[keycode]->actions_value[count + 1] = NULL;
        free(events[keycode]->actions);
        events[keycode]->actions = actions;
    }
    events[keycode]->count += 1;
    return SUCCESS;
}
