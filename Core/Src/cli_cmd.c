#include "cli_cmd.h"

const cli_cmd_t cmd_table[] =
{
    {"set", cli_cmd_set, "idk fill this out later"},
    {"get", cli_cmd_get, "idk fill this out later"},
    {"help", cli_cmd_help, "Prints out help messages"},
    {"", 0, ""} //End of table indicator
};

void cli_cmd_set(int argc, char **argv)
{

}

void cli_cmd_get(int argc, char **argv)
{

}

void cli_cmd_help(int argc, char **argv)
{

}