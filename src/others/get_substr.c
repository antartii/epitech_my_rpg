/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** get_substr
*/

#include "my_rpg.h"

char *get_substr(const char *str, int const start, int const end)
{
    int length = end - start + 1;
    char *substr = NULL;

    substr = malloc((length + 1) * sizeof(char));
    strncpy(substr, str + start, length);
    substr[length] = '\0';
    return substr;
}
