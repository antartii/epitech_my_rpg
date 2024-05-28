/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** get_file_content
*/

#include "my_rpg.h"

char *get_file_content(char const *file_path)
{
    FILE *file = fopen(file_path, "r");
    char *file_content = NULL;
    struct stat file_stat;

    stat(file_path, &file_stat);
    file_content = malloc(sizeof(char) * (file_stat.st_size + 1));
    fread(file_content, 1, file_stat.st_size, file);
    fclose(file);
    file_content[file_stat.st_size] = '\0';
    return file_content;
}
