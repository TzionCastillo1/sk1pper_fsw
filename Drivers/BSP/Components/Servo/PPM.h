#ifndef PPM_H
#define PPM_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stm32f4xx_hal.h"

#define PPM_PERIOD_TICKS        16000U
#define PPM_FREQUENCY           50U
#define PPM_PERIOD_MS           (1000 / PPM_FREQUENCY)
#define PPM_TICKS_PER_PERIOD    (PPM_PERIOD_TICKS / PPM_PERIOD_MS)



typedef struct PPM_t
{
    TIM_HandleTypeDef *htimx;
    uint32_t TIM_Channel;
}PPM_t;


void PPM_Init(PPM_t *PPM_Channel);

void PPM_DeInit(PPM_t *PPM_Channel);

void PPM_Start(PPM_t *PPM_Channel);

void PPM_Stop(PPM_t *PPM_Channel);

void PPM_SetMilliseconds(PPM_t *PPM_Channel, float PulseTimeMS);

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** PPM_H */