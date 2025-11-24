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

/** @defgroup LED
 * {
 */

#define LED2_PIN                    GPIO_PIN_5
#define LED2_GPIO_PORT              GPIOA
#define LED2_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()


 /**
 * @}
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


#ifdef __cplusplus
}
#endif


#endif /* __STM32F405_SPEEDYBEE_H */