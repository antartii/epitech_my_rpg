/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** exploration
*/

#include "my_rpg.h"

static int exploration_west_moving(entity_t *player)
{
    if (player == NULL)
        return ERR;
    player->direction.x = WEST;
    if (player->direction.x == EAST)
        player->is_moving.x = FALSE;
    else
        player->is_moving.x = TRUE;
    return SUCCESS;
}

int exploration_west(game_data_t *game_data,
    char const *state, char const *str)
{
    entity_t *player = NULL;

    if (game_data == NULL || state == NULL ||
        game_data->gamemode != EXPLORATION || (str == NULL && str != NULL))
        return ERR;
    player = get_entity(game_data->entities, "player");
    if (strcmp(state, "pressed") == 0)
        exploration_west_moving(player);
    if (strcmp(state, "released") == 0) {
        if (player->direction.x == WEST)
            player->is_moving.x = FALSE;
    }
    return SUCCESS;
}

static int exploration_north_moving(entity_t *player)
{
    if (player == NULL)
        return ERR;
    player->direction.y = NORTH;
    if (player->direction.y == SOUTH)
        player->is_moving.y = FALSE;
    else
        player->is_moving.y = TRUE;
    return SUCCESS;
}

int exploration_north(game_data_t *game_data, char const *state,
    char const *str)
{
    entity_t *player = NULL;

    if (game_data == NULL || state == NULL ||
        game_data->gamemode != EXPLORATION || (str == NULL && str != NULL))
        return ERR;
    player = get_entity(game_data->entities, "player");
    if (strcmp(state, "pressed") == 0)
        exploration_north_moving(player);
    if (strcmp(state, "released") == 0) {
        if (player->direction.y == NORTH)
            player->is_moving.y = FALSE;
    }
    return SUCCESS;
}

static int exploration_south_moving(entity_t *player)
{
    if (player == NULL)
        return ERR;
    player->direction.y = SOUTH;
    if (player->direction.y == NORTH)
        player->is_moving.y = FALSE;
    else
        player->is_moving.y = TRUE;
    return SUCCESS;
}

int exploration_south(
    game_data_t *game_data, char const *state, char const *str)
{
    entity_t *player = NULL;

    if (game_data == NULL || state == NULL ||
        game_data->gamemode != EXPLORATION || (str == NULL && str != NULL))
        return ERR;
    player = get_entity(game_data->entities, "player");
    if (strcmp(state, "pressed") == 0)
        exploration_south_moving(player);
    if (strcmp(state, "released") == 0) {
        if (player->direction.y == SOUTH)
            player->is_moving.y = FALSE;
    }
    return SUCCESS;
}

static int exploration_east_moving(entity_t *player)
{
    if (player == NULL)
        return ERR;
    player->direction.x = EAST;
    if (player->direction.x == WEST)
        player->is_moving.x = FALSE;
    else
        player->is_moving.x = TRUE;
    return SUCCESS;
}

int exploration_east(
    game_data_t *game_data,
    char const *state, char const *str)
{
    entity_t *player = NULL;

    if (game_data == NULL || state == NULL ||
        game_data->gamemode != EXPLORATION || (str == NULL && str != NULL))
        return ERR;
    player = get_entity(game_data->entities, "player");
    if (strcmp(state, "pressed") == 0)
        exploration_east_moving(player);
    if (strcmp(state, "released") == 0) {
        if (player->direction.x == EAST)
            player->is_moving.x = FALSE;
    }
    return SUCCESS;
}
