#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_DETAILS_LENGTH (MAX_USERNAME_LENGTH + 140)
#define MAX_MESSAGE_LENGTH (MAX_DETAILS_LENGTH + 2048)
#define MESSAGE_FORMAT "%02d:%02d | %s\n%s"

// NOTICE: Unfinished.

#include "../user_auth/user_auth.h"

int send_message(char *msg_buffer, size_t msg_buffer_len, int fd);
int receive_message(char *msg_buffer, size_t msg_buffer_len, int fd);

#endif // !MESSAGE_H
