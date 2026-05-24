#ifndef CLI_CMD_STUB_H
#define CLI_CMD_STUB_H

#include "stdbool.h"

extern bool cli_stub_set_called;
extern bool cli_stub_get_called;
extern bool cli_stub_help_called;
extern bool cli_stub_arm_called;
extern bool cli_stub_disarm_called;

void cli_stub_reset(void);

#endif /* CLI_CMD_STUB_H */