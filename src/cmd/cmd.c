/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** cmd
*/

#include "my_rpg.h"

int cmd_help(void)
{
    char *str = get_file_content("data/help.txt");

    puts(str);
    free(str);
    exit(0);
    return SUCCESS;
}

int cmd_devmode(game_data_t *game_data)
{
    puts("Launching game in devmode...");
    game_data->mode = DEVMODE;
    return SUCCESS;
}

int
do_commands(int const argc, char const *const *argv, game_data_t *game_data)
{
    if (argv == NULL || game_data == NULL)
        return ERR;
    if (argc < 2)
        return SUCCESS;
    if (strcmp(argv[1], "-h") == 0)
        cmd_help();
    if (strcmp(argv[1], "-d") == 0)
        cmd_devmode(game_data);
    return SUCCESS;
}
