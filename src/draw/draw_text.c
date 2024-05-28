/*
** EPITECH PROJECT, 2024
** dev
** File description:
** draw_text
*/

#include "my_rpg.h"

int text(game_data_t *game_data, sfVector2f pos, char *str, sfVector2i gridpos)
{
    entity_t *player = get_entity(game_data->entities, "player");
    sfText *text = NULL;
    sfFont *font = NULL;

    if (player->grid_pos.x == gridpos.x && player->grid_pos.y ==
        gridpos.y && game_data->gamemode == EXPLORATION) {
        font = sfFont_createFromFile("fonts/anta_font.ttf");
        text = sfText_create();
        sfText_setString(text, str);
        sfText_setCharacterSize(text, 64);
        sfText_setPosition(text, pos);
        sfText_setFont(text, font);
        sfRenderWindow_drawText(game_data->window->w, text, NULL);
        sfFont_destroy(font);
        sfText_destroy(text);
    }
    return SUCCESS;
}
