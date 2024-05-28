/*
** EPITECH PROJECT, 2024
** dev
** File description:
** count_multiple
*/

#include "my_rpg.h"

int count_multiple(int multiple, int multiplier)
{
    int count = 0;
    int result = 0;

    for (int i = 0; result <= multiple; i += 1) {
        result += multiplier;
        count += 1;
    }
    return count;
}
