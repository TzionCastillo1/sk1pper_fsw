#ifndef COMMS_H
#define COMMS_H

#include "stdint.h"
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stdbool.h"

/** Flag describing if a new message has been received */
bool newMessage = false; 

typedef void (*commsRxCallback_t)(char* data, uint8_t dataLength);

error_t commsInit(commsRxCallback_t callback);

error_t commsStart();

error_t commsStop();

error_t commsWrite();

uint8_t commsReadMessage();

error_t commsSetRxCallback();

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** COMMS_H */