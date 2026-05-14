#ifndef SERVO_H
#define SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "servo_types.h"
#include "stdint.h"

extern uint32_t SystemCoreClock;
#define SERVO_FREQUENCY             50U
#define SERVO_PERIOD_US             (1000000 / SERVO_FREQUENCY)
//Timer tick period (us) = prescaler * 1000000/clock frequency 
#define SERVO_TICKS_PER_US          (7000.0F / 20000.0F)

/*
ticks per microseconds = t/us
I have clock frequency, prescaler. Timer tick frequency = clock frequency/prescaler.
Timer tick period = prescaler/clock frequency
Timer tick period (us) = prescaler * 1000000/clocl frequency. This is period of clock pulse, not period of pwm signal 
Ticks = pulse (ms) * period (ticks) / period (ms)
Ticks = pulse (us) * period (ticks) / period (us)
*/

/**
 * @brief initialize the desired servo channel. Return an error if init unsuccesful
 * @param servo_channel servo channel to be initialized.
 * @return int 
 */
int servo_init(servo_t *servo);

/**
 * @brief enable the desired channel. Return an error if enable is unsuccesful
 * @param servo_channel servo channel to be enabled
 * @return int 
 */
int servo_enable(servo_t *servo);

/**
 * @brief enable all servo channels. Return an error if enable is unsuccesful
 * 
 * @return int 
 */
int servo_enable_all();

/**
 * @brief disable the desired channel. Return an error if enable is unsuccesful
 * @param servo_channel servo channel to be disabled
 * @return int 
 */
int servo_disable(servo_t *servo);

/**
 * @brief disable all servo channels. Return an error if disable is unsuccesful
 * 
 * @return int 
 */
int servo_disable_all();

/**
 * @brief set the angle for the desired servo channel. Return an error if unsuccseful.
 * 
 * @param servo_channel servo channel to be set to desired angle 
 * @param angle desired angle
 * @return int 
 */
int servo_set_angle(servo_t *servo, float angle);

/**
 * @brief set the pulse width in microseconds for the desired servo channel. Return an error if unsuccseful.
 * 
 * @param servo_channel servo channel to be set to desired angle 
 * @param microseconds desired pulse width in microseconds
 * @return int 
 */
int servo_set_microseconds(servo_t *servo, float microseconds);

/**
 * @brief update the command to the channel with the most recent value. Return an error if 
 * unsuccesful
 * 
 * @param servo_channel 
 * @return int 
 */
int servo_update(servo_t *servo);

/**
 * @brief update the command to all enabled channels with the most recent value. Return an error if 
 * unsuccesful
 * 
 * @return int 
 */
int servo_update_all();



#ifdef __cplusplus
}
#endif

#endif /** SERVO_H */