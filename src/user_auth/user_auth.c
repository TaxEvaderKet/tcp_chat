#include "../../include/user_auth/user_auth.h"
#include "../../include/util/util_macros.h"
#include <sodium/crypto_pwhash.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <openssl/rand.h>
#include <errno.h>

#define WHITESPACE 4

const char *USERDATA_FILE_NAME = "userdata"; 

/**************
 * nlock_file *
 **************
*/
int nlock_file(int fd, int lock_type) {
    struct flock file_lock;

    // F_UNLCK = 2, F_RDLCK = 0 
    if (lock_type > F_UNLCK || lock_type < F_RDLCK) {
        COLOR_MSG(RED, stderr, "Invalid lock type.");
        errno = EINVAL;
        return -1;
    }
    
    file_lock.l_type = lock_type;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0;

    if (fcntl(fd, F_SETLKW, &file_lock) == -1) {
        perror("fcntl");
        return -1;
    }

    return 0;
}

/*****************
 * hash_password *
 *****************
*/
int hash_password(const char *password, char *hash, uint8_t *salt) {
    if (sodium_init() < 0) {
        COLOR_MSG(RED, stderr, "Failed to initialise libsodium.");
        return EXIT_FAILURE;
    }

    randombytes_buf(salt, crypto_pwhash_SALTBYTES);

    if (crypto_pwhash_str(hash, password, strlen(password),
                          crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        COLOR_MSG(RED, stderr, "Failed to hash password.");
        return PWHASH_FAILED;
    }

    return EXIT_SUCCESS;
}

/**********
 * signup *
 **********
*/
int signup(User *user) {
    char hash[crypto_pwhash_STRBYTES];
    uint8_t salt[crypto_pwhash_SALTBYTES];
    int fd_userdata;
    int return_val = EXIT_FAILURE;
    FILE *userdata;

    if (hash_password(user->password, hash, salt) != 0) {
        return return_val;
    }
    
    if (access(USERDATA_FILE_NAME, F_OK) != 0) {
        
        if ((fd_userdata = open(USERDATA_FILE_NAME,
                                O_RDWR | O_CREAT, 
                                FILE_PERMISSIONS)) == -1) {
            perror("open");
            return return_val;
        }
        
        userdata = fdopen(fd_userdata, "w");
        user->logged_in = 0;
        
        nlock_file(fd_userdata, F_WRLCK);
        fprintf(userdata, "%s %s %d\n", user->username, hash, user->logged_in);
        nlock_file(fd_userdata, F_UNLCK);
        
        COLOR_MSG(GREEN, stdout, "Successfully created "
                                "userdata file and saved login credentials.");
        return_val = EXIT_SUCCESS;
        goto exit_signup;
    }
    
    if ((fd_userdata = open(USERDATA_FILE_NAME,
                            O_APPEND | O_RDWR,
                            FILE_PERMISSIONS)) == -1) {
        perror("open");
        return return_val;
    }

    userdata = fdopen(fd_userdata, "a+");
    user->logged_in = 0;
    
    char linebuf[MAX_USERNAME_LENGTH + crypto_pwhash_STRBYTES + WHITESPACE];

    while (fgets(linebuf, sizeof(linebuf), userdata) != NULL) {
        char username[MAX_USERNAME_LENGTH];
        char hash[crypto_pwhash_STRBYTES];
        int logged_in;

        if (sscanf(linebuf, "%s %s %d", username, hash, &logged_in) == 3 
            && strncmp(username, user->username, MAX_USERNAME_LENGTH) == 0) {
            COLOR_MSG(RED, stderr, "Username already in use.");
            return_val = NAME_IN_USE;
            goto exit_signup;
        }
    }

    nlock_file(fd_userdata, F_WRLCK);
    fprintf(userdata, "%s %s %d\n", user->username, hash, user->logged_in);
    nlock_file(fd_userdata, F_UNLCK);
    
    COLOR_MSG(GREEN, stdout, "Successfully saved login data.");
    return_val = EXIT_SUCCESS;

exit_signup:
    OPENSSL_cleanse(user->password, MAX_PASSWORD_LENGTH);
    fclose(userdata);
    return return_val;
}

/*******************
 * login_or_logout *
 *******************
*/
int login_or_logout(User *user, int action) {
    int fd_userdata;
    int return_val = EXIT_FAILURE;

    if (action != LOGIN && action != LOGOUT) {
        COLOR_MSG(RED, stderr, "Invalid action.");
        return return_val;
    }

    if ((fd_userdata = open(USERDATA_FILE_NAME, O_RDWR, FILE_PERMISSIONS)) == -1) {
        perror("open");
        return return_val;
    }

    FILE *userdata = fdopen(fd_userdata, "r+");

    if (userdata == NULL) {
        perror("fdopen");
        return return_val;
    }
   
    char line[MAX_USERNAME_LENGTH + crypto_pwhash_STRBYTES + WHITESPACE];

    while (fgets(line, sizeof(line), userdata) != NULL) {
        char username[MAX_USERNAME_LENGTH];
        char stored_hash[crypto_pwhash_STRBYTES];
        int logged_in;

        if (sscanf(line, "%s %s %d\n", username, stored_hash, &logged_in) != 3) {
            continue;
        }

        if (strncmp(username, user->username, MAX_USERNAME_LENGTH) != 0) {
            continue;
        }

        if (logged_in == 1 && action == LOGIN) {
            COLOR_MSG(RED, stderr, "User already logged in.");
            return_val = ALR_LOGGED_IN;
            goto exit_login_out;
        } 

        if (crypto_pwhash_str_verify(stored_hash, user->password, 
                                     strlen(user->password)) == 0) {
            char status[sizeof("Logout")];
            action == LOGOUT
                ? strncpy(status, "Logout", strlen("Logout"))
                : strncpy(status, "Login", strlen("Login"));

            user->logged_in = action;
            nlock_file(fd_userdata, F_WRLCK);
            fseek(userdata, -strlen(line), SEEK_CUR);
            fprintf(userdata, "%s %s %d\n", 
                    user->username, stored_hash, user->logged_in);
            nlock_file(fd_userdata, F_UNLCK);
            
            COLOR_MSG(GREEN, stdout, "%s successful.", status);
            return_val = EXIT_SUCCESS;
            goto exit_login_out;
        }
    }
    
    COLOR_MSG(RED, stderr, "Incorrect username or password.");
    return_val = INCORRECT_CREDS;
exit_login_out:
    OPENSSL_cleanse(user->password, MAX_PASSWORD_LENGTH);
    fclose(userdata);
    return return_val;
}

void read_password(char *password_buffer, char *prompt, int flags) {
    EVP_read_pw_string(password_buffer, MAX_PASSWORD_LENGTH - 1, prompt, flags);
}

#undef WHITESPACE
