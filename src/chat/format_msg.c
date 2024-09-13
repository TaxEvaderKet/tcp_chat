#include "../../include/chat/message.h"
#include "../../include/chat/format_msg.h"
#include "../../include/util/util_macros.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// This is just a default format. You are encouraged to tweak this to your liking.
const char *fmt_string = "%02u:%02u | %s\n%s";

void json_to_msg(char *msg_buffer, size_t bufsize, 
                 char *json_string, const char *fmt_string)
{
    if (bufsize < MAX_MESSAGE_LENGTH)
    {
        COLOR_MSG(RED, stderr, "Message buffer is too small.");
    }

    cJSON *json = cJSON_Parse(json_string);
    
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();

        if (error_ptr != NULL)
            COLOR_MSG(RED, stderr, "Error before: %s\n", error_ptr);

        exit(EXIT_FAILURE);
    }

    char msg_content[MAX_CONTENT_LENGTH];
    char sender[MAX_USERNAME_LENGTH];
    uint8_t hour;
    uint8_t minute;

    cJSON *content = cJSON_GetObjectItem(json, "msg_content");
    cJSON *usr = cJSON_GetObjectItem(json, "sender");
    cJSON *hr = cJSON_GetObjectItem(json, "hour");
    cJSON *min = cJSON_GetObjectItem(json, "minute");

    snprintf(msg_content, sizeof(msg_content), "%s", content->valuestring);
    snprintf(sender, sizeof(sender), "%s", usr->valuestring);
    hour = hr->valueint;
    minute = min->valueint;

    snprintf(msg_buffer, bufsize, 
             fmt_string, hour, minute, sender, msg_content);

    cJSON_Delete(json);
}
