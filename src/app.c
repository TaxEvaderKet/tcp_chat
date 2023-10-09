#include "../include/chat/net.h"
#include <openssl/rand.h>
#define PORT 1337

// I'll probably use this a few times here and there.
void remove_newline(char *s)
{
    s[strcspn(s, "\n")] = '\0';
}

int main(void)
{
    int socket_fd, client_fd;
    if ((socket_fd = init_socket(PORT)) == -1)
    {
        return EXIT_FAILURE;
    }
    
    if ((client_fd = accept_connection(socket_fd)) == -1)
    {
        return EXIT_FAILURE;
    }

    send(client_fd, (void *)"Hello, World!\n", strlen("Hello, World!\n"), 0);
    
    close(socket_fd);
    return EXIT_SUCCESS;
}
