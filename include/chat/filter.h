#ifndef FILTER
#define FILTER
#define MAX_MESSAGE_LENGTH 1024
#define MAX_SEARCH_SIZE (MAX_MESSAGE_LENGTH / 16)
#define MAX_REPLACE_SIZE (MAX_SEARCH_SIZE / 2)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strreplace(char *str, char *search, char *replace);

#endif // !FILTER