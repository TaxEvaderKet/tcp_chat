#include "../include/chat/net.h"
#include <openssl/rand.h>

// I'll probably use this a few times here and there.
void remove_newline(char *s)
{
    s[strcspn(s, "\n")] = '\0';
}

int main(void)
{
    // Networking stuff is yet to be added. I want to get user_auth out first, so I can implement it more easily.
    User usr;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    puts("Enter username.");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    EVP_read_pw_string(password, MAX_PASSWORD_LENGTH, "Enter password.\n", 0);
    
    remove_newline(username);
    strncpy(usr.username, username, MAX_USERNAME_LENGTH);
    strncpy(usr.password, password, MAX_PASSWORD_LENGTH);
    usr.logged_in = 1;
   
    OPENSSL_cleanse(password, sizeof(password));
    signup(&usr);

    User login_test;
    char login_name[MAX_USERNAME_LENGTH];
    char login_password[MAX_PASSWORD_LENGTH];
    
    puts("Enter username.");
    fgets(login_name, MAX_USERNAME_LENGTH, stdin);
    EVP_read_pw_string(login_password, MAX_PASSWORD_LENGTH, "Enter password.\n", 0);

    remove_newline(login_name);
    strncpy(login_test.username, login_name, MAX_USERNAME_LENGTH);
    strncpy(login_test.password, login_password, MAX_PASSWORD_LENGTH);
    
    if (login(&login_test) == EXIT_SUCCESS)
    {
        OPENSSL_cleanse(login_password, sizeof(login_password));
    }

    char yn;

    puts("Do you want to test logout? [y/n]");
    yn = getchar();

    if (yn == EOF)
    {
        return EXIT_FAILURE;
    }
    
    switch (yn)
    {
        case 'y':
            logout(&login_test);
            break;

        case 'n':
            break;
        
        default:
            puts("Invalid option");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
