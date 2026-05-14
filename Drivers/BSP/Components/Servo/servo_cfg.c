#include "servo_cfg.h"
/**
 * Configuration for servo channels on the SpeedyBee F405 Wing Mini flight controller
 * Currently only defining 6 channels"
 * Motor 1
 * Motor 2
 * Servo 1
 * Servo 2
 * Servo 3
 * Servo 4
 */

/**
 * The Hardware config is mapped to software channels as described below:
    PB7  TIM4_CH2  TIM4 PWM(1) GPIO(50) BIDIR
    PB6  TIM4_CH1  TIM4 PWM(2) GPIO(51)
    PB0  TIM3_CH3  TIM3 PWM(3) GPIO(52)
    PB1  TIM3_CH4  TIM3 PWM(4) GPIO(53) BIDIR
    PC8  TIM8_CH3  TIM8 PWM(5) GPIO(54)
    PC9  TIM8_CH4  TIM8 PWM(6) GPIO(55)
    PB14 TIM8_CH2N TIM8 PWM(7) GPIO(56)

    PA15 TIM2_CH1  TIM2 PWM(8) GPIO(57)
    PB10 TIM2_CH3  TIM2 PWM(9) GPIO(58)
    PB11 TIM2_CH4  TIM2 PWM(10) GPIO(59)

    PB15 TIM1_CH3N TIM1 PWM(11) GPIO(60)
    PA8  TIM1_CH1  TIM1 PWM(12) GPIO(61)# LED
*/

static const servo_cal_t servo_cal_default = 
{
    .min_microseconds = SERVO_DEFAULT_MIN_MICROSECONDS,
    .max_microseconds = SERVO_DEFAULT_MAX_MICROSECONDS,
    .trim_angle = SERVO_DEFAULT_TRIM_ANGLE,
    .abs_max_angle = SERVO_DEFAULT_MAX_ANGLE,
    .lim_min_angle = SERVO_DEFAULT_LIM_MIN_ANGLE,
    .lim_max_angle = SERVO_DEFAULT_LIM_MAX_ANGLE
};


servo_t servo_forward = 
{
    .ppm_channel = PPM_CHANNEL_1,
    .servo_cal = servo_cal_default
};