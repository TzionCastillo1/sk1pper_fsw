#include "unity.h"

#include "link_mgr.h"
#include "link_mgr_cmd_stubs.h"
#include "stdint.h"
#include "ringbuff.h"

#include "mock_link_mgr_cmd.h"
#include "mock_sensor_mgr.h"
#include "mock_param_mgr.h"

TEST_SOURCE_FILE("Core/Src/link_mgr_cmd.c")
TEST_SOURCE_FILE("Core/Src/ringbuff.c")

static uint8_t send_buffer[256] = {0};
static int16_t message_length; 
static mavlink_message_t rxMsg;
static mavlink_message_t testMsg;
static uint32_t msgid = 0;

error_t stub_tx(char *data, uint16_t len)
{
    mavlink_status_t status;
    for (int idx = 0; idx < len; idx++)
    {
        if(mavlink_parse_char(MAVLINK_COMM_1, data[idx], &rxMsg, &status))
        {
            msgid = rxMsg.msgid;
        }

    }
    //expected msgid from mavlink docs:
    //https://mavlink.io/en/messages/common.html#PARAM_VALUE
}

void setUp()
{
    lm_stub_reset();
    link_mgr_init(&stub_tx);
}

void tearDown()
{
    memset(send_buffer, 0, sizeof(send_buffer));
}

void test_link_mgr_invokes_param_list()
{
    mavlink_msg_param_request_list_pack_chan(
        0,
        MAV_COMP_ID_MISSIONPLANNER,
        MAVLINK_COMM_0,
        &testMsg,
        0,
        MAV_COMP_ID_ALL
    );

    int len = mavlink_msg_to_send_buffer(send_buffer, &testMsg);
    for (int byte_idx = 0; byte_idx < len; byte_idx++)
    {
        link_mgr_byte_received(send_buffer[byte_idx]);
    }

    link_mgr_rx_msg_process();

    link_mgr_send_params(10000);

    TEST_ASSERT_TRUE(link_mgr_stub_cmd_param_list_called);
    TEST_ASSERT_EQUAL_UINT32(20, rxMsg.msgid);

}
