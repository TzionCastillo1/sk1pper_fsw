#include "messagehandler.h"

/** ========== Private Prototypes ======== **/
Msg_Handler_Status_t MsgHandler_dispatch(mavlink_message_t msg);

typedef struct
{
    uint8_t buff[MSG_QUEUE_LEN * MAVLINK_MAX_PACKET_LEN];
    uint8_t count;
    uint8_t index;
} msg_queue_t;

/** ========== Private Variables ======== **/
static uint8_t msg_queue_count;


uint8_t msg_queue_buff[MSG_QUEUE_LEN * MAVLINK_MAX_PACKET_LEN];



Msg_Handler_Status_t MsgHandler_init()
{
    Msg_Handler_Status_t status = MSG_HANDLER_STATUS_ERROR;

    return status;
}

Msg_Handler_Status_t MsgHandler_start()
{
    Msg_Handler_Status_t status = MSG_HANDLER_STATUS_ERROR;

    return status;
}

void MsgHandler_stop()
{
}

Msg_Handler_Status_t Msg_Handler_update()
{
    Msg_Handler_Status_t status = MSG_HANDLER_STATUS_ERROR;

    return status;
}

Msg_Handler_Status_t Msg_Handler_send_state()
{
    Msg_Handler_Status_t status = MSG_HANDLER_STATUS_ERROR;

    return status;
}

void Msg_Handler_msg_received()
{
    msg_queue_count++;
}

Msg_Handler_Status_t MsgHandler_dispatch(mavlink_message_t msg);