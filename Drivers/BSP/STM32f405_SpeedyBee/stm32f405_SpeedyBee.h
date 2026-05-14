#ifndef __STM32F405_SPEEDYBEE_H
#define __STM32F405_SPEEDYBEE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#include "hw_config.h"
#include "servo.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "gpio.h"
#include "tim.h"
#include "adc.h"
#include "dma.h"

#if !defined(USE_STM32F405_SPEEDYBEE)
#define USE_STM32F405_SPEEDYBEE
#endif

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
#define PWMCORECLOCK 160000000

#define PRINTF_UART_TIMEOUT_MS 10

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


extern void putchar_(char c);



#ifdef __cplusplus
}
#endif


#endif /* __STM32F405_SPEEDYBEE_H */