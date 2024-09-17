/*************************************************************************************************
 *                                                                                               *
 *   TCP_CHAT: A chatting application which allows users to send messages over a TCP socket.     *
 *   Copyright (C) 2023-2024 TaxEvaderKet                                                        *
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

#include "../include/user_auth/user_auth.h"
#include <openssl/rand.h>
#include <string.h>

#define PORT 1337

void remove_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

int main(int argc, char *argv[]) {
    User usr;

    printf("Enter username or something: ");
    fgets(usr.username, MAX_USERNAME_LENGTH, stdin);
    read_password(usr.password, "Password: ", 0);

    remove_newline(usr.username);

    if (signup(&usr) == EXIT_SUCCESS) {
        OPENSSL_cleanse(usr.password, MAX_PASSWORD_LENGTH);
    }


    User new_user;

    printf("Enter username again: ");
    fgets(new_user.username, MAX_USERNAME_LENGTH, stdin);
    read_password(new_user.password, "Password: ", 0);

    remove_newline(new_user.username);

    if (login_or_logout(&new_user, LOGIN) == EXIT_SUCCESS) {
        OPENSSL_cleanse(usr.password, MAX_PASSWORD_LENGTH);
    }

    return EXIT_SUCCESS;
}
