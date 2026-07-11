#include "cli_cmd.h"
#include "printf/printf.h"
#include "errors.h"
#include "string.h"
#include "stdlib.h"
#include "param_mgr.h"

const cli_cmd_t cmd_table[] =
{
    {"set", cli_cmd_set, "idk fill this out later"},
    {"get", cli_cmd_get, "idk fill this out later"},
    {"save", cli_cmd_save, "Persist current parameters to SD card."},
    {"help", cli_cmd_help, "Prints out help messages"},
    {"", 0, ""} //End of table indicator
};

void cli_cmd_set(int argc, char **argv)
{
    if (argc != 3)
    {
        printf_("error: %i\r\n", ERROR_CLI_INVALID_ARGS);
    }
    else
    {
        float val = strtof(argv[2], NULL);
        error_t res = param_mgr_set(argv[1], val);
        if(res != ERROR_OK)
        {
            printf_("error: %i\r\n", res);
        }
    }

}

void cli_cmd_get(int argc, char **argv)
{
    //printf_("getting...\r\n");
    if (argc != 2)
    {
        printf_("error: %i\r\n", ERROR_CLI_INVALID_ARGS);
    }
    else
    {
        float val;
        error_t res = param_mgr_get(argv[1], &val);
        if(res == ERROR_OK)
        {
            printf_("%f\r\n", val);
        }
        else
        {
            printf_("error: %i\r\n", res);
        }
    }
}

void cli_cmd_save(int argc, char **argv)
{
    error_t res = ERROR_OK;
    if (argc != 1)
    {
        res = ERROR_CLI_INVALID_ARGS;
        printf_("error: %i\r\n", res);
    }
    else
    {
        res = param_mgr_save();
        if (res != ERROR_OK)
        {
            printf_("error: %i\r\n", res);
        }
    }
}

void cli_cmd_help(int argc, char **argv)
{
    for (int cmd_idx = 0; cmd_table[cmd_idx].cmd[0] != '\0'; cmd_idx++)
    {
        printf_("%s:        %s\r\n", cmd_table[cmd_idx].cmd, cmd_table[cmd_idx].helptext);
    }
}