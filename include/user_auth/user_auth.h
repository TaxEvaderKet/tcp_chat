#ifndef USER_AUTH
#define USER_AUTH
#define MAX_PASSWORD_LENGTH 64 + 1
#define MAX_USERNAME_LENGTH 32 + 1
#define SALT_LENGTH 16
#define TOTAL_ARGON2ID_LENGTH 98 + 1

#include <sodium/core.h>
#include <sodium/crypto_pwhash.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct 
{
    int user_id;
    char password[MAX_PASSWORD_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    int logged_in;      // 1 if true, 0 if false
} User;

int signup(User *user);
int login(User *user);

#endif // !USER_AUTH
