#ifndef FORMAT_MSG_H
#define FORMAT_MSG_H

extern const char *fmt_string;

void json_to_msg(char *msg_buffer, char *json_string, const char *fmt_string);

#endif // !FORMAT_MSG_H
