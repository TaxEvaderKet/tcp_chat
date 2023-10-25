/*************************************************************************************************
 *                                                                                               *
 *   TCP_CHAT: A chatting application which allows users to send messages over a TCP socket.     *
 *   Copyright (C) 2023 TaxEvaderKet                                                             *
 *                                                                                               *
 *   This program is free software: you can redistribute it and/or modify                        *
 *   it under the terms of the GNU General Public License as published by                        *
 *   the Free Software Foundation, either version 3 of the License, or                           *
 *   (at your option) any later version.                                                         *
 *                                                                                               *
 *   This program is distributed in the hope that it will be useful,                             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                              *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                               *
 *   GNU General Public License for more details.                                                *
 *                                                                                               *
 *   You should have received a copy of the GNU General Public License                           *
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.                      *
 *                                                                                               *
 *************************************************************************************************
*/

#include "../include/chat/net.h"
#include <openssl/rand.h>
#define PORT 1337

// I'll probably use this a few times here and there.
void remove_newline(char *s)
{
    s[strcspn(s, "\n")] = '\0';
}

int main(void)
{
    int socket_fd, client_fd;
    if ((socket_fd = init_socket(PORT)) == -1)
    {
        return EXIT_FAILURE;
    }
    
    if ((client_fd = accept_connection(socket_fd)) == -1)
    {
        return EXIT_FAILURE;
    }

    send(client_fd, (void *)"Hello, World!\n", strlen("Hello, World!\n"), 0);
    
    close(socket_fd);
    return EXIT_SUCCESS;
}
