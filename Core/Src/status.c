#include "status.h"
#include "stdint.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "leddriver.h"
#include "stdbool.h"
#include "cmsis_os.h"

static uint32_t timer_delay = pdMS_TO_TICKS(250);
static leddriver_handle_t log_led_handle;
static bool is_error = false;
extern osTimerId_t status_timerHandle;

void status_init()
{
    leddriver_init(&log_led_handle, GPIOA, LOG_LED_PIN);
}

void status_timer_callback(void *argument)
{
    //leddriver_toggle(&log_led_handle);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_13);
}

void status_set_armed()
{
    leddriver_set(&log_led_handle);
    osStatus_t status = osTimerStop(status_timerHandle);
}

void status_set_disarmed()
{
    leddriver_reset(&log_led_handle);
    osStatus_t status = osTimerStop(status_timerHandle);
}

/**
 * @brief Set the status LED to indicate an error. This must be called from a task.
 * @param - none
 * @return - none 
 * 
 */
void status_set_error()
{
    osStatus_t status = osTimerStart(status_timerHandle, timer_delay);
    if (status != osOK)
    {
        leddriver_set(&log_led_handle);
    }
}