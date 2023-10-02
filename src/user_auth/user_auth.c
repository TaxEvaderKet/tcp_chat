#include "../../include/user_auth/user_auth.h"

// Helper function. No documentation necessary.
int hash_password(const char *password, char *hash, uint8_t *salt)
{
    if (sodium_init() < 0)
    {
        puts("Failed to initialize libsodium");
        return EXIT_FAILURE;
    }

    randombytes_buf(salt, sizeof(salt));

    if (crypto_pwhash_str((char *)hash, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    {
        puts("Failed to hash password");
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
    char hash[HASH_LENGTH];
    uint8_t salt[SALT_LENGTH];
    char hashed_password[HASH_LENGTH + 1]; 

    if (hash_password(user->password, hash, salt) != 0)
    {
        fprintf(stderr, "\x1b[31mfailed to hash password\x1b[0m\n");
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
        fprintf(stderr, "\x1b[31mCould not open userdata file.\x1b[0m");
        return EXIT_FAILURE;
    }
    
    char line[MAX_USERNAME_LENGTH + HASH_LENGTH + 1];

    while (fgets(line, sizeof(line), userdata) != NULL)
    {
        char username[MAX_USERNAME_LENGTH + 1];
        char stored_hash[HASH_LENGTH];

        if (sscanf(line, "%s %s\n", username, stored_hash) != 3)
        {
            continue;
        }

        if (strcmp(username, user->username) != 0)
        {
            continue;
        }

        if (crypto_pwhash_str_verify(stored_hash, user->password, strlen(user->password)) == 0)
        {
            puts("\x1b[32mLogin successful.\x1b[0m");
            fclose(userdata);
            return EXIT_SUCCESS;
        }
    }
    
    fclose(userdata);
    fprintf(stderr, "Incorrect username or password.\n");
    return EXIT_FAILURE;
}
