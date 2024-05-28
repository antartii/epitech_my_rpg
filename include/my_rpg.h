/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_rpg
*/

#ifndef MY_RPG_H_
    #define MY_RPG_H_

// includes
    #include <stdio.h>
    #include "macro.h"
    #include <stddef.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/errno.h>
    #include <string.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/Audio.h>
    #include <string.h>
    #include <time.h>

    #define DEFAULTMODE 0
    #define DEVMODE 1

    #define DEFAULT 0
    #define HOVER 1
    #define CLICKING 2

    #define HIDDEN 0
    #define ACTIVE 1

    #define WINDOW_DATA "window"
    #define WINDOW_TITLE "title"
    #define WINDOW_STYLE "style"
    #define WINDOW_VM "video mode"

    #define TEXTURES_DATA "textures"

    #define SPRITES_DATA "sprites"

    #define STARTING 0
    #define EXPLORATION 1
    #define FIGHTING 2

    #define SIGN_1 "USE YOU ARROWS KEY TO MOVE"
    #define SIGN_2 "AND B TO FIGHT !"
    #define SIGN_3 "WHEN YOU'RE IN FIGHT JUST PRESS SPACE"
    #define SIGN_4 "THE FIGHT WILL GIVE YOU A RANDOM VALUE BASED ON YOUR STATS"

    #define PNJ_1 "YOU NEED TO FIGHT SOMEONE\nTO HELP OUR VILLAGE"
    #define PNJ_2 "PLEASE MR.CAT WE NEED YOU"
    #define PNJ_3 "WE'LL GIVE YOU TREATS"

typedef enum json_type_s {
    STRING,
    NUMBER,
    JSON_OBJECT,
    ARRAY,
    BOOLEAN,
    NULL_TYPE,
} json_type_t;

typedef enum direction_x_s {
    NORTH,
    SOUTH
} direction_x_t;

typedef enum direction_y_s {
    EAST,
    WEST
} direction_y_t;

typedef struct game_data_s game_data_t;

typedef int (*action_t) (game_data_t *, char const *);
typedef int (*key_action_t) (game_data_t *, char const *, char const *);
typedef int (*test_t) (void);

typedef struct json_object_s {
    char **keys;
    char **values;
    json_type_t *types;
    int count;
} json_object_t;

typedef struct texture_s {
    char *key;
    sfTexture *texture;
    char *texture_path;
} texture_t;

typedef struct frame_s {
    char *key;
    sfIntRect *rects;
} frame_t;

typedef struct sprite_s {
    char *key;
    sfTexture *texture;
    sfSprite *object;

    sfIntRect rect;
    sfVector2f scale;
    int fps;
    int visibility;
    int frame_state;
    int max_frame;
} sprite_t;

typedef struct window_s {
    sfRenderWindow *w;
    sfEvent event;
    sfVideoMode vm;
    int style;
    char *title;
    sfVector2i mousepos;
} window_t;

typedef struct display_s {
    char *key;
    sprite_t **sprites;
} display_t;

typedef struct button_s {
    char *key;
    sfVector2f pos;
    sfIntRect bounds;
    int state;
    sfVector2f scale;
    action_t *actions;
    int action_count;
    char **actions_value;
    sprite_t *sprite;
} button_t;

typedef struct menu_s {
    char *key;
    int visibility;
    button_t **buttons;
} menu_t;

typedef struct keyevent_s {
    key_action_t *actions;
    char **actions_value;
    int count;
} keyevent_t;

typedef struct event_s {
    action_t *actions;
    char **actions_value;
    int count;
} event_t;

typedef struct music_s {
    char *key;
    sfMusic *audio;
} music_t;

typedef struct entity_s {
    char *name;
    int xp;
    int xp_to_next_level;
    int lvl;
    int base_atk;
    int base_def;
    int base_hp;
    int base_spd;
    int base_luck;
    int curr_atk;
    int curr_def;
    int curr_hp;
    int curr_spd;
    int curr_luck;
    int *status;
    sfVector2i is_moving;
    sfVector2i grid_pos;
    sfVector2i direction;
    sprite_t *sprite;
} entity_t;

