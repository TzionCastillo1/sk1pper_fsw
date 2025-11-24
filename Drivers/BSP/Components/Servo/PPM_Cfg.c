#include "PPM_Cfg.h"

typedef enum
{
    PPM_0 = 0,
    PPM_1,
    PPMn
} PPM_Channels_t;


/**
 * Timer -> PWM channel mapping from SpeedyBeeF405Wing
PB7  TIM4_CH2  TIM4 PWM(1) GPIO(50) () BIDIR
PB6  TIM4_CH1  TIM4 PWM(2) GPIO(51) (D11)
PB0  TIM3_CH3  TIM3 PWM(3) GPIO(52)
PB1  TIM3_CH4  TIM3 PWM(4) GPIO(53) BIDIR
PC8  TIM8_CH3  TIM8 PWM(5) GPIO(54) 
* 
*/

/**
 * Timers to be used for PPM:
 * 
 */
const TIM_HandleTypeDef htim4 =
{
    .Instance = TIM4
};

const TIM_HandleTypeDef htim3 =
{
    .Instance = TIM3
};
/*************************************************/

/** PPM Channel Configurations */

const PPM_t PPM_Channel_0 = 
{
    .htimx = &htim4,
    .TIM_Channel = TIM_CHANNEL_2
};

const PPM_t PPM_Channel_1 = 
{
    .htimx = &htim4,
    .TIM_Channel = TIM_CHANNEL_1
};

const PPM_t PPM_Channel_2 = 
{
    .htimx = &htim3,
    .TIM_Channel = TIM_CHANNEL_3
};

const PPM_t PPM_Channel_3 = 
{
    .htimx = &htim3,
    .TIM_Channel = TIM_CHANNEL_4
};

PPM_t *PPM_Channels[PPMn] = 
{
    &PPM_Channel_0,
    &PPM_Channel_1,
    &PPM_Channel_2,
    &PPM_Channel_3
};