/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** is_char_in_str
*/

#include "my_rpg.h"

int is_char_in_str(char const c, char const *str)
{
    if (str == NULL)
        return FALSE;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == c)
            return TRUE;
    }
    return FALSE;
}
