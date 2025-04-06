#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stdint.h"
#include "errors.h"

/**
 * @brief structure to hold an incoming message.
 * @param data pointer to   
 * 
 */
typedef struct logData_t
{
    char *data;
    uint16_t dataLength;
    char source[16];
} logData_t;

error_t logInit();

error_t logStart();

error_t logStop();

error_t log();


#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** LOGGER_H */