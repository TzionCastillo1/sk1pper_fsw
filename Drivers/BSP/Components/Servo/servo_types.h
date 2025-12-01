#ifndef SERVO_TYPES_H
#define SERVO_TYPES_H

#include "stm32f4xx_hal.h" 
#include "stdint.h"
#include "stdbool.h"

typedef enum servo_channels_t
{
    SERVO_CHANNEL_1 = 0,
    SERVO_CHANNEL_2,
    SERVO_CHANNEL_3,
    SERVO_CHANNEL_4,
    SERVO_MAX_CHANNELS
} servo_channels_t;

/**
 * @brief contains hardware configuration info for a servo channel
 * 
 */
typedef struct servo_HW_config_t
{
    TIM_HandleTypeDef *htimx;
    uint32_t tim_channel;
    GPIO_TypeDef *servo_port;
    uint16_t servo_pin;
} servo_HW_config_t;

/**
 * @brief contains calibration info for a servo channel/device.
 * 
 */
typedef struct servo_cal_t
{
    uint16_t min_microseconds;
    uint16_t max_microseconds;
    uint16_t abs_max_angle;
    float lim_min_angle;
    float lim_max_angle;
} servo_cal_t;

/**
 * @brief contains state data for a servo channel
 * 
 */
typedef struct servo_state_t
{
    bool is_initialized;
    bool is_enabled;
    uint16_t current_microseconds;
    uint16_t next_microseconds;
} servo_state_t;
/**
 * @brief combines hardware, calibration, and state information into one struct.
 * 
 */
typedef struct servo_t 
{
    servo_HW_config_t servo_hw_config;
    servo_cal_t servo_cal;
    servo_state_t servo_state;
} servo_t;

#endif /* SERVO_TYPES_H */