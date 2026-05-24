#include "stdint.h"

// Minimal type definitions to satisfy the liner
typedef struct { uint32_t dummy; } ADC_HandleTypeDef;
ADC_HandleTypeDef hadc1;

int HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length)
{
    return 0;
}

int HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc)
{
    return 0;
}