#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include "../include/user_auth/user_auth.h"
#include "../include/user_auth/read_info.h"

#define PORT 6969
#define BACKLOG_MAX 15 

int main(void)
{
/*  
 *  int socket_fd, client_fd;
    struct sockaddr_in sockaddr, client_addr;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return EXIT_FAILURE;
    }

    sockaddr.sin_port = htons(PORT);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t socket_len = sizeof(sockaddr);
    socklen_t client_len = sizeof(client_addr);

    if (bind(socket_fd, (struct sockaddr *)&sockaddr, socket_len) < 0)
    {
        perror("bind");
        return EXIT_FAILURE;
    }
    
    if (listen(socket_fd, BACKLOG_MAX) < 0) 
    {
        perror("listen");
        return EXIT_FAILURE;
    }
    
    printf("Listening on the port %d\n", PORT);

    for (;;)
    {
        client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
        
        char *msg = "Hello World\n";

        send(client_fd, (void *)msg, strlen(msg), 0);
    }
    
    close(socket_fd);

    return EXIT_SUCCESS;
    */
    
    User usr;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    puts("Enter username.");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    puts("Enter password.");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);

    sanitize(username);

    strncpy(usr.username, username, MAX_USERNAME_LENGTH);
    strncpy(usr.password, password, MAX_PASSWORD_LENGTH);
    usr.logged_in = 1;
    
    create_user(&usr);
}
