#ifndef SERVO_TYPES_H
#define SERVO_TYPES_H

#include "stm32f4xx_hal.h" 
#include "ppm_types.h"
#include "stdint.h"
#include "stdbool.h"

/**
 * @brief contains calibration info for a servo channel/device.
 * 
 */
typedef struct servo_cal_t
{
    uint16_t min_microseconds;
    uint16_t max_microseconds;
    uint16_t abs_max_angle;
    float trim_angle;
    float lim_min_angle;
    float lim_max_angle;
} servo_cal_t;

/**
 * @brief combines hardware, calibration, and state information into one struct.
 * 
 */
typedef struct servo_t 
{
    ppm_channels_t ppm_channel;
    servo_cal_t servo_cal;
} servo_t;

#endif /* SERVO_TYPES_H */