#ifndef MESSAGE_H
#define MESSAGE_H
// Adjust this value according to your needs.
#define FMT_CHARS 9 
#define MAX_DECORATIONS_LENGTH (MAX_USERNAME_LENGTH + FMT_CHARS)
#define MAX_MESSAGE_LENGTH (MAX_DECORATIONS_LENGTH + 2048)

#include "../user_auth/user_auth.h"

int send_message(User *usr, char msg_buffer[MAX_MESSAGE_LENGTH], int fd);
int receive_message(char *msg_buffer, int fd);

#endif // !MESSAGE_H
