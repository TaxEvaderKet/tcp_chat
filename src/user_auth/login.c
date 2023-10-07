#include "../../include/user_auth/user_auth.h"
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
