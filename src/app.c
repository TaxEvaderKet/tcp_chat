#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include "../include/user_auth/user_auth.h"
#include "../include/chat/filter.h"

#define PORT 6969
#define BACKLOG_MAX 15 

// I'll probably use this a few times here and there.
void remove_newline(char *s)
{
    s[strcspn(s, "\n")] = '\0';
}

int main(void)
{
    // Networking stuff is yet to be added. I want to get user_auth out first, so I can implement it more easily.
    
    User usr;
    char *username;
    char *password;

    puts("Enter username.");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    password = getpass("Enter password.\n");

    remove_newline(username);

    strncpy(usr.username, username, MAX_USERNAME_LENGTH);
    strncpy(usr.password, password, MAX_PASSWORD_LENGTH);
    usr.logged_in = 1;
   
    signup(&usr);

    char msg[MAX_MESSAGE_LENGTH];

    fgets(msg, sizeof(msg), stdin);
    
    strreplace(msg, "\x1b", "");

    printf("%s\n", msg);
}
