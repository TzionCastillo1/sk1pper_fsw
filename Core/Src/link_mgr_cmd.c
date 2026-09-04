#include "link_mgr_cmd.h"
#include "errors.h"
#include "param_mgr.h"
#include "stm32f405_SpeedyBee.h"

static char uart_txbuff[256];

const link_mgr_cmd_t lm_cmd_table[] =
{
    {MAVLINK_MSG_ID_PARAM_REQUEST_LIST, lm_cmd_param_list},
    {MAVLINK_MSG_ID_PARAM_SET, lm_cmd_param_set},
    {LINK_MGR_END_OF_TABLE, 0}
};

void lm_cmd_param_set(mavlink_message_t *msg)
{
    uint8_t system_id = 42;
    uint8_t base_mode = 0;
    uint8_t custom_mode = 0;
    float param_val;
    uint32_t param_idx;
    mavlink_message_t message;

    //Decode and update param internally
    mavlink_param_set_t param_cmd;
    mavlink_msg_param_set_decode(msg, &param_cmd);
    param_mgr_set(param_cmd.param_id, param_cmd.param_value);

    //Confirm new param value by sending back to GCS
    param_mgr_get(param_cmd.param_id, &param_val);
    param_mgr_find(param_cmd.param_id, &param_idx);
    mavlink_msg_param_value_pack_chan(system_id,
                                    MAV_COMP_ID_AUTOPILOT1,
                                    MAVLINK_COMM_0,
                                    &message,
                                    param_cmd.param_id,
                                    param_val,
                                    MAV_PARAM_TYPE_REAL32,
                                    send_params_sm.param_count,
                                    param_idx);
    //need to come up with a better solution for this buffer. Maybe a common buffer should
    //live in the bsp module?
    const int len = mavlink_msg_to_send_buffer(uart_txbuff, &message);
    int status = BSP_link_mgr_tx_func(uart_txbuff, len);
}

void lm_cmd_param_list(mavlink_message_t *msg)
{
    send_params_sm.idle = false;
}