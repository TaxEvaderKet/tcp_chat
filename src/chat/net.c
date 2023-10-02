#include "../../include/chat/net.h"

// TODO: Actually add functionality to them lmao

/*
 * Creates and binds the server socket.
 * @param [port] unsigned short. Will be the port the server listens to.
 * @returns the server file descriptor, or a negative value on error.
*/
int init_socket(portnum_t port)
{
    if (port > USHRT_MAX || port < 1)
    {
        fprintf(stderr, "\x1b[31mPort number cannot exceed %d or be less than 1 \x1b[34m(TIP: use port numbers greater than 1000)\x1b[0m", USHRT_MAX);
        return PORT_RANGE_ERR;
    }

    int server_fd;
    return server_fd;
}

/*
 * Listens for connections and accepts.
 * @param [server_fd] the server socket's file descriptor.
 * @returns client file descriptor, or -1 on error. 
*/
int accept_connection(int server_fd)
{
    int client_fd;
    return client_fd;
}
