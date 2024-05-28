/*
** EPITECH PROJECT, 2024
** dev
** File description:
** update
*/

#include "my_rpg.h"

static int update_player_direction_x(
    entity_t *player, sfIntRect rect, sfVector2f *movement, int **map)
{
    if (player->direction.x == EAST && rect.left == TRUE &&
        map[player->grid_pos.y][player->grid_pos.x - 1] <= 0) {
        player->is_moving.x = FALSE;
        movement->x = 0;
        }
    if (player->direction.x == WEST && rect.width == TRUE &&
        map[player->grid_pos.y][player->grid_pos.x + 1] <= 0) {
        player->is_moving.x = FALSE;
        movement->x = 0;
        }
    return SUCCESS;
}

static int update_player_direction_y(
    entity_t *player, sfIntRect rect, sfVector2f *movement, int **map)
{
    if (player->direction.y == NORTH && rect.top == TRUE &&
            map[player->grid_pos.y - 1][player->grid_pos.x] <= 0) {
            player->is_moving.y = FALSE;
            movement->y = 0;
            }
        if (player->direction.y == SOUTH && rect.height == TRUE &&
            map[player->grid_pos.y + 1][player->grid_pos.x] <= 0) {
            player->is_moving.y = FALSE;
            movement->y = 0;
            }
    return SUCCESS;
}

int update_player_direction(
    sfIntRect rect,
    entity_t *player,
    game_data_t *game_data,
    sfVector2f *movement)
{
    int **map = game_data->maps[game_data->active_map]->map;

    if (player->is_moving.y == TRUE)
        update_player_direction_y(player, rect, movement, map);
    if (player->is_moving.x == TRUE)
        update_player_direction_x(player, rect, movement, map);
    return SUCCESS;
}

int update_player(game_data_t *game_data)
{
    entity_t *player = NULL;
    sfVector2f movement = {0, 0};
    sfIntRect rect = {0, 0, 0, 0};
    map_t *active_map = game_data->maps[game_data->active_map];

    if (game_data == NULL)
        return ERR;
    player = get_entity(game_data->entities, "player");
    movement = get_entity_movement(player, game_data);
    rect = is_entity_grid_bounded(player, active_map, 20);
    update_player_direction(rect, player, game_data, &movement);
    sfSprite_move(player->sprite->object, movement);
    update_grid_pos(player, game_data->maps[game_data->active_map]);
    return SUCCESS;
}

static void update_cam_exploration(game_data_t *game_data)
{
    sfView *camera = sfView_create();
    entity_t *player = get_entity(game_data->entities, "player");
    sfVector2f player_position = sfSprite_getPosition(player->sprite->object);
    sfFloatRect center_player =
        sfSprite_getGlobalBounds(player->sprite->object);

    player_position.x += (center_player.width / 2);
    player_position.y += (center_player.height / 2);
    sfView_setSize(camera, (sfVector2f) {1920, 1080});
    sfView_setCenter(camera, player_position);
    sfRenderWindow_setView(game_data->window->w, camera);
    sfView_destroy(camera);
}

static void update_cam(game_data_t *game_data)
{
    sfView *camera = sfView_createFromRect((sfFloatRect) {0, 0, 1920, 1080});

    sfRenderWindow_setView(game_data->window->w, camera);
    sfView_destroy(camera);
}

int update(game_data_t *game_data)
{
    if (game_data == NULL)
        return ERR;
    update_player(game_data);
    update_cam(game_data);
    if (game_data->gamemode == EXPLORATION)
        update_cam_exploration(game_data);
    return SUCCESS;
}
