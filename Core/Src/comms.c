#include "comms.h"
#include "peripheralconfig.h"

#include "usart.h"

static commsRxCallback_t rxCallback;
extern usart1Buffer[256];

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
 * @brief function for placing data from USART into a comms packet buffer and setting a flag. 
 * TODO: implement!
 */
void commsUSARTCallback()
{
    
}