#include "stm32f4xx_nucleo.h"

/**
 * @defgroup STM32F4XX_NUCLEO_Private_Variables
 * @{ 
 * 
 */

GPIO_TypeDef *GPIO_PORT[LEDn] = {LED2_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED2_PIN};

const Servo_init_t Servo_Cfg[SERVOn] =
{
    /** Servo 0 Configuration */
    {
        SERVO0_GPIO_PORT,
        SERVO0_PIN,
        SERVO0_TIM,
        &SERVO0_TIM->CCR1,
        TIM_CHANNEL_1,
        PWMCORECLOCK,
        0.65,
        2.3
    }
};

TIM_HandleTypeDef *SERVO_TIM[SERVOn] = {SERVO0_TIM};

/**
 * @} 
 * 
 */

/** @defgroup LED Functions
 * @{
 */

/**
 * @brief Configure LED GPIO
 * @param Led: LED to be configured.
 *        This parameter can be one of the follwoing values:
 *          @arg LED2 or LED4 on Nucleo-64 with extermal SMPS
 * @retval None
 * 
 */
void BSP_LED_Init(Led_t Led)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Enable the GPIO_LED CLock */
    LED2_GPIO_CLK_ENABLE();

    /* COnfigure the GPIO_LED pin*/
    GPIO_InitStruct.Pin     = GPIO_PIN[Led];
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_NOPULL;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
}

/**
 * @brief Deinitialize LED GPIO.
 * @param LED: LED to be deinitialized.
 *      This parameter can be one of the following values:
 *          @arg LED2 or LED4 on Nucleo-64 with external SMPS
 * @note BSP_LED_Deinit() does not disable the GPIO clock
 * @retval None 
 */
void BSP_Led_DeInit(Led_t Led)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Turn off LED */
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
    /* DeInit the GPIO_LED pin */
    GPIO_InitStruct.Pin = GPIO_PIN[Led];
    HAL_GPIO_DeInit(GPIO_PORT[Led], GPIO_InitStruct.Pin);
}


/**
 * @brief Turn selected LED on.
 * @param Led: Specifies the Led to be set on.
 *  This parameter can be one of the follwoing parameters:
 *  @arg LED2 or LED4 on Nucleo-64 with external SMPS
 * 
 * @retval None
 */
void BSP_LED_On(Led_t Led)
{
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
}

/**
 * @brief Turn selected LED Off.
 * @param Led: Specifies the Led to be set off.
 *  This parameter can be one of the following parameters:
 *  @arg LED2 or LED4 on Nucleo-64 with external SMPS
 * 
 * @retval None
 */
void BSP_LED_Off(Led_t Led)
{
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
}

/**
 * @brief Toggle the selected LED.
 * @param Led: Specifies the Led to be toggled.
 *  This parameter can be one of the follwoing parameters:
 *      @arg LED2 or LED4 on Nucleo-64 with external SMPS
 * @retval None
 */
void BSP_LED_Toggle(Led_t Led)
{
    HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}

/** @} */
TIM_HandleTypeDef htim4;

/**
 * @defgroup Servo Functions 
 * @{
 */

 /**
  * @brief Configure Servo PWM  
  * 
  * @param Servo: Servo to be initialized.
  *     @arg Servo can be Servo0 through Servo4
  * @retval None
  */
 void BSP_Servo_Init(Servo_t Servo)
 {
    /* USER CODE BEGIN TIM4_Init 0 */

    /* USER CODE END TIM4_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    htim4.Instance = Servo_Cfg[Servo].TIMx;
    htim4.Init.Prescaler = 200;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 16000;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM4_Init 2 */

    /* USER CODE END TIM4_Init 2 */
    HAL_TIM_MspPostInit(&htim4);

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

 }

 /**
  * @brief Deinitialize Servo PWM
  * 
  * @param Servo: Servo to be Deinitialized.
  *     @arg Servo can be Servo0 through Servo4
  * @retval None
  */
 void BSP_Servo_DeInit(Servo_t Servo)
 {
    
 }

/**
 * @brief Set Servo to the 'center' 
 * 
 * @param Servo: Servo to be centered 
 *      @arg Servo can be Servo0 through Servo4
 * @retval None
 */
 void BSP_Servo_Center(Servo_t Servo)
 {
    uint32_t Pulse_Ticks = 0.925 * 16000 / 20;
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Pulse_Ticks);
 }

 /**
  * @brief Set Servo to the 'minimum'
  * 
  * @param Servo: Servo to be minimumed
  *     @arg Servo can be Servo0 through Servo4
  * @retval None  
  */
 void BSP_Servo_Min(Servo_t Servo)
 {

 }

 /**
  * @brief Set Servo to the 'maximum'
  * 
  * @param Servo: Servo to be maximumed 
  *     @arg Servo can be Servo0 through Servo4
  * @retval None
  */
 void BSP_Servo_Max(Servo_t Servo)
 {
    uint32_t Pulse_Ticks = Servo_Cfg[Servo].MaxPulse * 16000 / 20;
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Pulse_Ticks);
 }

 /**
  * @brief Set Servo to an arbitrary location
  * 
  * @param Servo: Servo to be set to an arbitrary location 
  *     @arg Servo can be Servo0 through Servo4
  * @param PulseMicroseconds: location servo is set to
  *     @arg PuleMicroseconds can be 1000 through 2000
  * @retval None
  */
 void BSP_Servo_Set(Servo_t Servo, uint16_t PulseMicroseconds)
 {

 }

 /**
  * @} 
  * 
  */
