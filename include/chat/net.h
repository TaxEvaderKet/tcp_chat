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

typedef unsigned short portnum_t;

int init_socket(portnum_t port);
int accept_connection(int server_fd);

#endif // !NET
