#include "../../include/chat/net.h"
#include "../../include/util/util_macros.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <limits.h>
#include <errno.h>

/***************
 * init_socket *
 ***************
*/
int init_socket(portnum_t port) {
    if (port > USHRT_MAX || port < 1024) {
        COLOR_MSG(RED, stderr, "Port number must be between 1024 and 65535.");
        errno = EINVAL;
        return -1;
    }

    int server_fd;
    struct sockaddr_in server_addr;
    
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, 
             (struct sockaddr *)&server_addr, 
             sizeof(server_addr)) == -1) {
        perror("bind");
        return -1;
    }

    return server_fd;
}

/*********************
 * accept_connection *
 *********************
*/
int accept_connection(int server_fd) {
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    
    if (listen(server_fd, MAX_BACKLOGS) == -1) {
        perror("listen");
        return -1;
    }

    if ((client_fd = accept(server_fd,
                            (struct sockaddr *)&client_addr, 
                            &client_addrlen)) == -1) {
        perror("accept");
        return -1;
    }
    
    return client_fd;
}
