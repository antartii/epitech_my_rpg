/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** json_array
*/

#include "my_rpg.h"

int json_array_count(char const *value)
{
    int count = 0;
    int read_value = FALSE;

    if (value == NULL)
        return count;
    for (int i = 1; value[i + 1] != '\0'; i += 1) {
        if (is_char_in_str(value[i], "\n \t,") == FALSE && read_value == FALSE)
            read_value = TRUE;
        if (value[i] == ',' && read_value == TRUE) {
            count += 1;
            read_value = FALSE;
        }
    }
    if (read_value == TRUE)
        count += 1;
    return count;
}

char **json_array_create(char const *value)
{
    char **array = NULL;
    int index = 0;
    int read_value = FALSE;
    int first_stamp = 0;

    array = malloc(sizeof(char *) * (json_array_count(value) + 1));
    array[json_array_count(value)] = NULL;
    for (int i = 1; value[i + 1] != '\0'; i += 1) {
        if (is_char_in_str(value[i], "\n \t,") == FALSE && read_value == FALSE)
            first_stamp = i;
        if (is_char_in_str(value[i], "\n \t,") == TRUE && read_value == TRUE) {
            array[index] = get_substr(value, first_stamp, i - 1);
            index += 1;
        }
        if (is_char_in_str(value[i], "\n \t,") == read_value)
            read_value = !read_value;
    }
    if (read_value == TRUE)
        array[index] = get_substr(value, first_stamp, strlen(value) - 2);
    return array;
}
