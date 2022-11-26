#ifndef _SHELL_PARSER_H_
#define _SHELL_PARSER_H_

void parse_command();
int has_param(int cmd_id);
char *get_param(char sign);

#endif /* !_SHELL_PARSER_H_ */