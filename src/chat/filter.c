#include "../../include/chat/filter.h"
#include "../../include/util/util_macros.h"

/**************
 * strreplace *
 **************
*/
void strreplace(char *str, const char *search, const char *replace) {
    size_t search_len = strlen(search);
    size_t replace_len = strlen(replace);

    if (search_len > strlen(str) || replace_len > strlen(str)) {
        COLOR_MSG(RED, stderr, "Search or replace string exceeds" 
                                "the length of the input string.");
        exit(EXIT_FAILURE);
    }
    
    size_t max_increase = (replace_len > search_len) 
        ? (replace_len - search_len) 
        : 0;    
    
    char buffer[strnlen(str, MAX_MESSAGE_LENGTH) + max_increase]; 
    
    if (sizeof(buffer) < strlen(str)) {
        COLOR_MSG(RED, stderr, "Buffer size is too small.");
        exit(EXIT_FAILURE);
    }

    char *p = str;
    
    while ((p = strstr(p, search))) {
        strncpy(buffer, str, p - str);
        buffer[p - str] = '\0';
        strncat(buffer, replace, MAX_REPLACE_SIZE - 1);
        strncat(buffer, p + strlen(search), MAX_SEARCH_SIZE - 1);
        strncpy(str, buffer, strlen(str));
        p++;
    }
}
