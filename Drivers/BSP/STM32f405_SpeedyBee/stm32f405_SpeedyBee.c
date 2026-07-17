#include "stm32f405_SpeedyBee.h"
#include "printf/printf.h"


/**
 * @defgroup STM32F4XX_NUCLEO_Private_Variables
 * @{ 
 * 
 */

GPIO_TypeDef *GPIO_PORT[LEDn] = {LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED2_PIN, LED3_PIN};





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

void putchar_(char c)
{
  HAL_StatusTypeDef status;
  status = HAL_UART_Transmit(&huart1, (uint8_t*) &c, 1, PRINTF_UART_TIMEOUT_MS);
}
