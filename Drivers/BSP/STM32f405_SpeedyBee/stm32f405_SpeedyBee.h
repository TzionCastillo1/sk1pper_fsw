#ifndef __STM32F405_SPEEDYBEE_H
#define __STM32F405_SPEEDYBEE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#include "Servo.h"

#if !defined(USE_STM32F405_SPEEDYBEE)
#define USE_STM32F405_SPEEDYBEE
#endif

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
#define PWMCORECLOCK 160000000

#define PRINTF_UART_TIMEOUT_MS 10

/** @defgroup STM32F405_SPEEDYBEE_Public_Variables
 * @{
 */

extern UART_HandleTypeDef huart1;

/**
 * @} 
 * 
 */


/** @defgroup STM32F405_SPEEDYBEE_Exported_Types
 * @{
 */
typedef enum
{
    LED2 = 0,
    LED_GREEN = LED2,
    LEDn
} Led_t;

 /** @}
 */

void MX_GPIO_Init(void);


void SystemClock_Config(void);


/** @defgroup Error Handling
 * {
 */
void Error_Handler(void);
/** @}
*/

/** @addtogroup STM32F405_SPEEDYBEE_LED_Functions
  * @{
  */
void BSP_LED_Init(Led_t Led);
void BSP_LED_DeInit(Led_t Led);
void BSP_LED_On(Led_t Led);
void BSP_LED_Off(Led_t Led);
void BSP_LED_Toggle(Led_t Led);
 /**
 * @} 
 */

/** @addtogroup STM32F405_SPEEDYBEE_TIM_Functions
 *  @{
 */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
/**
* @} 
*/


/** 
 * @defgroup STM32F405_SPEEDYBEE_UART_Functions
 */
void MX_USART1_UART_Init(void);



#ifdef __cplusplus
}
#endif


#endif /* __STM32F405_SPEEDYBEE_H */