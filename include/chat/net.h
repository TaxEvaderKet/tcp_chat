#ifndef NET
#define NET
#define MAX_BACKLOGS 25

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <limits.h>
#include "../user_auth/user_auth.h"
#include "filter.h"

enum SOCKET_ERRNO
{
    GENERIC_ERR = -1,
    PORT_RANGE_ERR = -2,
    SOCKET_CREATION_ERR = -3,
    BIND_ERR = -4,
    LISTEN_ERR = -5,
    ACCEPT_ERR = -6,
    SEND_ERR = -7,
    RECV_ERR = -8
};

typedef unsigned short portnum_t;

int init_socket(portnum_t port);
int accept_connection(int server_fd);

#endif // !NET
