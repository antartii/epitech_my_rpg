/*
** EPITECH PROJECT, 2024
** dev
** File description:
** my_split_str
*/

#include "my_rpg.h"

char **my_split_string(char *str, const char *delimiter)
{
    char **result = malloc(sizeof(char *));
    char *token = strtok(str, delimiter);
    int i = 0;

    result[0] = strdup(token);
    while (token != NULL) {
        result = realloc(result, sizeof(char *) * (i + 2));
        result[i] = strdup(token);
        result[i + 1] = NULL;
        i += 1;
        token = strtok(NULL, delimiter);
    }
    return result;
}
