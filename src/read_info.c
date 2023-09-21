#include <stdio.h>
#include <string.h>
#include "../include/user_auth/read_info.h"

void sanitize(char *s)
{
    size_t n = strcspn(s, "\n");
    s[n] = '\0';
}
