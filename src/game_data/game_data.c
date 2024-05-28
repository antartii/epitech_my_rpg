/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** game_data
*/

#include "my_rpg.h"

static int init_game_data2(game_data_t *game_data)
{
    game_data->mode = DEFAULTMODE;
    game_data->is_fullscreen = FALSE;
    game_data->gamemode = STARTING;
    game_data->key_pressed = malloc(sizeof(int) * sfKeyCount);
    game_data->active_map = 0;
    game_data->sign_state = 0;
    game_data->tuto_state = 0;
    for (int i = 0; i < sfKeyCount; i += 1)
        game_data->key_pressed[i] = FALSE;
    game_data->stock_potions[0] = 5;
    game_data->stock_potions[1] = 0;
    game_data->stock_potions[2] = 0;
    return SUCCESS;
}

game_data_t *init_game_data(void)
{
    game_data_t *game_data = NULL;

    game_data = malloc(sizeof(game_data_t));
    game_data->textures = NULL;
    game_data->sprites = NULL;
    game_data->window = NULL;
    game_data->display_index = 0;
    game_data->displays = NULL;
    game_data->buttons = NULL;
    game_data->menus = NULL;
    game_data->is_running = TRUE;
    init_game_data2(game_data);
    return game_data;
}

int destroy_settings(settings_t *settings)
{
    if (settings == NULL)
        return SUCCESS;
    free(settings);
    return SUCCESS;
}

static int init_gamedata_onstart(game_data_t *game_data)
{
    change_menu_visibility(game_data, "starting_menu");
    play_music(game_data, "lmao_you_re_dumb");
    return SUCCESS;
}

int generate_data(game_data_t *game_data)
{
    char *json = get_file_content("data/data.json");
    json_object_t *json_data = json_object_create(json);

    game_data->textures = generate_textures(json_data);
    game_data->window = generate_window(json_data);
    game_data->sprites =
        generate_sprites(json_data, game_data->textures, game_data->window->w);
    game_data->displays = generate_displays(json_data, game_data->sprites);
    game_data->buttons = generate_buttons(json_data, game_data);
    game_data->menus = generate_menus(json_data, game_data->buttons);
    game_data->key_events = init_key_events();
    game_data->musics = generate_musics(json_data);
    game_data->entities = generate_entities(json_data, game_data);
    game_data->settings = set_settings(json_data);
    game_data->maps = generate_maps(json_data, game_data->textures);
    init_gamedata_onstart(game_data);
    free(json);
    json_object_destroy(json_data);
    return SUCCESS;
}

int destroy_game_data(game_data_t *game_data)
{
    sfRenderWindow_close(game_data->window->w);
    destroy_sprites(game_data->sprites);
    destroy_textures(game_data->textures);
    destroy_window(game_data->window);
    destroy_buttons(game_data->buttons);
    destroy_menus(game_data->menus);
    destroy_key_events(game_data->key_events);
    destroy_entities(game_data->entities);
    destroy_maps(game_data->maps);
    free(game_data);
    return SUCCESS;
}
