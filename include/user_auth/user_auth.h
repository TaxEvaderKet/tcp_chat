#ifndef USER_AUTH

#define USER_AUTH
#define MAX_PASSWORD_LENGTH 64
#define MAX_USERNAME_LENGTH 32

/*
 * CAUTION: USERNAMES, AND PASSWORDS ARE PERMANENT.
 * changes to logged_in take effect immediately.
*/
typedef struct 
{
    char password[MAX_PASSWORD_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    int logged_in;      // 1 if true, 0 if false
} User;

/**
 * Save user data to a file in the same directory as the server executable.
 * returns 0 on success, 1 on failure.
 * Takes a pointer to a User struct as parameter
*/
int create_user(User *user);

/**
 * Finds requested user and sets its logged_in flag to 1
 * returns 0 on success, 1 on failure.
 * Takes a pointer to a User struct as parameter
*/
int login(User *user);
#endif // USER_AUTH
