#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stm32f4xx_hal.h"
#include "stdint.h"

typedef struct leddriver_handle_t
{
    GPIO_TypeDef *LEDPort;
    uint16_t LEDPin;
} leddriver_handle_t;


void leddriver_init(leddriver_handle_t *leddriver_handle, GPIO_TypeDef *LEDPort, uint16_t LEDPin);

void leddriver_set(leddriver_handle_t *leddriver_handle);

void leddriver_reset(leddriver_handle_t *leddriver_handle);

void leddriver_toggle(leddriver_handle_t *leddriver_handle);

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** LEDDRIVER_H */