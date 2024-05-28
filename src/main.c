/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** main
*/

#include "my_rpg.h"

static int uppdate_animation(game_data_t *game_data)
{
    while ((int) game_data->settings->time_since_last_update.microseconds
        <= (1.0f / 16.0f) * 1000000) {
        change_sprite_frame(game_data, "signs");
        game_data->settings->time_since_last_update.microseconds -=
            (1.0f / 16.0f) * 1000000;
    }
    return SUCCESS;
}

static void update_cursor(game_data_t *game_data)
{
    sfVector2u size_win = sfRenderWindow_getSize(game_data->window->w);

    sfRenderWindow_setPosition(game_data->window->w, (sfVector2i) {0, 0});
    game_data->window->mousepos.x =
        (int) 1920 * game_data->window->mousepos.x / size_win.x;
    game_data->window->mousepos.y =
        (int) 1080 * game_data->window->mousepos.y / size_win.y;
}

int game(game_data_t *game_data)
{
    if (game_data == NULL)
        return ERR;
    while (game_data->is_running == TRUE) {
        game_data->settings->time =
            sfClock_restart(game_data->settings->clock);
        game_data->settings->time_since_last_update.microseconds +=
            game_data->settings->time.microseconds;
        uppdate_animation(game_data);
        game_data->window->mousepos =
            sfMouse_getPositionRenderWindow(game_data->window->w);
        update_cursor(game_data);
        update(game_data);
        process_events(game_data);
        draw(game_data);
    }
    return SUCCESS;
}

static int get_player_atk(entity_t *enemy, entity_t *player)
{
    int enemy_atk = enemy->curr_atk - player->curr_def;
    time_t t;

    srand(time(&t));
    if (rand() % 100 <= enemy->curr_luck)
        enemy_atk *= 2;
    if (enemy_atk < 0)
        enemy_atk = 0;
    return enemy_atk;
}

static void compute_fight2(int is_player_stunned,
    entity_t *player, entity_t *enemy)
{
    int enemy_atk = get_player_atk(enemy, player);
    int player_atk = get_player_atk(player, enemy);
    time_t t;

    srand(time(&t));
    if (enemy->curr_spd >= player->curr_spd) {
        player->curr_hp -= enemy_atk;
        if (is_player_stunned == FALSE)
            enemy->curr_hp -= player_atk;
    } else {
        if (is_player_stunned == FALSE)
            enemy->curr_hp -= player_atk;
        if (enemy->curr_hp > 0)
            player->curr_hp -= enemy_atk;
    }
}

int compute_fight(entity_t *player, entity_t *enemy, int is_player_stunned)
{
    compute_fight2(is_player_stunned, player, enemy);
    if (enemy->curr_hp <= 0) {
        enemy->curr_hp = enemy->base_hp;
        return 2;
    }
    if (player->curr_hp <= 0)
        return 1;
    return 0;
}

int use_potion(game_data_t *game_data, char const *state, char const *hp)
{
    entity_t *player = get_entity(game_data->entities, "player");
    int index_potion = 0;

    if (state == NULL && state != NULL)
        return ERR;
    if (strcmp(hp, "10") == 0)
        index_potion = 1;
    if (strcmp(hp, "20") == 0)
        index_potion = 2;
    if (game_data->stock_potions[index_potion] == 0)
        return SUCCESS;
    player->curr_hp += atoi(hp);
    game_data->stock_potions[index_potion] -= 1;
    if (player->curr_hp > player->base_hp)
        player->curr_hp = player->base_hp;
    return SUCCESS;
}

int main(int const argc, char const *const *argv)
{
    game_data_t *game_data = init_game_data();

    generate_data(game_data);
    init_keys_action(game_data->key_events);
    init_buttons_action(game_data->buttons);
    do_commands(argc, argv, game_data);
    game(game_data);
    destroy_game_data(game_data);
    return 0;
}
