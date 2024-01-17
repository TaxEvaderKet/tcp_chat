#ifndef USER_AUTH_H
#define USER_AUTH_H
#define MAX_PASSWORD_LENGTH 64
#define MAX_USERNAME_LENGTH 32
#define SALT_LENGTH 16
#define FILE_PERMISSIONS 0644 /* read, write, but not execute */
#define USERDATA_FILE_NAME "userdata"


typedef struct 
{
    // int user_id;                     | This doesn't do anything yet, so I got to figure out how to use this for now, if at all.
    char password[MAX_PASSWORD_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    int logged_in;
} User;

enum actions {
    LOGOUT = 0,
    LOGIN = 1
};

/*
 * Purpose: Putting different kinds of locks on a file descriptor.
 * Example of usage: nlock_file(fd_to_some_file, F_WRLCK); 
 * Possible values for mode: F_RDLCK (shared lock), F_WRLCK (exclusive lock), and F_UNLCK (remove lock)
*/
void nlock_file(int fd, int mode);

/*
 * Purpose: Writes user login data to a file. File is created if it doesn't exist.
 * Example of usage: signup(&example_usr);
*/
int signup(User *user);

/*
 * Purpose: Reading from user data file and setting the logged_in flag to action.
 * Example of usage: logn(&example_usr, LOGIN);
*/
int logn(User *user, int action);


/*
 * This is just for safely reading passwords.
 * Just a wrapper, but I thought this belongs here.
*/
void read_password(char password_buffer[MAX_PASSWORD_LENGTH], char *prompt, int flags);

#endif // !USER_AUTH
