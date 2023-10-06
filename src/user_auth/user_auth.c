#include "../../include/user_auth/user_auth.h"

/*
 * Helper function.
 * @param [mode] 0 = readlock, 1 = writelock, 2 = unlock
*/
void nlock_file(int fd, int mode)
{
    struct flock file_lock;
    
    if (mode > F_UNLCK || mode < F_RDLCK)
    {
        fprintf(stderr, "Invalid input.\n");
        exit(EXIT_FAILURE);
    }
    
    file_lock.l_type = mode;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0;

    fcntl(fd, F_SETLK, &file_lock);
}

int hash_password(const char *password, char *hash, uint8_t *salt)
{
    if (sodium_init() < 0)
    {
        fprintf(stderr, "\x1b[31mFailed to initialize libsodium\n\x1b[0m");
        return EXIT_FAILURE;
    }

    randombytes_buf(salt, crypto_pwhash_SALTBYTES);

    if (crypto_pwhash_str(hash, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
        fprintf(stderr, "\x1b[31mFailed to hash password\n\x1b[0m");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Takes in user data, hashes the password, and saves username and argon2id digest to a file
 * @param pointer to a user struct
 * @returns 1 on error, 0 on success
*/
int signup(User *user)
{
    char hash[crypto_pwhash_STRBYTES];
    uint8_t salt[crypto_pwhash_SALTBYTES];

    if (hash_password(user->password, hash, salt) != 0)
    {
        fprintf(stderr, "\x1b[31mfailed to hash password\n\x1b[0m");
        return EXIT_FAILURE;
    }
    
    if (access(USERDATA_FILE_NAME, F_OK) != 0)
    {
        int fd_userdata;
        
        if ((fd_userdata = open(USERDATA_FILE_NAME, O_RDWR | O_CREAT, FILE_PERMISSIONS)) == -1)
        {
            perror("fcntl");
            return EXIT_FAILURE;
        }
        
        FILE *userdata = fdopen(fd_userdata, "w");
        user->logged_in = 0;
        
        nlock_file(fd_userdata, F_WRLCK);
        fprintf(userdata, "%s %s %d\n", user->username, hash, user->logged_in);
        nlock_file(fd_userdata, F_UNLCK);

        puts("\x1b[32mSuccessfully created the user data file and saved login data.\x1b[0m");
        fclose(userdata);
        close(fd_userdata);
        return EXIT_SUCCESS;
    }

    int fd_userdata;
    
    if ((fd_userdata = open(USERDATA_FILE_NAME, O_APPEND | O_WRONLY, FILE_PERMISSIONS)) == -1)
    {
        perror("fcntl");
        return EXIT_FAILURE;
    }

    FILE *userdata = fdopen(fd_userdata, "a");
    user->logged_in = 0;

    nlock_file(fd_userdata, F_WRLCK);
    fprintf(userdata, "%s %s %d\n", user->username, hash, user->logged_in);
    
    nlock_file(fd_userdata, F_UNLCK);
    puts("\x1b[32mSuccessfully saved login data.\x1b[0m");
    fclose(userdata);
    close(fd_userdata);
    return EXIT_SUCCESS;
}

/*
 * Reads from a userdata file and compares data from passed in user struct with stored user data, then sets the logged_in flag to 1 (true).
 * @param pointer to a user struct 
 * @returns 0 on success, 1 on error
*/
int login(User *user)
{
    int fd_userdata;

    if ((fd_userdata = open(USERDATA_FILE_NAME, O_RDWR, FILE_PERMISSIONS)) == -1)
    {
        perror("fcntl");
        return EXIT_FAILURE;
    }

    FILE *userdata = fdopen(fd_userdata, "r+");

    if (userdata == NULL)
    {
        perror("fdopen");
        return EXIT_FAILURE;
    }
    
    char line[MAX_USERNAME_LENGTH + TOTAL_ARGON2ID_LENGTH + 1];
    
    while (fgets(line, sizeof(line), userdata) != NULL)
    {
        char username[MAX_USERNAME_LENGTH];
        char stored_hash[crypto_pwhash_STRBYTES];
        int logged_in;

        if (sscanf(line, "%s %s %d\n", username, stored_hash, &logged_in) != 3)
        {
            continue;
        }

        if (strncmp(username, user->username, MAX_USERNAME_LENGTH) != 0)
        {
            continue;
        }

        if (logged_in == 1)
        {
            puts("You're already logged in.");
            fclose(userdata);
            close(fd_userdata);
            return EXIT_SUCCESS;
        }

        if (crypto_pwhash_str_verify(stored_hash, user->password, strlen(user->password)) == 0)
        {
            user->logged_in = 1;
            nlock_file(fd_userdata, F_RDLCK);
            fseek(userdata, -strlen(line), SEEK_CUR);
            fprintf(userdata, "%s %s %d\n", user->username, stored_hash, user->logged_in);
            
            nlock_file(fd_userdata, F_UNLCK);
            fclose(userdata);
            close(fd_userdata);
            puts("\x1b[32mLogin successful.\x1b[0m");
            return EXIT_SUCCESS;
        }
    }
    
    fprintf(stderr, "Incorrect username or password.\n");
    fclose(userdata);
    close(fd_userdata);
    return EXIT_FAILURE;
}

/*
 * Sets the logged_in flag to 0. Originally sent SIGTERM to the process, but oh well.
 * @param [user] The user to log out.
 * @returns 0 on success, 1 on error.
*/
int logout(User *user)
{
    int fd_userdata;

    if ((fd_userdata = open(USERDATA_FILE_NAME, O_RDWR, FILE_PERMISSIONS)) == -1)
    {
        perror("fcntl");
        return EXIT_FAILURE;
    }

    FILE *userdata = fdopen(fd_userdata, "r+");

    if (userdata == NULL)
    {
        perror("fdopen");
        return EXIT_FAILURE;
    }

    char line[MAX_USERNAME_LENGTH + TOTAL_ARGON2ID_LENGTH + 1];

    while (fgets(line, sizeof(line), userdata) != NULL)
    {
        char username[MAX_USERNAME_LENGTH];
        char stored_hash[crypto_pwhash_STRBYTES];
        int logged_in;

        if (sscanf(line, "%s %s %d\n", username, stored_hash, &logged_in) != 3)
        {
            continue;
        }

        if (strncmp(user->username, username, MAX_USERNAME_LENGTH) == 0)
        {
            user->logged_in = 0;

            nlock_file(fd_userdata, F_RDLCK);
            fseek(userdata, -strlen(line), SEEK_CUR);
            fprintf(userdata, "%s %s %d\n", user->username, stored_hash, user->logged_in);
            
            nlock_file(fd_userdata, F_UNLCK);
            fclose(userdata);
            close(fd_userdata);
            puts("\x1b[32mLogout successful.\x1b[0m");
            
            return EXIT_SUCCESS;
        }
    }
    
    fclose(userdata);
    close(fd_userdata);
    return EXIT_FAILURE;
}
