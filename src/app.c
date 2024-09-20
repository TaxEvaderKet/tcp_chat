#include "../include/user_auth/user_auth.h"
#include <openssl/rand.h>
#include <string.h>

#define PORT 1337

void remove_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

int main(int argc, char *argv[]) {
    User usr;

    printf("Enter username or something: ");
    fgets(usr.username, MAX_USERNAME_LENGTH, stdin);
    read_password(usr.password, "Password: ", 0);

    remove_newline(usr.username);

    if (signup(&usr) == EXIT_SUCCESS) {
        OPENSSL_cleanse(usr.password, MAX_PASSWORD_LENGTH);
    }


    User new_user;

    printf("Enter username again: ");
    fgets(new_user.username, MAX_USERNAME_LENGTH, stdin);
    read_password(new_user.password, "Password: ", 0);

    remove_newline(new_user.username);

    if (login_or_logout(&new_user, LOGIN) == EXIT_SUCCESS) {
        OPENSSL_cleanse(usr.password, MAX_PASSWORD_LENGTH);
    }

    return EXIT_SUCCESS;
}
