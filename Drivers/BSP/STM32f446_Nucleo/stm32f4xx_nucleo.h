#ifndef __STM32F4XX_NUCLEO_H
#define __STM32F4XX_NUCLEO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#if !defined(USE_STM32F4XX_NUCLEO)
#define USE_STM32F4XX_NUCLEO
#endif

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
#define PWMCORECLOCK 160000000


/** @defgroup STM32F4XX_NUCLEO_Exported_Types
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

/** @defgroup STM32F4XX_NUCLEO_Exported_Types
 * @{
 */

 typedef enum
 {
  SERVO0 = 0,
  SERVO_NORTH = SERVO0,
  SERVOn
 }Servo_t;

 typedef struct
 {
    uint16_t GPIO_PIN;
    GPIO_TypeDef *GPIO_PORT;
    TIM_TypeDef *TIMx;
    uint32_t *TIM_CCRx;
    uint32_t TIM_CHANNEL;
    uint32_t TIM_CLK;
    float MinPulse;
    float MaxPulse;
 } Servo_init_t;
 
/**
 * @} 
 * 
 */

/** @defgroup Servo
 *  {
 */

 /**
  * Timer -> PWM channel mapping from SpeedyBeeF405Wing
    PB7  TIM4_CH2  TIM4 PWM(1) GPIO(50) BIDIR
    PB6  TIM4_CH1  TIM4 PWM(2) GPIO(51)
    PB0  TIM3_CH3  TIM3 PWM(3) GPIO(52)
    PB1  TIM3_CH4  TIM3 PWM(4) GPIO(53) BIDIR
    PC8  TIM8_CH3  TIM8 PWM(5) GPIO(54) 
  * 
  */

 #define SERVO0_PIN                 GPIO_PIN_7
 #define SERVO0_GPIO_PORT           GPIOB
 #define SERVO0_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
 #define SERVO0_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE()
 #define SERVO0_TIM                 TIM4

 #define SERVO1_PIN
 #define SERVO1_GPIO_PORT
 #define SERVO1_
 #define SERVO1_GPIO_CLK_ENABLE()
 #define SERVO1_GPIO_CLK_DISABLE()
 
 #define SERVO2_PIN
 #define SERVO2_GPIO_PORT
 #define SERVO2_GPIO_CLK_ENABLE()
 #define SERVO2_GPIO_CLK_DISABLE()

 #define SERVO3_PIN
 #define SERVO3_GPIO_PORT
 #define SERVO3_GPIO_CLK_ENABLE()
 #define SERVO3_GPIO_CLK_DISABLE()

 #define SERVO4_PIN
 #define SERVO4_GPIO_PORT
 #define SERVO4_GPIO_CLK_ENABLE()
 #define SERVO4_GPIO_CLK_DISABLE()
 /**
  * @} 
  * 
*/


 /** @addtogroup STM32F4XX_NUCLEO_LED_Functions
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

/**
 * @addtogroup STM32F4XX_NUCLEO_SERVO_Functions 
 * @{
 */

 void BSP_Servo_Init(Servo_t Servo);
 void BSP_Servo_DeInit(Servo_t Servo);
 void BSP_Servo_Center(Servo_t Servo);
 void BSP_Servo_Min(Servo_t Servo);
 void BSP_Servo_Max(Servo_t Servo);
 void BSP_Servo_Set(Servo_t Servo, uint16_t PulseMicroseconds);

 /**
 * @} 
 * 
 */

#ifdef __cplusplus
}
#endif


#endif /* __STM32F4XX_NUCLEO_H */