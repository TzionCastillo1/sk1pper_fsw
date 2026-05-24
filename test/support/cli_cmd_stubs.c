#include "cli_cmd.h"
#include "stdbool.h"

void cli_cmd_set_stub(int argc, char **argv);
void cli_cmd_get_stub(int argc, char **argv);
void cli_cmd_help_stub(int argc, char **argv);
// These flags are checked by tests to verify dispatch occurred
bool cli_stub_set_called    = false;
bool cli_stub_get_called    = false;
bool cli_stub_help_called   = false;
bool cli_stub_arm_called    = false;
bool cli_stub_disarm_called = false;

// Reset all flags — called from setUp()
void cli_stub_reset(void)
{
    cli_stub_set_called    = false;
    cli_stub_get_called    = false;
    cli_stub_help_called   = false;
    cli_stub_arm_called    = false;
    cli_stub_disarm_called = false;
}

const cli_cmd_t cmd_table[] =
{
    {"set", cli_cmd_set_stub, "idk fill this out later"},
    {"get", cli_cmd_get_stub, "idk fill this out later"},
    {"help", cli_cmd_help_stub, "Prints out help messages"},
    {"", 0, ""} //End of table indicator
};


void cli_cmd_set_stub(int argc, char **argv)
{
    cli_stub_set_called = true;

}

void cli_cmd_get_stub(int argc, char **argv)
{
    cli_stub_get_called = true;

}

void cli_cmd_help_stub(int argc, char **argv)
{
    cli_stub_help_called = true;

}