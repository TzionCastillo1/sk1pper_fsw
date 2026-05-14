#include "ppm_cfg.h"
/**
 * Configuration for ppm channels on the SpeedyBee F405 Wing Mini flight controller
 * Currently only defining 6 channels"
 * Motor 1
 * Motor 2
 * PPM 1
 * PPM 2
 * PPM 3
 * PPM 4
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

ppm_t ppm_channels[PPM_MAX_CHANNELS] =
{
    /** PPM_CHANNEL_1 */
    {
        .ppm_hw_config = 
        {
            .htimx = &htim4,
            .tim_channel = TIM_CHANNEL_2,
            .ppm_port = (GPIO_TypeDef *)GPIOB,
            .ppm_pin = GPIO_PIN_6
        },
        .ppm_state =
        {
            .is_initialized = false,
            .is_enabled = false,
            .current_microseconds = PPM_DEFAULT_MICROSECONDS,
            .next_microseconds = PPM_DEFAULT_MICROSECONDS
        }
    },
    /** PPM_CHANNEL_2 */
    {
        .ppm_hw_config = 
        {
            .htimx = &htim4,
            .tim_channel = TIM_CHANNEL_1,
            .ppm_port = (GPIO_TypeDef *)GPIOB,
            .ppm_pin = GPIO_PIN_7
        },
        .ppm_state =
        {
            .is_initialized = false,
            .is_enabled = false,
            .current_microseconds = PPM_DEFAULT_MICROSECONDS,
            .next_microseconds = PPM_DEFAULT_MICROSECONDS
        }
    },
    /** PPM_CHANNEL_3 */
    {
        .ppm_hw_config = 
        {
            .htimx = &htim3,
            .tim_channel = TIM_CHANNEL_3,
            .ppm_port = (GPIO_TypeDef *)GPIOB,
            .ppm_pin = GPIO_PIN_0
        },
        .ppm_state =
        {
            .is_initialized = false,
            .is_enabled = false,
            .current_microseconds = PPM_DEFAULT_MICROSECONDS,
            .next_microseconds = PPM_DEFAULT_MICROSECONDS
        }
    },
    /** PPM_CHANNEL_4 */
    {
        .ppm_hw_config = 
        {
            .htimx = &htim3,
            .tim_channel = TIM_CHANNEL_4,
            .ppm_port = (GPIO_TypeDef *)GPIOB,
            .ppm_pin = GPIO_PIN_1
        },
        .ppm_state =
        {
            .is_initialized = false,
            .is_enabled = false,
            .current_microseconds = PPM_DEFAULT_MICROSECONDS,
            .next_microseconds = PPM_DEFAULT_MICROSECONDS
        }
    },
    /** PPM_CHANNEL_5 */
    {
        .ppm_hw_config = 
        {
            .htimx = &htim8,
            .tim_channel = TIM_CHANNEL_3,
            .ppm_port = (GPIO_TypeDef *)GPIOC,
            .ppm_pin = GPIO_PIN_8
        },
        .ppm_state =
        {
            .is_initialized = false,
            .is_enabled = false,
            .current_microseconds = PPM_DEFAULT_MICROSECONDS,
            .next_microseconds = PPM_DEFAULT_MICROSECONDS
        }
    }
};

