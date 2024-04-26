// License: GNU GPL 3.0 or later
/******************************************************************************************************************
 * This file only provides one function, which will serve the purpose of input sanitization. (among other things) *
 * Copyright (C) 2023 TaxEvaderKet                                                                                *
 * Full notice can be found in src/app.c                                                                          *
 ******************************************************************************************************************
*/

#include "../../include/chat/filter.h"

/*
 * Takes in a string, finds substrings that match the given one, and replace it with the one specified.
 * @param [str] The string you want substrings to be replaced in.
 * @param [search] The substring that is to be replaced.
 * @param [replace] The substring that [search] is replaced with, if found.
*/
void strreplace(char *str, const char *search, const char *replace)
{
    size_t search_len = strlen(search);
    size_t replace_len = strlen(replace);

    if (search_len > strlen(str) || replace_len > strlen(str)) {
        fprintf(stderr, "\x1b[31mSearch or replace string larger than input string.\n\x1b[0m");
        exit(EXIT_FAILURE);
    }
    
    size_t max_increase = (replace_len > search_len) ? (replace_len - search_len) : 0;    
    
    char buffer[strnlen(str, MAX_MESSAGE_LENGTH) + max_increase]; 
    
    if (sizeof(buffer) < strlen(str)) {
        fprintf(stderr, "\x1b[31mSize of input string exceeds the maximum of the buffer.\n\x1b[0m");
        exit(EXIT_FAILURE);
    }

    char *p = str;
    
    while ((p = strstr(p, search)))
    {
        strncpy(buffer, str, p - str);
        buffer[p - str] = '\0';
        strncat(buffer, replace, MAX_REPLACE_SIZE - 1);
        strncat(buffer, p + strlen(search), MAX_SEARCH_SIZE - 1);
        strncpy(str, buffer, strlen(str));
        p++;
    }
}
