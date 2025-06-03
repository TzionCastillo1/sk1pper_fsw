#include "stdint.h"
#include "stdbool.h"
#include "debug.h"
#include "leddriver.h"
#include "cmsis_os.h"

#define DEBUG_LED_PIN GPIO_PIN_13

extern osEventFlagsId_t ErrorHandle;

static leddriver_handle_t debug_led_handle;

void debug_init()
{
    leddriver_init(&debug_led_handle, GPIOA, DEBUG_LED_PIN);
}

void debug_flash()
{
    osEventFlagsSet(ErrorHandle, EVENT_FLAG_ERROR);
}

void debug_error()
{
    osEventFlagsSet(ErrorHandle, EVENT_FLAG_DEBUG);
}

void startDebugTask()
{
    /**
     * TODO: If the flash() function has been called, the LED should just pulse once
     * If the error() function has been called, the LED should blink indefinitely 
     * 
     */
    for (;;)
    {
        osEventFlagsWait(ErrorHandle, (EVENT_FLAG_ERROR | EVENT_FLAG_DEBUG), osFlagsWaitAny, osWaitForever); /** EVENT_FLAG_ERROR and EVENT_FLAG_DEBUG found in FreeRTOSConfig.h */
        /** TODO: Add event reader/queue */
        if ((osEventFlagsGet(ErrorHandle) & EVENT_FLAG_ERROR) == EVENT_FLAG_ERROR)
        {
            leddriver_toggle(&debug_led_handle);
            osDelay(250);
        }
        else
        {   
            leddriver_set(&debug_led_handle);
            osDelay(500);
            leddriver_reset(&debug_led_handle);
            osEventFlagsClear(ErrorHandle, EVENT_FLAG_DEBUG); 
        }
    }
}


