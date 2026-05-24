#ifndef CLI_CMD_H
#define CLI_CMD_H

#include "cli.h"

extern const cli_cmd_t cmd_table[];

/*-------------Command Handlers---------------*/
void cli_cmd_set(int argc, char **argv);

void cli_cmd_get(int argc, char **argv);

void cli_cmd_help(int argc, char **argv);
/**
 * TODO: Add the rest of CLI cmd function definitions
 */


#endif /* CLI_CMD_H*/