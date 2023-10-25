#ifndef FILTER_H
#define FILTER_H
#define MAX_SEARCH_SIZE MAX_MESSAGE_LENGTH - MAX_DETAILS_LENGTH
#define MAX_REPLACE_SIZE MAX_MESSAGE_LENGTH - MAX_DETAILS_LENGTH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void strreplace(char *str, char *search, char *replace);

#endif // !FILTER
