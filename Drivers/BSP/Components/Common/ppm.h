#ifndef PPM_H
#define PPM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ppm_types.h"
#include "stdint.h"

extern uint32_t SystemCoreClock;
#define PPM_FREQUENCY             50U
#define PPM_PERIOD_US             (1000000 / PPM_FREQUENCY)
//Timer tick period (us) = prescaler * 1000000/clock frequency 
#define PPM_TICKS_PER_US          (7000.0F / 20000.0F)

/*
ticks per microseconds = t/us
I have clock frequency, prescaler. Timer tick frequency = clock frequency/prescaler.
Timer tick period = prescaler/clock frequency
Timer tick period (us) = prescaler * 1000000/clocl frequency. This is period of clock pulse, not period of pwm signal 
Ticks = pulse (ms) * period (ticks) / period (ms)
Ticks = pulse (us) * period (ticks) / period (us)
*/

/**
 * @brief initialize the desired ppm channel. Return an error if init unsuccesful
 * @param ppm_channel ppm channel to be initialized.
 * @return int 
 */
int ppm_init(ppm_channels_t ppm_channel);

/**
 * @brief enable the desired channel. Return an error if enable is unsuccesful
 * @param ppm_channel ppm channel to be enabled
 * @return int 
 */
int ppm_enable(ppm_channels_t ppm_channel);

/**
 * @brief enable all ppm channels. Return an error if enable is unsuccesful
 * 
 * @return int 
 */
int ppm_enable_all();

/**
 * @brief disable the desired channel. Return an error if enable is unsuccesful
 * @param ppm_channel ppm channel to be disabled
 * @return int 
 */
int ppm_disable(ppm_channels_t ppm_channel);

/**
 * @brief disable all ppm channels. Return an error if disable is unsuccesful
 * 
 * @return int 
 */
int ppm_disable_all();

/**
 * @brief set the pulse width in microseconds for the desired ppm channel. Return an error if unsuccseful.
 * 
 * @param ppm_channel ppm channel to be set to desired angle 
 * @param microseconds desired pulse width in microseconds
 * @return int 
 */
int ppm_set_microseconds(ppm_channels_t ppm_channel, float microseconds);

/**
 * @brief update the command to the channel with the most recent value. Return an error if 
 * unsuccesful
 * 
 * @param ppm_channel 
 * @return int 
 */
int ppm_update(ppm_channels_t ppm_channel);


#ifdef __cplusplus
}
#endif

#endif /** PPM_H */