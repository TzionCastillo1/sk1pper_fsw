#include "cli_cmd.h"
#include "printf/printf.h"

const cli_cmd_t cmd_table[] =
{
    {"set", cli_cmd_set, "idk fill this out later"},
    {"get", cli_cmd_get, "idk fill this out later"},
    {"help", cli_cmd_help, "Prints out help messages"},
    {"", 0, ""} //End of table indicator
};

void cli_cmd_set(int argc, char **argv)
{
    printf_("setting...\r\n");
}

void cli_cmd_get(int argc, char **argv)
{
    printf_("getting...\r\n");
}

void cli_cmd_help(int argc, char **argv)
{
    for (int cmd_idx = 0; cmd_table[cmd_idx].cmd[0] != '\0'; cmd_idx++)
    {
        printf_("%s:        %s\r\n", cmd_table[cmd_idx].cmd, cmd_table[cmd_idx].helptext);
    }
}