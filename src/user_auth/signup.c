#include "../../include/user_auth/user_auth.h"

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
