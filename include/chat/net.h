#ifndef NET_H
#define NET_H
#define MAX_BACKLOGS 25

typedef unsigned short portnum_t;

int init_socket(portnum_t port);
int accept_connection(int server_fd);

#endif // !NET_H