typedef struct settings_s {
    float game_speed;
    sfClock *clock;
    sfTime time;
    sfTime time_since_last_update;
    int framerate;
} settings_t;

typedef struct map_s {
    int **map;
    int height;
    int *line_width;
    sfVector2f window_scale;
    sfVector2i scale;
    sfSprite ***tiles;
    sfVector2i grid_offset;
} map_t;

typedef struct game_data_s {
    texture_t **textures;
    sprite_t **sprites;
    window_t *window;
    display_t **displays;
    button_t **buttons;
    menu_t **menus;
    keyevent_t **key_events;
    music_t **musics;
    entity_t **entities;
    settings_t *settings;
    map_t **maps;
    int is_in_fight;
    int is_sign;
    int sign_state;
    int is_tuto;
    int tuto_state;
    int active_map;
    int *key_pressed;
    int is_running;
    int display_index;
    int mode;
    int gamemode;
    int is_fullscreen;
    int stock_potions[3];
} game_data_t;

// libC
char *strdup(const char *s);

// cmd
int
do_commands(int const argc, char const *const *argv, game_data_t *game_data);

// game_data
int destroy_game_data(game_data_t *game_data);
int generate_data(game_data_t *game_data);
texture_t **generate_textures(json_object_t *json_data);
button_t **generate_buttons(json_object_t *data, game_data_t *game_data);
display_t **generate_displays(json_object_t *json_data, sprite_t **sprites);
sprite_t **generate_sprites(
    json_object_t *json_data,
    texture_t **textures,
    sfRenderWindow *window);
window_t *generate_window(json_object_t *json_data);
game_data_t *init_game_data(void);
menu_t **generate_menus(json_object_t *json_data, button_t **buttons);
int destroy_menus(menu_t **menus);
entity_t **generate_entities(json_object_t *json_data, game_data_t *game_data);
music_t **generate_musics(json_object_t *json_data);
settings_t *set_settings(json_object_t *json_data);
keyevent_t **init_key_events(void);

int destroy_window(window_t *window);
int destroy_textures(texture_t **textures);
int destroy_sprites(sprite_t **sprites);
int destroy_displays(display_t **displays);
int destroy_buttons(button_t **buttons);
int destroy_entities(entity_t **entities);
int destroy_musics(music_t **musics);
int destroy_key_events(keyevent_t **key_events);

//event
int process_events(game_data_t *game_data);

//actions
int init_buttons_action(button_t **buttons);
int no_action(game_data_t *game_data, char const *str);
int debug_action(game_data_t *game_data, char const *str);
int add_button_action(button_t **buttons,
    char const *key, action_t action, char const *str);
int change_display(game_data_t *game_data, char const *display_name);
int change_menu_visibility(game_data_t *game_data, char const *menu_name);
int change_sprite_frame(game_data_t *game_data, char const *sprite_name);
int exit_the_game(game_data_t *game_data, char const *str);
int change_sprite_visibility(game_data_t *game_data, char const *sprite_name);
int show_only_this_menu(game_data_t *game_data, char const *menu_name);
int toggle_fullscreen(game_data_t *game_data);
int add_keyevent(keyevent_t **events, key_action_t action,
    sfKeyCode keycode, char const *str);

//my_rpg_action
int change_game_mode(game_data_t *game_data, char const *str);
int return_menu(game_data_t *game_data, char const *str);
int check_box_action(game_data_t *game_data, char const *check_box_name);
int set_starting_screen_action(button_t **buttons);
int init_keys_action(keyevent_t **key_events);
int exploration_west(game_data_t *game_data, char const *state,
    char const *str);
int exploration_north(game_data_t *game_data, char const *state,
    char const *str);
int exploration_east(game_data_t *game_data, char const *state,
    char const *str);
int exploration_south(game_data_t *game_data, char const *state,
    char const *str);
int devcommand_godevmode(game_data_t *game_data, char const *state,
    char const *str);
