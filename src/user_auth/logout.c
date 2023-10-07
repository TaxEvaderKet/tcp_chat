#include "../../include/user_auth/user_auth.h"

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
