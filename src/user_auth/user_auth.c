// License: GPL 3.0 or later
/***********************************************************************************************************************
 * user_auth handles secure password storage, login, and logout using libsodium.                                       *
 * This file is part of TCP_CHAT.                                                                                      *
 * Copyright (C) 2023-2024 TaxEvaderKet                                                                                *
 * Full notice can be found in src/app.c                                                                               *
 ***********************************************************************************************************************
*/

#include "../../include/user_auth/user_auth.h"
#include <sodium/crypto_pwhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <openssl/rand.h>

// As I've said before, adjust the file name as needed.
const int EINUSE = 2; 
const char* USERDATA_FILE_NAME = "userdata"; 

/*
 * Utility function. (Un)locks file descriptor. 
*/
void nlock_file(int fd, int mode)
{
    struct flock file_lock;

    /*
     * Brief overview of the different locks, just to make things clearer:
     * F_RDLCK = 0
     * F_WRLCK = 1
     * F_UNLCK = 2 
    */

    if (mode > F_UNLCK || mode < F_RDLCK) 
    {
        fprintf(stderr, "Invalid input.\n");
        exit(EXIT_FAILURE);
    }
    
    file_lock.l_type = mode;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0;

    if (fcntl(fd, F_SETLKW, &file_lock) == -1) 
    {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

/*
 * Utility function, hashes input password for secure storage.
*/
int hash_password(const char *password,
                  char *hash,
                  uint8_t *salt)
{
    if (sodium_init() < 0) 
    {
        fprintf(stderr, "\x1b[31mFailed to initialize libsodium\n\x1b[0m");
        return EXIT_FAILURE;
    }

    randombytes_buf(salt, crypto_pwhash_SALTBYTES);

    if (crypto_pwhash_str(hash, password, strlen(password),
                          crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) 
    {
        fprintf(stderr, "\x1b[31mFailed to hash password\n\x1b[0m");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Takes in user data, hashes the password, and saves username and argon2id digest to a file
 * @returns 1 or EINUSE on error, 0 on success
*/
int signup(User *user)
{
    char hash[crypto_pwhash_STRBYTES];
    uint8_t salt[crypto_pwhash_SALTBYTES];
    int fd_userdata;

    if (hash_password(user->password, hash, salt) != 0)
        return EXIT_FAILURE;
    
    if (access(USERDATA_FILE_NAME, F_OK) != 0) {
        
        if ((fd_userdata = open(USERDATA_FILE_NAME,
                                O_RDWR | O_CREAT,
                                FILE_PERMISSIONS)) == -1) 
        {
            perror("open");
            return EXIT_FAILURE;
        }
        
        FILE *userdata = fdopen(fd_userdata, "w");
        user->logged_in = 0;
        
        nlock_file(fd_userdata, F_WRLCK);
        fprintf(userdata, "%s %s %d\n", user->username, hash, user->logged_in);
        nlock_file(fd_userdata, F_UNLCK);
        
        fprintf(stderr, "\x1b[32mSuccessfully created the user data file and saved login data.\n\x1b[0m");
        OPENSSL_cleanse(user->password, MAX_PASSWORD_LENGTH);
        fclose(userdata);
        return EXIT_SUCCESS;
    }
    
    if ((fd_userdata = open(USERDATA_FILE_NAME,
                            O_APPEND | O_RDWR,
                            FILE_PERMISSIONS)) == -1) 
    {
        perror("open");
        return EXIT_FAILURE;
    }

    FILE *userdata = fdopen(fd_userdata, "a+");
    user->logged_in = 0;
    
    // 4 is equal to all whitespace and the newline at the end.
    char linebuf[MAX_USERNAME_LENGTH + crypto_pwhash_STRBYTES + 4];

    while (fgets(linebuf, sizeof(linebuf), userdata) != NULL)
    {
        char username[MAX_USERNAME_LENGTH];
        char hash[crypto_pwhash_STRBYTES];
        int logged_in;

        if (sscanf(linebuf, "%s %s %d", username, hash, &logged_in) == 3 
            && strncmp(username, user->username, MAX_USERNAME_LENGTH) == 0)
        {
            fprintf(stderr, "\x1b[31m\"%s\" is taken.\n\x1b[0m", user->username);
            return EINUSE;
        }
    }

    nlock_file(fd_userdata, F_WRLCK);
    fprintf(userdata, "%s %s %d\n", user->username, hash, user->logged_in);
    nlock_file(fd_userdata, F_UNLCK);
    
    fprintf(stderr, "\x1b[32mSuccessfully saved login data.\n\x1b[0m");
    OPENSSL_cleanse(user->password, MAX_PASSWORD_LENGTH);
    fclose(userdata);
    return EXIT_SUCCESS;
}

/*
* Reads from a userdata file and compares data from passed in user struct with stored user data, then sets the logged_in flag to action.
* @param [action] whether to log specified user in (1) or out (0)
* @returns 0 on success, 1 on error
*/
int logn(User *user, int action)
{
    int fd_userdata;

    if (action != LOGIN && action != LOGOUT) 
    {
        fprintf(stderr, "Incorrect action specified.\n");
        return EXIT_FAILURE;
    }

    if ((fd_userdata = open(USERDATA_FILE_NAME,
                            O_RDWR, FILE_PERMISSIONS)) == -1) 
    {
        perror("open");
        return EXIT_FAILURE;
    }

    FILE *userdata = fdopen(fd_userdata, "r+");

    if (userdata == NULL) 
    {
        perror("fdopen");
        return EXIT_FAILURE;
    }
   
    char line[MAX_USERNAME_LENGTH + crypto_pwhash_STRBYTES + 4];

    while (fgets(line, sizeof(line), userdata) != NULL)
    {
        char username[MAX_USERNAME_LENGTH];
        char stored_hash[crypto_pwhash_STRBYTES];
        int logged_in;

        if (sscanf(line, "%s %s %d\n", username,
                   stored_hash, &logged_in) != 3) 
        {
            continue;
        }

        if (strncmp(username, user->username, 
                    MAX_USERNAME_LENGTH) != 0) 
        {
            continue;
        }

        if (logged_in == 1 && action == LOGIN) 
        {
            puts("You're already logged in.");
            fclose(userdata);
            return EXIT_FAILURE;
        } 

        if (crypto_pwhash_str_verify(stored_hash, user->password,
                                     strlen(user->password)) == 0) 
        {
            char status[sizeof("Logout")];
            action == LOGOUT
                ? strncpy(status, "Logout", strlen("Logout"))
                : strncpy(status, "Login", strlen("Login"));

            user->logged_in = action;
            nlock_file(fd_userdata, F_WRLCK);
            fseek(userdata, -strlen(line), SEEK_CUR);
            fprintf(userdata, "%s %s %d\n", user->username,
                                            stored_hash, 
                                            user->logged_in);
            nlock_file(fd_userdata, F_UNLCK);
            
            fprintf(stderr, "\x1b[32m%s successful.\n\x1b[0m", status);
            OPENSSL_cleanse(user->password, MAX_PASSWORD_LENGTH);
            fclose(userdata);
            return EXIT_SUCCESS;
        }
    }
   
    fprintf(stderr, "Incorrect username or password.\n");
    OPENSSL_cleanse(user->password, MAX_PASSWORD_LENGTH);
    fclose(userdata);
    return EXIT_FAILURE;
}

void read_password(char *password_buffer,
                   char *prompt,
                   int flags)
{
    EVP_read_pw_string(password_buffer, 
                       MAX_PASSWORD_LENGTH - 1, 
                       prompt, flags);
}
