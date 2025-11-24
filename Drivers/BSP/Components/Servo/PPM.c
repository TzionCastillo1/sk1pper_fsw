#include "PPM.h"
#include "PPM_Cfg.h"


/**
 * TODO: Add Error checking/ return values 
 * 
 */

uint32_t PPM_MillisecondsToTicks(float Milliseconds);

/**
 * @brief Configure Servo PPM
 * 
 * @param me: PPM to be initialized.
 * 
 * @retval None
 */
void PPM_Init(PPM_t *PPM_Channel)
{
    /* USER CODE BEGIN TIM4_Init 0 */

    /* USER CODE END TIM4_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    //me->htimx->Instance = me->TIMx;
    PPM_Channel->htimx->Init.Prescaler = 200;
    PPM_Channel->htimx->Init.CounterMode = TIM_COUNTERMODE_UP;
    PPM_Channel->htimx->Init.Period = 16000;
    PPM_Channel->htimx->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    PPM_Channel->htimx->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(PPM_Channel->htimx) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(PPM_Channel->htimx, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(PPM_Channel->htimx) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(PPM_Channel->htimx, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(PPM_Channel->htimx, &sConfigOC, PPM_Channel->TIM_Channel) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN TIM4_Init 2 */

    /* USER CODE END TIM4_Init 2 */
    HAL_TIM_MspPostInit(PPM_Channel->htimx);

}

/**
 * @brief Deinitialize PPM 
 * 
 * @param me: PPM channel to be deinitialized. 
 * 
 * @retval None
 */
void PPM_DeInit(PPM_t *PPM_Channel)
{
    HAL_TIM_PWM_DeInit(PPM_Channel->htimx);
}

/**
 * @brief Start the PPM Channel 
 * 
 * @param me: PPM channel to be started 
 * 
 * @retval None
 */
void PPM_Start(PPM_t *PPM_Channel)
{
    HAL_TIM_PWM_Start(PPM_Channel->htimx, PPM_Channel->TIM_Channel);
}

/**
 * @brief Stop the PPM Channel 
 * 
 * @param me: PPM channel to be stopped
 * 
 * @retval None 
 */
void PPM_Stop(PPM_t *PPM_Channel)
{
    HAL_TIM_PWM_Stop(PPM_Channel->htimx, PPM_Channel->TIM_Channel);
}

/**
 * @brief Set the PPM pulse time
 * 
 * @param me: PPM channel to be set
 * @param PulseTimeMS: Pulse time to be set
 * 
 * @retval None
 */
void PPM_SetMilliseconds(PPM_t *PPM_Channel, float PulseTimeMS)
{
    /**
     * TODO: Implement function 
     * 
     */
    uint32_t CompareTicks = PPM_MillisecondsToTicks(PulseTimeMS);
    __HAL_TIM_SET_COMPARE(PPM_Channel->htimx, PPM_Channel->TIM_Channel, CompareTicks);

}

/**
 * @brief Convert Milliseconds to number of ticks for PPM timer 
 * 
 * @param Milliseconds: desired Pulse Width 
 * @return uint32_t: number of ticks 
 */
uint32_t PPM_MillisecondsToTicks(float Milliseconds)
{
    return (uint32_t) (Milliseconds * PPM_PERIOD_TICKS / PPM_PERIOD_MS);
}