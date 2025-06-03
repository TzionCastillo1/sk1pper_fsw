/**
 * @file comms.c
 * @author Tzion Castillo
 * @brief This module contains the communications task, which is responsible for sending and receiving
 * telemetry.
 * @version 0.1
 * @date 2025-06-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef COMMS_H
#define COMMS_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stdint.h"
#include "stdbool.h"
#include "errors.h"
#include "mavlink.h"
//#include "queue.h"


//QueueHandle_t comms_outgoing_queue;

#define COMMS_DEFAULT_CHANNEL 0

typedef enum comms_status_t
{
    NO_MESSAGE = 0,
    NEW_MESSAGE = 1,
} comms_status_t;

error_t comms_init();

void comms_parse_buffer(uint8_t byte);

comms_status_t comms_is_new_message(mavlink_message_t *message_destination);

/**
 * TODO: write function to pass data to UART driver for write 
 * 
 */

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** COMMS_H */