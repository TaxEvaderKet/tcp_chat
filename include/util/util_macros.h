#ifndef UTIL_MACROS_H
#define UTIL_MACROS_H

#include <stdio.h>

#define RED "31"
#define GREEN "32"
#define YELLOW "33"
#define BLUE "34"

#define COLOR_MSG(color, fd, fmt, ...)\
    fprintf(fd, "\x1b[%sm" fmt "\x1b[0m\n", color, ##__VA_ARGS__);

#endif // !UTIL_MACROS_H
