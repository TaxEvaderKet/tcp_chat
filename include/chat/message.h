#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_DECORATIONS_LENGTH (MAX_USERNAME_LENGTH + FMT_CHARS)
#define MAX_MESSAGE_LENGTH (MAX_DECORATIONS_LENGTH + MAX_CONTENT_LENGTH)

#include "../user_auth/user_auth.h"
#include <stdlib.h>

extern const size_t JSON_STRING_LENGTH;
extern const int FMT_CHARS;
extern const int MAX_CONTENT_LENGTH;

int send_message(User *usr, char msg_buffer[MAX_MESSAGE_LENGTH], int fd);
int receive_message(char *msg_buffer, int fd);

#endif // !MESSAGE_H
