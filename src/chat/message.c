/*********************************************************************************************************
 * message.c: Implementation of the message.h header.                                                    *
 * This file is part of the chat library.                                                                *
 * The purpose of this file is to simplify the process of sending/receiving messages in a custom format. *
 * Copyright (C) 2023 TaxEvaderKet                                                                       *
 * License: GNU GPL 3.0                                                                                  *
 * Full notice can be found in src/app.c                                                                 *
 *********************************************************************************************************
*/

#include "../../include/chat/message.h"

// This is unfinished.

int send_message(User *usr, char *msg_buffer, size_t msg_buffer_len, int fd)
{
    char full_msg_buffer[MAX_MESSAGE_LENGTH];
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    int hours = time_info->tm_hour;
    int minutes = time_info->tm_min;

    snprintf(full_msg_buffer, MAX_MESSAGE_LENGTH, "%02d:%02d | %s\n%s", hours, minutes, usr->username, msg_buffer);

    send(fd, (void *)full_msg_buffer, sizeof(full_msg_buffer), 0);
    return EXIT_SUCCESS;
}

int receive_message(char *msg_buffer, size_t msg_buffer_len, int fd)
{
    return EXIT_SUCCESS;
}
