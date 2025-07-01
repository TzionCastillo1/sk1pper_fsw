#include "status.h"
#include "stdint.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "leddriver.h"
#include "stdbool.h"
#include "cmsis_os.h"

static uint32_t timer_delay = pdMS_TO_TICKS(100);
static leddriver_handle_t log_led_handle;
static bool is_error = false;
extern osTimerId_t status_timerHandle;

void status_init()
{
    leddriver_init(&log_led_handle, GPIOA, LOG_LED_PIN);
}

void status_timer_callback(void *argument)
{
    if(is_error)
    {
        osStatus_t status = osTimerStart(status_timerHandle, timer_delay);
    }
}

void status_set_armed()
{
    leddriver_set(&log_led_handle);
    is_error = false;
}

void status_set_disarmed()
{
    leddriver_reset(&log_led_handle);
    is_error = false;
}

void status_set_error()
{
    is_error = true;
    osStatus_t status = osTimerStart(status_timerHandle, timer_delay);
}