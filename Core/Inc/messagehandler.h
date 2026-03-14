/**
 * @file messagehandler.h
 * @author Tzion Castillo (tzionmcastillo@gmail.msg)
 * @brief Mavlink message handling & routing
 * @version 0.1
 * @date 2026-01-10
 * 
 *  This module is responsible for taking Mavlink messages from the telemetry manager, decoding them,
 *  and dispatching them as appropriate.
 * 
 */

#ifndef MSG_HANDLER_H
#define MSG_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "mavlink.h"

#define MSG_QUEUE_LEN 8

/** =========== Public Types =========== */
typedef enum
{
    MSG_HANDLER_STATUS_OK = 0,
    MSG_HANDLER_STATUS_ERROR,
    MSG_HANDLER_STATUS_UNSUPPORTED,
} Msg_Handler_Status_t;


/**
 * @brief Initialize the message handler module
 * 
 * @return  MSG_HANDLER_STATUS_OK if succesful
 *          MSG_HANDLER_STATUS_ERROR if unsuccesful
 */
Msg_Handler_Status_t MsgHandler_init();

/**
 * @brief Start the message handler module
 * 
 * @return  MSG_HANDLER_STATUS_OK if succesful
 *          MSG_HANDLER_STATUS_ERROR if unsuccesful
 */
Msg_Handler_Status_t MsgHandler_start();

/**
 * @brief Stop the message handler module 
 * 
 */
void MsgHandler_stop();

/**
 * @brief Update the message handler module
 * 
 * Method to be called from the Message Handler Task 
 * 
 * @return  MSG_HANDLER_STATUS_OK if succesful
 *          MSG_HANDLER_STATUS_ERROR if unsuccesful
 */
Msg_Handler_Status_t Msg_Handler_update();

/**
 * @brief Add a state message to the outgoing queue 
 * 
 * @return  MSG_HANDLER_STATUS_OK if succesful
 *          MSG_HANDLER_STATUS_ERROR if unsuccesful
 */
Msg_Handler_Status_t Msg_Handler_send_state();

/**
 * @brief Call when an incoming message has been detected
 * 
 * Can be called from the UART ISR to signal for processing to begin.
 * This should not do any processing, just sets a flag for the task 
 * to process.
 * 
 */
void Msg_Handler_msg_received();


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MSG_HANDLER_H