#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "errors.h"
#include "events.h"
#include "stdint.h"

/**
 * define default battery setup
define HAL_BATT_MONITOR_DEFAULT 4
define HAL_BATT_VOLT_PIN 10
define HAL_BATT_CURR_PIN 11
define HAL_BATT_VOLT_SCALE 11.05 # matched to PDB board
define HAL_BATT_CURR_SCALE 50    # matched to PDB board
 */

error_t battery_monitor_init();

error_t battery_monitor_enable();

error_t battery_monitor_disable();

float battery_monitor_get_voltage();

uint8_t battery_monitor_get_soc();


#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** BATTERYMONITOR_H */