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
 * Takes in user data, hashes the password, and saves username, password hash, and salt to a file
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
    
    if (access("userdata", F_OK) != 0)
    {
        FILE *userdata = fopen("userdata", "w");
        
        fprintf(userdata, "%s %s\n", user->username, hash);
        puts("\x1b[32mSuccessfully created the userdata file and saved user data.\x1b[0m");
        return EXIT_SUCCESS;
    }

    FILE *userdata = fopen("userdata", "a");

    fprintf(userdata, "%s %s\n", user->username, hash);
    puts("\x1b[32mSuccessfully saved user data.\x1b[0m");

    fclose(userdata);
    return EXIT_SUCCESS;
}

/*
 * Reads from a userdata file and compares data from passed in user struct with stored user data, then sets the logged_in flag to 1 (true).
 * @param pointer to a user struct 
 * @returns 0 on success, 1 on error
*/
int login(User *user)
{
    FILE *userdata = fopen("userdata", "r");
    
    if (userdata == NULL)
    {
        fprintf(stderr, "\x1b[31mCould not open userdata file.\n\x1b[0m");
        return EXIT_FAILURE;
    }
    
    char line[MAX_USERNAME_LENGTH + TOTAL_ARGON2ID_LENGTH + 1];
    
    while (fgets(line, sizeof(line), userdata) != NULL)
    {
        char username[MAX_USERNAME_LENGTH];
        char stored_hash[crypto_pwhash_STRBYTES];

        if (sscanf(line, "%s %s\n", username, stored_hash) != 2)
        {
            continue;
        }

        if (strncmp(username, user->username, MAX_USERNAME_LENGTH) != 0)
        {
            continue;
        }

        if (crypto_pwhash_str_verify(stored_hash, user->password, strlen(user->password)) == 0)
        {
            puts("\x1b[32mLogin successful.\x1b[0m");
            user->logged_in = 1;
            fclose(userdata);
            return EXIT_SUCCESS;
        }
    }
    
    fclose(userdata);
    fprintf(stderr, "Incorrect username or password.\n");
    return EXIT_FAILURE;
}
