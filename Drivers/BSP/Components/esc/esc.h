#ifndef ESC_H
#define ESC_H

#include "stdint.h"
#include "ppm_types.h"

typedef struct esc_t
{
    ppm_channels_t ppm_channel;
    uint16_t min_microseconds;
    uint16_t max_microseconds;
} esc_t;

/**
 * @brief Initialize the ESC object
 * 
 * @param esc esc to be initialized
 * @return int 
 */
int esc_init(esc_t *esc);

/**
 * @brief Enable the ESC object
 * 
 * @param esc esc to be enabled
 * @return int 
 */
int esc_enable(esc_t *esc);

/**
 * @brief Disable the ESC object
 * 
 * @param esc esc to be disabled
 * @return int 
 */
int esc_disable(esc_t *esc);

/**
 * @brief Perform ESC calibration routine. This can only be performed while connected to debug UART 
 * 
 * @param esc esc to be calibrated
 * @return int 
 */
int esc_cal(esc_t *esc);

/**
 * @brief Set the ESC throttle percentage.
 * 
 * @param esc esc to be set
 * @param throttle Acceptable range is 0 -> 1.0, where 0.5 is 50%
 * @return int 
 */
int esc_set_throttle(esc_t *esc, float throttle);

/**
 * @brief Set the ESC PPM in microseconds directly.
 * 
 * @param esc esc to be set
 * @param microseconds Acceptable range is 
 * @return int 
 */
int esc_set_microseconds(esc_t *esc, uint16_t microseconds);

/**
 * @brief Call to update the signal being sent to the esc
 * with the latest throttle setting.
 * 
 * @param esc 
 * @return int 
 */
int esc_update(esc_t *esc);



#endif //ESC_H
