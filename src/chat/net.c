// License: GPL 3.0 or later 
/*********************************************
 * net.c: Simplifying socket stuff.          *   
 * Copyright (C) 2023-2024 TaxEvaderKet      *
 * Full notice can be found in src/app.c     *
 *********************************************
*/

#include "../../include/chat/net.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Creates and binds the server socket.
 * @param [port] unsigned short. Will be the port the server listens to.
 * @returns the server file descriptor, or 1 on error.
*/
int init_socket(portnum_t port)
{
    if (port > USHRT_MAX || port < 1024)
    {
        fprintf(stderr,
                "\x1b[31mPort number cannot exceed %d\
                or be less than 1024\n\x1b[0m", USHRT_MAX);
        
        return EXIT_FAILURE;
    }

    int server_fd;
    struct sockaddr_in server_addr;
    
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return EXIT_FAILURE;
    }

    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, 
             (struct sockaddr *)&server_addr, 
             sizeof(server_addr)) == -1)
    {
        perror("bind");
        return EXIT_FAILURE;
    }

    return server_fd;
}

/*
 * Listens for connections and accepts.
 * @param [server_fd] the server socket's file descriptor.
 * @returns client file descriptor, or 1 on error. 
*/
int accept_connection(int server_fd)
{
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    
    if (listen(server_fd, MAX_BACKLOGS) == -1)
    {
        perror("listen");
        return EXIT_FAILURE;
    }

    if ((client_fd = accept(server_fd,
                            (struct sockaddr *)&client_addr, 
                            &client_addrlen)) == -1)
    {
        perror("accept");
        return EXIT_FAILURE;
    }
    
    return client_fd;
}
