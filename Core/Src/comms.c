#include "comms.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

static bool is_new_message = false;
static mavlink_message_t mavlink_message;
static mavlink_status_t message_status;
static UART_HandleTypeDef *commsUART;



error_t comms_init(UART_HandleTypeDef *huart)
{
    /**
     * TODO: init the UART driver 
     * 
     */
    return NO_ERR;
}

void comms_parse_byte(uint8_t byte)
{
    if(mavlink_parse_char(COMMS_DEFAULT_CHANNEL, byte, &mavlink_message, &message_status))
    {
       //dispatcher_enqueue(&mavlink_message); 
    }
    else
    {
        is_new_message = false;
    }
}

/**
 * TODO: The transmission should pull the oldest message from a transmission queue
 */
void comms_transmit_message(mavlink_message_t *mavlink_message)
{
    /** TODO: Tie to the UART driver */
    //HAL_UART_Transmit(commsUART, )
}

void startCommsTask(void)
{
    for(;;)
    {

    }
}