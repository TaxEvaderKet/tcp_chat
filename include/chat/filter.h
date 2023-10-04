#ifndef FILTER
#define FILTER
#define MAX_MESSAGE_LENGTH 1025
#define MAX_SEARCH_SIZE MAX_MESSAGE_LENGTH
#define MAX_REPLACE_SIZE MAX_MESSAGE_LENGTH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strreplace(char *str, char *search, char *replace);

#endif // !FILTER
