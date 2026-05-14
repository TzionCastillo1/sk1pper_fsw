#ifndef PPM_TYPES_H
#define PPM_TYPES_H

#include "stm32f4xx_hal.h" 
#include "stdint.h"
#include "stdbool.h"

typedef enum ppm_channels_t
{
    PPM_CHANNEL_1 = 0,
    PPM_CHANNEL_2,
    PPM_CHANNEL_3,
    PPM_CHANNEL_4,
    PPM_CHANNEL_5,
    PPM_MAX_CHANNELS
} ppm_channels_t;

/**
 * @brief contains hardware configuration info for a ppm channel
 * 
 */
typedef struct ppm_HW_config_t
{
    TIM_HandleTypeDef *htimx;
    uint32_t tim_channel;
    GPIO_TypeDef *ppm_port;
    uint16_t ppm_pin;
} ppm_HW_config_t;


/**
 * @brief contains state data for a ppm channel
 * 
 */
typedef struct ppm_state_t
{
    bool is_initialized;
    bool is_enabled;
    uint16_t current_microseconds;
    uint16_t next_microseconds;
} ppm_state_t;

/**
 * @brief combines hardware, calibration, and state information into one struct.
 * 
 */
typedef struct ppm_t 
{
    ppm_HW_config_t ppm_hw_config;
    ppm_state_t ppm_state;
} ppm_t;

#endif /* PPM_TYPES_H */