#include "unity.h"
#include "comms.h"
#include "stdint.h"

static uint8_t send_buffer[256] = {0};
static int16_t message_length; 
static mavlink_message_t rxMsg;
static mavlink_message_t testMsg;

void setUp()
{

    const uint8_t system_id = 42;
    const uint8_t base_mode = 0;
    const uint8_t custom_mode = 0;

    mavlink_msg_heartbeat_pack(
        system_id,
        MAV_COMP_ID_PERIPHERAL,
        &testMsg,
        MAV_TYPE_GENERIC,
        MAV_AUTOPILOT_GENERIC,
        base_mode,
        custom_mode,
        MAV_STATE_STANDBY
    );
    message_length = mavlink_msg_to_send_buffer(send_buffer, &testMsg);
}

void tearDown()
{
    memset(send_buffer, 0, sizeof(send_buffer));
}
/*
void test_commsIncompleteMessage(void)
{
    uint8_t byte_to_read;
    comms_isr_cb(byte_to_read);
}*/

void test_commsInitStartsUartDriver(void)
{
    error_t ret = comms_init();
    TEST_ASSERT_EQUAL(NO_ERR, ret);
}

void test_commsReturnsOkWhenNewMessage(void)
{
    for (int index = 0; index < message_length; index++)
    {
        comms_parse_byte(send_buffer[index]);
    }    

    uint8_t ret = comms_is_new_message(&rxMsg);
    TEST_ASSERT_EQUAL_INT(NEW_MESSAGE, ret);
}

void test_commsReturnsNoWhenNoMessage(void)
{

    for (int index = 0; index < (message_length - 3); index++)
    {
        comms_parse_byte(send_buffer[index]);
    }    

    uint8_t ret = comms_is_new_message(&rxMsg);
    TEST_ASSERT_EQUAL_INT(NO_MESSAGE, ret);

}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_commsInitStartsUartDriver);
    RUN_TEST(test_commsReturnsOkWhenNewMessage);
    RUN_TEST(test_commsReturnsNoWhenNoMessage);
    /**
     * TODO: Implement the test list:
     */

    return UNITY_END();
}