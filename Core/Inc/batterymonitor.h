#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "errors.h"
#include "events.h"
#include "stdint.h"

error_t battery_monitor_init();

error_t battery_monitor_enable();

error_t battery_monitor_disable();

float battery_monitor_get_voltage();

uint8_t battery_monitor_get_soc();


#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** BATTERYMONITOR_H */