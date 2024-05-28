/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** draw
*/

#include "my_rpg.h"

static int draw_devmode_menu(sfRenderWindow *window, menu_t *menu)
{
    sfColor color = sfGreen;
    sfRectangleShape *button_rect = NULL;

    for (int i = 0; menu->buttons[i] != NULL; i += 1) {
        if (menu->buttons[i]->state == DEFAULT)
            color = sfGreen;
        if (menu->buttons[i]->state == HOVER)
            color = sfYellow;
        if (menu->buttons[i]->state == CLICKING)
            color = sfRed;
        button_rect = set_rectangle(menu->buttons[i]->bounds,
            menu->buttons[i]->pos, color, menu->buttons[i]->scale);
        sfRenderWindow_drawRectangleShape(window, button_rect, NULL);
        sfRectangleShape_destroy(button_rect);
    }
    return SUCCESS;
}

static int draw_devmode_map(map_t *map, sfVector2i curr_tile,
    sfRenderWindow *window, game_data_t *game_data)
{
    if (game_data->gamemode != EXPLORATION)
        return SUCCESS;
    for (int i = curr_tile.y - 1; i < curr_tile.y + 2; i += 1) {
        for (int j = curr_tile.x - 1; j < curr_tile.x + 2; j += 1)
            set_devmode_map(map, window, i, j);
    }
    return SUCCESS;
}

static int draw_devmode(game_data_t *game_data)
{
    sfRenderWindow *window = game_data->window->w;
    entity_t *player = get_entity(game_data->entities, "player");

    for (int i = 0; game_data->menus[i] != NULL; i += 1) {
        if (game_data->menus[i]->visibility == ACTIVE) {
            draw_devmode_menu(window, game_data->menus[i]);
            draw_devmode_map(game_data->maps[game_data->active_map],
                player->grid_pos, window, game_data);
        }
    }
    return SUCCESS;
}

int draw_exploration(game_data_t *game_data, sfRenderWindow *window)
{
    for (int i = 0;
        i < game_data->maps[game_data->active_map]->height; i += 1) {
        for (int j = 0;
            j < game_data->maps[game_data->active_map]->line_width[i]; j += 1)
            sfRenderWindow_drawSprite(window,
                game_data->maps[game_data->active_map]->tiles[i][j], NULL);
    }
    return SUCCESS;
}

static int draw_display(display_t *display, sfRenderWindow *window)
{
    for (int i = 0; display->sprites[i] != NULL; i += 1) {
        if (display->sprites[i]->visibility == TRUE) {
            sfRenderWindow_drawSprite(window, display->sprites[i]->object,
                NULL);
        }
    }
    return SUCCESS;
}

static void is_fighting(game_data_t *game_data, sprite_t *sprite)
{
    if (game_data->gamemode == FIGHTING &&
            strcmp(sprite->key, "fighting_background") && rand() % 100 == 0)
        change_sprite_frame(game_data, "fighting_background");
}

static int draw_other(display_t *display, game_data_t *game_data,
    sfRenderWindow *window)
{
    for (int i = 0; display->sprites[i] != NULL; i += 1) {
        if (display->sprites[i]->visibility == TRUE) {
            sfRenderWindow_drawSprite(window, display->sprites[i]->object,
                NULL);
            is_fighting(game_data, display->sprites[i]);
        }
    }
    return SUCCESS;
}

static int text_init(game_data_t *game_data)
{
    text(game_data, (sfVector2f) {500, 100},
        "USE YOUR ARROWS\nKEY TO MOVE AND\nF TO FIGHT !",
        (sfVector2i) {2, 2});
    text(game_data, (sfVector2f) {500, 100},
        "YOU NEED TO FIGHT SOMEONE\nTO HELP OUR VILLAGE",
        (sfVector2i) {6, 3});
    return SUCCESS;
}

static void draw_cursor(game_data_t *game_data)
{
    sprite_t *cursor = find_sprite(game_data->sprites, "cursor");

    if (game_data == NULL)
        return;
    sfSprite_setPosition(cursor->object, (sfVector2f) {
        game_data->window->mousepos.x - 20,
        game_data->window->mousepos.y - 10});
    if (game_data->gamemode != EXPLORATION)
        sfRenderWindow_drawSprite(game_data->window->w, cursor->object, NULL);
}

int draw(game_data_t *game_data)
{
    sfRenderWindow *window = NULL;
    display_t *display = game_data->displays[game_data->display_index];

    if (game_data == NULL)
        return ERR;
    window = game_data->window->w;
    sfRenderWindow_clear(window, sfBlack);
    if (game_data->gamemode == EXPLORATION)
        draw_exploration(game_data, window);
    draw_other(display, game_data, window);
    draw_display(display, window);
    if (game_data->mode == DEVMODE)
        draw_devmode(game_data);
    text_init(game_data);
    edit_positions_explo(game_data, window);
    draw_stats_glob(game_data);
    draw_cursor(game_data);
    sfRenderWindow_display(window);
    return SUCCESS;
}
