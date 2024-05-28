/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** array
*/

#include "my_rpg.h"

int ptr_array_len(void **array)
{
    int count = 0;

    if (array == NULL)
        return count;
    for (int i = 0; array[i] != NULL; i += 1)
        count += 1;
    return count;
}

int free_ptr_array(void **array)
{
    if (array == NULL)
        return SUCCESS;
    for (int i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    free(array);
    return SUCCESS;
}