int devcommand_exit(game_data_t *game_data, char const *state,
    char const *str);
int devcommand_fullscreen(game_data_t *game_data,
    char const *state, char const *str);

//draw
int draw(game_data_t *game_data);
int draw_stats_glob(game_data_t *game_data);
void edit_positions_explo(game_data_t *game_data, sfRenderWindow *window);

// change state
int change_button_state(sprite_t *sprite, int state);
int change_sprite_state(sprite_t *sprite, int frame_state);

// json
sfVector2f
convert_start_pos(char *str_pos_x, char *str_pos_y, sfRenderWindow *window);
char *json_convert_to_line(char const *json);
int json_object_destroy(json_object_t *json_object);
json_object_t *json_object_create(char const *json);
int json_count_values(char const *json);
char **json_get_strvalues(char const *json);
char **json_get_strkeys(char const *json);
int json_convert_str(char **str_adress);
sfVector2f json_convert_vector2f(char const *value);
sfIntRect json_convert_intrect(char const *value);
json_type_t json_get_value_type(char const *value);
sfVideoMode json_convert_videomode(char const *value);
char **json_array_create(char const *value);
int json_array_count(char const *value);
char *json_find_value(json_object_t *json_object, char const *key);

// others
char *get_file_content(char const *file_path);
char *get_substr(const char *str, int const start, int const end);
int is_char_in_str(char const c, char const *str);
int find_texture_index(texture_t **textures, char const *key);
sprite_t *find_sprite(sprite_t **sprites, char const *key);
int free_ptr_array(void **array);
int ptr_array_len(void **array);
sfVector2f get_end_pos(
    sfVector2f start_pos, sfIntRect bounds, sfVector2f scale);
int is_hovering_object(
    sfVector2f start_pos, sfIntRect bounds, sfVector2f scale,
    sfVector2i mousepos);
sfRectangleShape *set_rectangle(
    sfIntRect bounds, sfVector2f pos, sfColor color, sfVector2f scale);
sfVector2f set_pos(sfVector2f start_pos, sfVector2f offset, sfVector2f scale);
button_t *find_button(button_t **buttons, char const *key);
menu_t *get_menu(menu_t **menus, char const *key);
int get_display_index(display_t **displays, char const *key);
menu_t *get_active_menu(game_data_t *game_data);
music_t *get_music(music_t **musics, char const *name);
entity_t *get_entity(entity_t **entities, char const *name);
int play_music(game_data_t *game_data, char const *name);
sfIntRect is_entity_grid_bounded(
    entity_t *entity, map_t *active_map, int offset);
sfVector2f get_entity_movement(entity_t *entity, game_data_t *game_data);

// other .h
    #define ACTIONCOUNT 1

int **set_map(map_t *map, char **splited_map, json_object_t *json_map);
sfVector2i update_grid_pos(entity_t *entity, map_t *active_map);
char **my_split_string(char *str, const char *delimiter);
int count_multiple(int multiple, int multiplier);
int destroy_maps(map_t **maps);
map_t **generate_maps(json_object_t *json_data, texture_t **textures);
int update(game_data_t *game_data);
int increase_volume(
    game_data_t *game_data,
    char const *music_name);
int decrease_volume(
    game_data_t *game_data,
    char const *music_name);
int flee_button(game_data_t *game_data, char const *str);
int use_potion(game_data_t *game_data, char const *state, char const *hp);
int fight_button(game_data_t *game_data, char const *str);
int compute_fight(entity_t *player, entity_t *enemy, int is_player_stunned);
int set_fighting_button_action(button_t **buttons);
int set_devmode_map(map_t *map, sfRenderWindow *window, int i, int j);
void draw_nb_potions(game_data_t *game_data,
    int visible, sfVector2f pos);
void set_text_potions(game_data_t *game_data,
    sfText **text, sfFont **font, sfVector2f pos);
int text(game_data_t *game_data, sfVector2f pos, char *str,
    sfVector2i gridpos);

#endif /* !MY_RPG_H_ */
