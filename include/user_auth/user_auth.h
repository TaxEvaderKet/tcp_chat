#ifndef USER_AUTH_H
#define USER_AUTH_H
#define MAX_PASSWORD_LENGTH 64
#define MAX_USERNAME_LENGTH 32
#define SALT_LENGTH 16
#define FILE_PERMISSIONS 0644 /* read, write, but not execute */
#define USERDATA_FILE_NAME "userdata"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct 
{
    // int user_id;                     | This doesn't do anything yet, so I got to figure out how to use this for now, if at all.
    char password[MAX_PASSWORD_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    int logged_in;
} User;

/*
 * Purpose: Putting different kinds of locks on a file descriptor.
 * Example of usage: nlock_file(fd_to_some_file, F_WRLCK); 
 * For the different types of locks, see fcntl.
*/
void nlock_file(int fd, int mode);

/*
 * Purpose: Writes user login data to a file. File is created if it doesn't exist.
 * Example of usage (not recommended): signup((User *)&{ "password", "user", 0 });
 * Disclaimer: The examples below (and the one above) are for demonstration purposes only.
*/
int signup(User *user);

/*
 * Purpose: Reading from user data file and setting the logged_in flag to 1.
 * Example of usage (also not recommended): login((User *)&{ "password123", "user123", 0 });
*/
int login(User *user);

/*
 * Purpose: Similar to `login`, except it sets the logged_in flag to 0.
 * Example of usage (please don't do this at home): logout((User *)&{ "password", "user", 1 });
*/
int logout(User *user);

#endif // !USER_AUTH
