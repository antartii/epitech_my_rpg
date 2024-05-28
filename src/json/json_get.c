/*
** EPITECH PROJECT, 2024
** new_rpg
** File description:
** json_object_get
*/

#include "my_rpg.h"


static int
json_is_value_end(char const *json, int const start_index, int const index)
{
    char first_char = json[start_index];
    char curr_char = json[index];

    if (first_char == '{' && curr_char == '}')
        return TRUE;
    if (first_char == '[' && curr_char == ']')
        return TRUE;
    if (first_char == '\"' && curr_char == '\"')
        return TRUE;
    if (is_char_in_str(first_char, "-0123456789") == TRUE &&
    is_char_in_str(json[index + 1], "0123456789") == FALSE)
        return TRUE;
    if (is_char_in_str(first_char, "tf") == TRUE && curr_char == 'e')
        return TRUE;
    if (first_char == 'n' && json[index - 1] == 'l' && curr_char == 'l')
        return TRUE;
    return FALSE;
}

static int json_count_char_in_value(char const *json, int const index)
{
    int count = 0;
    int in_quotes = FALSE;

    for (int i = index; json[i] != '\0'; i += 1) {
        if (json_is_value_end(json, index, i) == TRUE && i != index)
            return count;
        if (is_char_in_str(json[i], "[{") == TRUE && in_quotes == FALSE &&
        i != index) {
            count += json_count_char_in_value(json, i);
            i += json_count_char_in_value(json, i);
        }
        count += 1;
    }
    return count;
}

int json_count_values(char const *json)
{
    int count = 0;
    int in_quotes = FALSE;

    for (int i = 0; json[i] != '\0'; i += 1) {
        if (is_char_in_str(json[i], "\"") == TRUE)
            in_quotes = !in_quotes;
        if (json[i] == ':' && in_quotes == FALSE) {
            count += 1;
            i += json_count_char_in_value(json, i + 1) + 1;
        }
    }
    return count;
}

char **json_get_strvalues(char const *json)
{
    int first_stamp = 0;
    int in_quotes = FALSE;
    char **values = NULL;
    int index = 0;

    values = malloc(sizeof(char *) * (json_count_values(json) + 1));
    values[json_count_values(json)] = NULL;
    for (int i = 0; json[i] != '\0'; i += 1) {
        if (is_char_in_str(json[i], "\"") == TRUE)
            in_quotes = !in_quotes;
        if (json[i] == ':' && in_quotes == FALSE) {
            first_stamp = i + 1;
            i += json_count_char_in_value(json, i + 1) + 1;
            values[index] = get_substr(json, first_stamp, i);
            index += 1;
        }
    }
    return values;
}

char **json_get_strkeys(char const *json)
{
    int first_stamp = 0;
    int in_quotes = FALSE;
    char **keys = NULL;
    int index = 0;

    keys = malloc(sizeof(char *) * (json_count_values(json) + 1));
    keys[json_count_values(json)] = NULL;
    for (int i = 0; json[i] != '\0'; i += 1) {
        if (in_quotes == FALSE && json[i] == '\"')
            first_stamp = i + 1;
        if (in_quotes == TRUE && json[i] == '\"') {
            keys[index] = get_substr(json, first_stamp, i - 1);
            index += 1;
        }
        if (is_char_in_str(json[i], "\"") == TRUE)
            in_quotes = !in_quotes;
        if (json[i] == ':' && in_quotes == FALSE)
            i += json_count_char_in_value(json, i + 1) + 1;
    }
    return keys;
}

json_type_t json_get_value_type(char const *value)
{
    if (value == NULL)
        return NULL_TYPE;
    if (value[0] == '\"')
        return STRING;
    if (value[0] == '{')
        return JSON_OBJECT;
    if (value[0] == '[')
        return ARRAY;
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0)
        return BOOLEAN;
    if (strcmp(value, "null") == 0)
        return NULL_TYPE;
    return NUMBER;
}
