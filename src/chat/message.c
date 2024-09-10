// License: GPL 3.0 or later
/********************************************************************************************************
 * This is a utility for sending and receiving message contents in JSON. Formatting occurs separately.  *
 * Copyright (C) 2023-2024 TaxEvaderKet                                                                 *
 * Full notice can be found in src/app.c                                                                *
 ********************************************************************************************************
*/

#include "../../include/chat/message.h"
#include <time.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>

// Adjust these values according to your needs; they're meant to be modified.
// These are just defaults.
const size_t FMT_CHARS = 9;
const size_t MAX_CONTENT_LENGTH = 2048;

// 4 = hours and minutes, 61 = JSON string chars
// username accounted for in MAX_MESSAGE_LENGTH, see message.h for details.
const size_t JSON_STRING_LENGTH = MAX_MESSAGE_LENGTH + 4 + 61;

/*
 * Utility function. Takes in message components and puts them into a JSON string.
 * Time is always displayed in 24-hour format. So, to all 12-hour clock users: cope.
*/
void format_msg_to_json(char *msg_content,
                        char *username,
                        int hh, int mm,
                        char *message_buffer, size_t bufsize)
{
    if (bufsize < JSON_STRING_LENGTH)
    {
        fprintf(stderr, "\x1b[33mWarning: buffer smaller than\
                        recommended size of %zu\n\x1b[0m",
                JSON_STRING_LENGTH);
    }

    char json_string[JSON_STRING_LENGTH];

    snprintf(json_string, sizeof(json_string),
             "{\
                \"msg_content\": \"%s\",\
                \"sender\": \"%s\",\
                \"hour\": \"%02d\",\
                \"minute\": \"%02d\"\
            }",
            msg_content, username, hh, mm);

    strncpy(message_buffer, json_string, JSON_STRING_LENGTH);
}

/*
 * Sends the components of a message in JSON format to specified file descriptor.
 * @param [usr] Required to display the sender's username in message.
 * Rest: self-explanatory. 
 * Returns status 1 (failure) or 0 (success).
*/
int send_message(User *usr, char *msg_content, int socket_fd)
{
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    int hours = time_info->tm_hour;
    int minutes = time_info->tm_min;
    char stringified_components[JSON_STRING_LENGTH];
    
    format_msg_to_json(msg_content, usr->username,
                       hours, minutes,
                       stringified_components,
                       sizeof(stringified_components));

    if (send(socket_fd, stringified_components,
             strlen(stringified_components), 0) == -1)
    {
        perror("send");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Simply a wrapper for recv. Yup. All there is to it.
*/
int receive_message(char *components_buffer, size_t bufsize, int socket_fd)
{
    if (bufsize < JSON_STRING_LENGTH)
        fprintf(stderr, "\x1b[33mWarning: buffer might be too small.\
                        Consider resizing the buffer to %zu.\n\x1b[0m", JSON_STRING_LENGTH);

    ssize_t bytes_received = recv(socket_fd,
                                  components_buffer,
                                  sizeof(components_buffer), 0);

    if (bytes_received < 0) {
        perror("recv");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
