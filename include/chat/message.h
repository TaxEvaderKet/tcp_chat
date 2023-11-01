#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_DETAILS_LENGTH (MAX_USERNAME_LENGTH + 140)
#define MAX_MESSAGE_LENGTH (MAX_DETAILS_LENGTH + 2048)

#include "../user_auth/user_auth.h"
#include <time.h>
#include "net.h"

int send_message(User *usr, char *msg_buffer, size_t msg_buffer_len, int fd);
int receive_message(char *msg_buffer, size_t msg_buffer_len, int fd);

#endif // !MESSAGE_H
