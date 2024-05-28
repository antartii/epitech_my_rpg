/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** keyevents
*/

#include "my_rpg.h"

keyevent_t **init_key_events(void)
{
    keyevent_t **key_events = malloc(sizeof(keyevent_t *) * (sfKeyCount + 1));

    key_events[sfKeyCount] = NULL;
    for (int i = 0; i < sfKeyCount; i += 1) {
        key_events[i] = malloc(sizeof(keyevent_t));
        key_events[i]->count = 0;
        key_events[i]->actions = NULL;
    }
    return key_events;
}

int destroy_key_events(keyevent_t **key_events)
{
    if (key_events == NULL)
        return SUCCESS;
    for (int i = 0; i < sfKeyCount; i += 1) {
        if (key_events[i] != NULL) {
            free(key_events[i]->actions);
            free(key_events[i]);
        }
    }
    free(key_events);
    return SUCCESS;
}
