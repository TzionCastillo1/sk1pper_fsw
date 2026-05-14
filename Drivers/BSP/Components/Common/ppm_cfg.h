#ifndef PPM_CFG_H
#define PPM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "ppm.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim8;


#define PPM_DEFAULT_MIN_MICROSECONDS 1000U
#define PPM_DEFAULT_MAX_MICROSECONDS 4000U
#define PPM_DEFAULT_MICROSECONDS 2500U

extern ppm_t ppm_channels[PPM_MAX_CHANNELS];

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** PPM_CFG_H */