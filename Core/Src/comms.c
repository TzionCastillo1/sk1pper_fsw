#include "comms.h"
#include "peripheralconfig.h"

#include "usart.h"

static commsRxCallback_t rxCallback;

comms_packet_t comms_packet;

void commsUSARTCallback();


error_t commsInit(commsRxCallback_t callback)
{
    rxCallback = callback;
    /** defined in peripheralconfig.h might get rid of this later, not sure we need this configurability*/
    #ifdef TELEM_UART_1
    MX_USART1_UART_Init();
    USART1registerCallback(commsUSARTCallback);
    #endif /** TELEM_UART_1 */

}

/**
 * @brief start UART1, triggering an interrupt anytime a byte is received. 
 * 
 * @return error_t 
 */
error_t commsStart()
{
    HAL_UART_Receive_IT(&huart1, usart1Buffer, 1);
}

/**
 * @brief function for placing data from USART into a comms packet buffer and setting a flag. 
 * TODO: implement!
 */
void commsUSARTCallback()
{
    if(commsDecodePacket(byte, &comms_packet))
    {
        newMessage = true;
    }
    HAL_UART_Receive_IT(&huart1, usart1Buffer, 1);
}