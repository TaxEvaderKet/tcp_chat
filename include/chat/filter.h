#ifndef FILTER_H
#define FILTER_H
#define MAX_SEARCH_SIZE MAX_MESSAGE_LENGTH - MAX_DECORATIONS_LENGTH
#define MAX_REPLACE_SIZE MAX_MESSAGE_LENGTH - MAX_DECORATIONS_LENGTH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void strreplace(char *str, const char *search, const char *replace);

#endif // !FILTER
