#include "stdint.h"
#include "stdbool.h"
#include "log.h"
#include "leddriver.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "logtypes.h"


extern osEventFlagsId_t ErrorHandle;
extern UART_HandleTypeDef huart1;

/** TODO: I think the LED should be moved to a different module */
static log_level_t log_level;

void log_init()
{
}

void log_event()
{
    osEventFlagsSet(ErrorHandle, EVENT_FLAG_DEBUG);
}

void log_error()
{
    osEventFlagsSet(ErrorHandle, EVENT_FLAG_ERROR);
}

void log_set_verbosity(log_level_t desired_log_level)
{
    log_level = desired_log_level;
}

void startLogTask()
{
    log_msg_obj_t log_msg_obj;
    for (;;)
    {
        /**
         * TODO: Look for messages from a queue.
         * Wait on Messages from the queue.
         * determine message's verbosity, and print to uart sd card as appropriate.
         */

        //Look for message on the queues.
        // The different levels of messages will be hosted on the same Queue:
        /**
         * ErrorQueue - Error Messages that require immediate attention no matter verbosity
         * InfoQueue - Messages that should be logged in normal operation
         * DebugQueue - Messages that should only be logged and written to the console in debug mode
         */
         //osMessageQueueGet(log_msg_queue, &log_msg_obj, NULL, 0U);

        //Check for the verbosity of the message
        osDelay(100);
    }
}


