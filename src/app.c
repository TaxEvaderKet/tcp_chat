#include "../include/chat/net.h"

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
    
    puts("Enter a uh... string.");
    fgets(msg, sizeof(msg), stdin);
    
    strreplace(msg, "\x1b", "");

    printf("%s\n", msg);

    User login_test;
    char login_name[MAX_USERNAME_LENGTH + 1];
    char *login_password;

    puts("Enter username.");
    fgets(login_name, MAX_USERNAME_LENGTH, stdin);
    login_password = getpass("Enter password.\n");

    remove_newline(login_name);

    strncpy(login_test.username, login_name, MAX_USERNAME_LENGTH);
    strncpy(login_test.password, login_password, MAX_PASSWORD_LENGTH);
    login(&login_test);
}
