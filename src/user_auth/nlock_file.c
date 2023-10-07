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
