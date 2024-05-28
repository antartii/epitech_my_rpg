/*
** EPITECH PROJECT, 2024
** dev
** File description:
** fight
*/

#include "my_rpg.h"

int end_of_fight(entity_t *player, int xp_won)
{
    player->xp += xp_won;
    if (player->xp >= player->xp_to_next_level) {
        player->xp -= player->xp_to_next_level;
        player->lvl += 1;
        player->base_atk += 3;
        player->base_def += 2;
        player->base_hp += 5;
        player->base_luck += 5;
        player->base_spd += 1;
        player->xp_to_next_level = (int) (player->xp_to_next_level * 1.5f);
    }
    return SUCCESS;
}

static void draw_flee_text(game_data_t *game_data)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("fonts/anta_font.ttf");

    sfText_setString(text,
                    "YOU FAILED TO ESCAPE\nIT'S NOW THE OPPONENT'S TURN !");
    sfText_setCharacterSize(text, 48);
    sfText_setPosition(text, (sfVector2f) {200, 200});
    sfText_setFont(text, font);
    sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfRenderWindow_display(game_data->window->w);
    sfSleep(sfSeconds(1));
    sfFont_destroy(font);
    sfText_destroy(text);
}

int flee(game_data_t *game_data)
{
    entity_t *player = get_entity(game_data->entities, "player");
    int flee_chance_percentage = player->curr_spd;
    time_t t = {};
    int result = 0;

    srand((unsigned int) time(&t));
    result = rand() % 100;
    if (result >= flee_chance_percentage) {
        draw_flee_text(game_data);
        return FALSE;
    }
    return TRUE;
}

static int flee2(int computed_fight, game_data_t *game_data)
{
    entity_t *player = get_entity(game_data->entities, "player");

    if (computed_fight == 2) {
        change_game_mode(game_data, "exploration");
        change_menu_visibility(game_data, "fighting");
        change_display(game_data, "exploration");
        end_of_fight(player, 500);
    }
    return SUCCESS;
}

int flee_button(game_data_t *game_data, char const *str)
{
    entity_t *player = get_entity(game_data->entities, "player");
    entity_t *enemy = get_entity(game_data->entities, "enemy");
    int computed_fight = 0;

    if (str != NULL && str == NULL)
        return ERR;
    if (flee(game_data) == TRUE) {
        game_data->gamemode = EXPLORATION;
        change_menu_visibility(game_data, "fighting");
        change_display(game_data, "exploration");
    } else {
        computed_fight = compute_fight(player, enemy, TRUE);
        if (computed_fight == 1) {
            change_display(game_data, "game_over");
            change_menu_visibility(game_data, "fighting");
            end_of_fight(player, 500);
        }
        flee2(computed_fight, game_data);
    }
    return SUCCESS;
}

int fight_button(game_data_t *game_data, char const *str)
{
    entity_t *player = get_entity(game_data->entities, "player");
    entity_t *enemy = get_entity(game_data->entities, "enemy");
    int computed_fight = compute_fight(player, enemy, FALSE);

    if (str != NULL && str == NULL)
        return ERR;
    if (computed_fight == 1) {
        change_menu_visibility(game_data, "fighting");
        change_display(game_data, "game_over");
    }
    if (computed_fight == 2) {
        change_game_mode(game_data, "exploration");
        change_menu_visibility(game_data, "fighting");
        change_display(game_data, "exploration");
        end_of_fight(player, 500);
    }
    return SUCCESS;
}
