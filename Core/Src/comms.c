#include "comms.h"

static bool is_new_message = false;
static mavlink_message_t destination_message;
static mavlink_status_t message_status;

error_t comms_init()
{
    return NO_ERR;
}

void comms_parse_byte(uint8_t byte)
{
    if(mavlink_parse_char(COMMS_DEFAULT_CHANNEL, byte, &destination_message, &message_status))
    {
        is_new_message = true;
    }
    else
    {
        is_new_message = false;
    }

}

comms_status_t comms_is_new_message(mavlink_message_t *message_destination)
{
    return is_new_message;
}