#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_DECORATIONS_LENGTH (MAX_USERNAME_LENGTH + FMT_CHARS)
#define MAX_MESSAGE_LENGTH (MAX_DECORATIONS_LENGTH + MAX_CONTENT_LENGTH)

#include "../user_auth/user_auth.h"
#include <stdlib.h>

extern const size_t JSON_STRING_LENGTH;
extern const size_t FMT_CHARS;
extern const size_t MAX_CONTENT_LENGTH;

int send_message(User *usr, char *msg_content, int fd);
int receive_message(char *msg_buffer, size_t bufsize, int fd);

#endif // !MESSAGE_H
