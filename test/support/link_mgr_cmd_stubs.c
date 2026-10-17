#include "link_mgr_cmd.h"
#include "stdbool.h"

void lm_cmd_param_list_stub(mavlink_message_t *msg);

// These flags are checked by the tester to verify dispatch occured
bool link_mgr_stub_cmd_param_list_called    = false;

const link_mgr_cmd_t lm_cmd_table[] =
{
    {MAVLINK_MSG_ID_PARAM_REQUEST_LIST, lm_cmd_param_list_stub},
    {LINK_MGR_END_OF_TABLE, 0} // End of Table indicator
};

//Reset all flags - Called from setUp()
void lm_stub_reset()
{
    link_mgr_stub_cmd_param_list_called = false;
}

void lm_cmd_param_list_stub(mavlink_message_t *msg)
{
    link_mgr_stub_cmd_param_list_called = true;
    send_params_sm.idle = false;
}