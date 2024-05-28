/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** process_events
*/

#include "my_rpg.h"

int event_close(game_data_t *game_data, sfEvent event)
{
    if (event.type == sfEvtClosed)
        game_data->is_running = FALSE;
    return SUCCESS;
}

static int
check_button_state(button_t *button, sfVector2i mousepos, sfEvent event)
{
    sfVector2f pos = button->pos;
    sfIntRect bounds = button->bounds;
    sfVector2f scale = button->scale;
    int is_hovering = is_hovering_object(pos, bounds, scale, mousepos);

    if (button->state == DEFAULT && is_hovering == TRUE)
        button->state = HOVER;
    if (button->state == HOVER && is_hovering == FALSE)
        button->state = DEFAULT;
    if (button->state == HOVER && event.type == sfEvtMouseButtonPressed)
        button->state = CLICKING;
    if (button->state == CLICKING && event.type == sfEvtMouseButtonReleased) {
        if (is_hovering_object(pos, bounds, scale, mousepos))
            button->state = HOVER;
        else
            button->state = DEFAULT;
    }
    return SUCCESS;
}

static int process_actions(button_t *button, game_data_t *game_data)
{
    if (button == NULL)
        return ERR;
    for (int j = 0; j < button->action_count; j += 1)
        button->actions[j](game_data, button->actions_value[j]);
    return SUCCESS;
}

int change_button_state(sprite_t *sprite, int state)
{
    sfIntRect new_rect = {0, 0, 0, 0};

    new_rect.height = sprite->rect.height;
    new_rect.width = sprite->rect.width;
    new_rect.top = sprite->rect.top;
    new_rect.left = (sprite->rect.width * state);
    sprite->rect = new_rect;
    sprite->frame_state = state;
    sfSprite_setTextureRect(sprite->object, new_rect);
    return SUCCESS;
}

static int
process_buttons(button_t **buttons, game_data_t *game_data, sfEvent event)
{
    int old_state = DEFAULT;

    for (int j = 0; buttons[j] != NULL; j += 1) {
        old_state = buttons[j]->state;
        check_button_state(buttons[j], game_data->window->mousepos, event);
        if (old_state == CLICKING && old_state != buttons[j]->state)
            process_actions(buttons[j], game_data);
        if (old_state != buttons[j]->state)
            change_button_state(buttons[j]->sprite, buttons[j]->state);
    }
    return SUCCESS;
}

int process_menus(game_data_t *game_data, sfEvent event)
{
    if (game_data == NULL)
        return ERR;
    for (int i = 0; game_data->menus[i] != NULL; i += 1) {
        if (game_data->menus[i]->visibility == ACTIVE) {
            process_buttons(game_data->menus[i]->buttons, game_data, event);
        }
    }
    return SUCCESS;
}

static void do_key_events(game_data_t *game_data, sfEvent event, char *test)
{
    keyevent_t **key_events = game_data->key_events;

    if (test != NULL) {
        for (int i = 0; i < key_events[event.key.code]->count; i += 1)
            key_events[event.key.code]->actions[i](game_data, test,
            key_events[event.key.code]->actions_value[i]);
    }
}

int process_keyevents(game_data_t *game_data, sfEvent event)
{
    char *test = NULL;

    if (game_data == NULL)
        return ERR;
    if (event.type == sfEvtKeyPressed) {
        test = "pressed";
        game_data->key_pressed[event.key.code] = TRUE;
    }
    if (event.type == sfEvtKeyReleased) {
        test = "released";
        game_data->key_pressed[event.key.code] = FALSE;
    }
    do_key_events(game_data, event, test);
    return SUCCESS;
}

int process_events(game_data_t *game_data)
{
    sfRenderWindow *window = NULL;
    sfEvent event;

    if (game_data == NULL)
        return ERR;
    window = game_data->window->w;
    while (sfRenderWindow_pollEvent(window, &event)) {
        event_close(game_data, event);
        process_keyevents(game_data, event);
        process_menus(game_data, event);
        window = game_data->window->w;
    }
    return SUCCESS;
}
