#include "../../include/chat/filter.h"

/*
 * Takes in a string, finds substrings that match the given one, and replace it with the one specified.
 * @param [str] The string you want substrings to be replaced in.
 * @param [search] The substring that is to be replaced.
 * @param [replace] The substring that [search] is replaced with, if found.
*/
void strreplace(char *str, char *search, char *replace)
{
    if (strlen(search) >= strlen(str))
    {
        puts("\x1b[31mWhat the hell are you doing?\x1b[0m");
        exit(1);
    }

    char buffer[strnlen(str, MAX_MESSAGE_LENGTH)];
    char *p = str;
    
    while ((p = strstr(p, search)))
    {
        strncpy(buffer, str, p - str);
        buffer[p - str] = '\0';
        strncat(buffer, replace, MAX_REPLACE_SIZE);
        strncat(buffer, p + strlen(search), MAX_SEARCH_SIZE);
        strncpy(str, buffer, MAX_MESSAGE_LENGTH);
        p++;
    }
}

