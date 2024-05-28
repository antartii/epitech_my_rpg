/*
** EPITECH PROJECT, 2024
** dev
** File description:
** draw_potion
*/

#include "my_rpg.h"

void set_text_key_pot(game_data_t *game_data, int visible, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("fonts/anta_font.ttf");
    char stats[10] = {};

    sprintf(stats, "P\t\tO\t\tT");
    sfText_setString(text, stats);
    sfText_setCharacterSize(text, 32);
    sfText_setPosition(text, (sfVector2f) {pos.x, pos.y + 80});
    sfText_setFont(text, font);
    if (visible == TRUE)
        sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
}

void draw_nb_potions(game_data_t *game_data,
    int visible, sfVector2f pos)
{
    sfText *text = NULL;
    sfFont *font = NULL;

    set_text_key_pot(game_data, visible, pos);
    set_text_potions(game_data, &text, &font, pos);
    if (visible == TRUE)
        sfRenderWindow_drawText(game_data->window->w, text, NULL);
    sfFont_destroy(font);
    sfText_destroy(text);
}
