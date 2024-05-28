/*
** EPITECH PROJECT, 2024
** My rpg draw_stats
** File description:
** draw stats
*/

#include "my_rpg.h"

static void draw_square(game_data_t *game_data, sfVector2f pos)
{
    sfRectangleShape *square = sfRectangleShape_create();
    sfColor color = sfColor_fromRGBA(200, 200, 200, 50);

    sfRectangleShape_setFillColor(square, color);
    sfRectangleShape_setPosition(square, pos);
    sfRectangleShape_setSize(square, (sfVector2f) {25, 25});
    sfRectangleShape_setScale(square, (sfVector2f) {10, 10});
    sfRenderWindow_drawRectangleShape(game_data->window->w, square, NULL);
    sfRectangleShape_destroy(square);
}

static void draw_stats_exploration(game_data_t *game_data,
    entity_t *player, sfVector2f pos)
{
    sfText *text = NULL;
    sfFont *font = NULL;
    char stats[90] = {};

    draw_square(game_data, pos);
    sprintf(stats, "HP : %d\nATK : %d\nDEF : %d\nSPD : %d",
            player->base_hp, player->base_atk,
            player->base_def, player->base_spd);
    font = sfFont_createFromFile("fonts/anta_font.ttf");
    text = sfText_create();
    sfText_setString(text, stats);
    sfText_setCharacterSize(text, 48);
    sfText_setPosition(text, (sfVector2f) {pos.x + 10, pos.y + 10});
    sfText_setFont(text, font);
    sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
}

static void draw_hp_player(game_data_t *game_data)
{
    entity_t *player = get_entity(game_data->entities, "player");
    sfText *text = NULL;
    sfFont *font = NULL;
    char stats[11] = {};

    sprintf(stats, "%d/%d", player->curr_hp, player->base_hp);
    font = sfFont_createFromFile("fonts/anta_font.ttf");
    text = sfText_create();
    sfText_setString(text, stats);
    sfText_setCharacterSize(text, 48);
    sfText_setPosition(text, (sfVector2f) {75, 95});
    sfText_setFont(text, font);
    sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
}

static void draw_hp_enemy(game_data_t *game_data)
{
    entity_t *enemy = get_entity(game_data->entities, "enemy");
    sfText *text = NULL;
    sfFont *font = NULL;
    char stats[90] = {};

    sprintf(stats, "%d/%d", enemy->curr_hp, enemy->base_hp);
    font = sfFont_createFromFile("fonts/anta_font.ttf");
    text = sfText_create();
    sfText_setString(text, stats);
    sfText_setCharacterSize(text, 48);
    sfText_setPosition(text, (sfVector2f) {1690, 95});
    sfText_setFont(text, font);
    sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
}

static void draw_head_fight(game_data_t *game_data)
{
    sfText *text = NULL;
    sfFont *font = NULL;

    font = sfFont_createFromFile("fonts/anta_font.ttf");
    text = sfText_create();
    sfText_setString(text, "PLAYER                            VS    \
                        ENEMY");
    sfText_setCharacterSize(text, 64);
    sfText_setPosition(text, (sfVector2f) {30, 5});
    sfText_setFont(text, font);
    sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
    draw_hp_enemy(game_data);
    draw_hp_player(game_data);
}

static void draw_stats_fighting(game_data_t *game_data,
    entity_t *player, sfVector2f pos)
{
    sfText *text = NULL;
    sfFont *font = NULL;
    char stats[90] = {};

    draw_head_fight(game_data);
    draw_square(game_data, pos);
    sprintf(stats, "- YOU -\nATK : %d\nDEF : %d\nSPD : %d",
            player->curr_atk, player->curr_def, player->curr_spd);
    font = sfFont_createFromFile("fonts/anta_font.ttf");
    text = sfText_create();
    sfText_setString(text, stats);
    sfText_setCharacterSize(text, 48);
    sfText_setPosition(text, (sfVector2f) {pos.x + 10, pos.y + 10});
    sfText_setFont(text, font);
    sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
}

void set_text_potions(game_data_t *game_data,
    sfText **text, sfFont **font, sfVector2f pos)
{
    int nb_potions = game_data->stock_potions[0] +
        game_data->stock_potions[1] + game_data->stock_potions[2];
    char stats[90] = {};

    sprintf(stats, "%d\t %d\t %d", game_data->stock_potions[0],
                game_data->stock_potions[1], game_data->stock_potions[2]);
    *font = sfFont_createFromFile("fonts/anta_font.ttf");
    *text = sfText_create();
    sfText_setString(*text, stats);
    sfText_setCharacterSize(*text, 48);
    if (nb_potions > 27)
        sfText_setCharacterSize(*text, 37);
    if (nb_potions > 200)
        sfText_setCharacterSize(*text, 32);
    sfText_setPosition(*text, pos);
    sfText_setFont(*text, *font);
}

int draw_stats_glob(game_data_t *game_data)
{
    entity_t *player = get_entity(game_data->entities, "player");
    sfVector2f player_pos = sfSprite_getPosition(player->sprite->object);
    sprite_t *inv = find_sprite(game_data->sprites, "inv");
    sfVector2f inv_pos = sfSprite_getPosition(inv->object);

    if (game_data->gamemode == EXPLORATION) {
        draw_stats_exploration(game_data, player,
            (sfVector2f) {player_pos.x - 870, player_pos.y + 360});
        draw_nb_potions(game_data, TRUE,
            (sfVector2f) {player_pos.x - 70, player_pos.y + 485});
    }
    if (game_data->gamemode == FIGHTING) {
        draw_stats_fighting(game_data, player, (sfVector2f) {1660, 820});
        draw_nb_potions(game_data, inv->visibility,
                        (sfVector2f) {inv_pos.x + 10, inv_pos.y + 5});
    }
    return SUCCESS;
}

void edit_positions_explo(game_data_t *game_data, sfRenderWindow *window)
{
    entity_t *player = get_entity(game_data->entities, "player");
    sfVector2f player_pos = sfSprite_getPosition(player->sprite->object);
    sprite_t *inv = find_sprite(game_data->sprites, "inv");
    sfVector2f pos = sfSprite_getPosition(inv->object);

    if (game_data->gamemode == EXPLORATION) {
        sfSprite_setPosition(inv->object, (sfVector2f) {player_pos.x - 80,
                                                        player_pos.y + 480});
        sfRenderWindow_drawSprite(window, inv->object, NULL);
        sfSprite_setPosition(inv->object, pos);
    }
}
