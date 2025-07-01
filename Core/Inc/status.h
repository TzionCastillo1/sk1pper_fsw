#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#define LOG_LED_PIN GPIO_PIN_13

typedef enum 
{
    SYSTEM_STATUS_ARMED = 0,
    SYSTEM_STATUS_DISARMED,
    SYSTEM_STATUS_ERROR
} system_status_t;

void status_init();

void status_set_armed();

void status_set_disarmed();

void satus_set_error();

void status_timer_callback(void *argument);

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** STATUS_H */