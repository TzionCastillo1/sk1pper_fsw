#ifndef LINK_MGR_CMD_H
#define LINK_MGR_CMD_H

#include "link_mgr.h"

extern const link_mgr_cmd_t lm_cmd_table[];

/*-------------Command Handlers---------------*/
void lm_cmd_param_list(mavlink_message_t *msg);
void lm_cmd_param_set(mavlink_message_t *msg);
#endif /** LINK_MGR_CMD_H */