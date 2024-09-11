#include "../../include/chat/message.h"
#include "../../include/chat/format_msg.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// This is just a default format. You are encouraged to tweak this to your liking.
const char *fmt_string = "%02u:%02u | %s\n%s";

void json_to_msg(char *msg_buffer, char *json_string, const char *fmt_string)
{
    if (sizeof(msg_buffer) > MAX_MESSAGE_LENGTH)
    {
        fprintf(stderr, "\x1b[33mWarning: buffer might be too small. Resize to %zu\x1b[0m\n", MAX_MESSAGE_LENGTH);
    }

    cJSON *json = cJSON_Parse(json_string);
    
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();

        if (error_ptr != NULL)
            fprintf(stderr, "Error before %s\n", error_ptr);
        
        exit(EXIT_FAILURE);
    }

    char msg_content[MAX_CONTENT_LENGTH];
    char sender[MAX_USERNAME_LENGTH];
    uint8_t hour;
    uint8_t minute;

    // TODO: Idk, like, the rest of the function. Procrastinate it to tomorrow, no worries.
     
}
