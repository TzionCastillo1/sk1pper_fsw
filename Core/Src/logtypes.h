#ifndef LOGTYPES_H
#define LOGTYPES_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "errors.h"
#include "stdint.h"

typedef struct {
    uint32_t millis;
    char char_buff[64];
    error_t error;
} log_msg_obj_t;

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** LOGTYPES_H */