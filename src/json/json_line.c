/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** json_line
*/

#include "my_rpg.h"

static int json_count_line(char const *json)
{
    int count = 0;
    int in_quotes = FALSE;

    for (int i = 0; json[i] != '\0'; i += 1) {
        if (is_char_in_str(json[i], "\"") == TRUE)
            in_quotes = !in_quotes;
        if (is_char_in_str(json[i], " \t\n") == FALSE || in_quotes == TRUE)
            count += 1;
    }
    return count;
}

char *json_convert_to_line(char const *json)
{
    char *json_line = NULL;
    int index = 0;
    int in_quotes = FALSE;

    json_line = malloc(sizeof(char) * (json_count_line(json) + 1));
    json_line[json_count_line(json)] = '\0';
    for (int i = 0; json[i] != '\0'; i += 1) {
        if (is_char_in_str(json[i], "\"") == TRUE)
            in_quotes = !in_quotes;
        if (is_char_in_str(json[i], " \t\n") == FALSE || in_quotes == TRUE) {
            json_line[index] = json[i];
            index += 1;
        }
    }
    return json_line;
}
