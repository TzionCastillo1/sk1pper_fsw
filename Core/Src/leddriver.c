#include "leddriver.h"
#include "stm32f4xx_hal.h"


void leddriver_init(leddriver_handle_t *leddriver_handle, GPIO_TypeDef *LEDPort, uint16_t LEDPin)
{
    leddriver_handle->LEDPort = LEDPort;
    leddriver_handle->LEDPin = LEDPin;
}

void leddriver_set(leddriver_handle_t *leddriver_handle)
{
    HAL_GPIO_WritePin(leddriver_handle->LEDPort, leddriver_handle->LEDPin, GPIO_PIN_SET);
}

void leddriver_reset(leddriver_handle_t *leddriver_handle)
{
    HAL_GPIO_WritePin(leddriver_handle->LEDPort, leddriver_handle->LEDPin, GPIO_PIN_RESET);
}

void leddriver_toggle(leddriver_handle_t *leddriver_handle)
{
    HAL_GPIO_TogglePin(leddriver_handle->LEDPort, leddriver_handle->LEDPin);
}

