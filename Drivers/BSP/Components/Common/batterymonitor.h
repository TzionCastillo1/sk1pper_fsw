#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stm32f4xx_hal.h" 
#include "errors.h"
#include "events.h"
#include "stdint.h"
#include "stdbool.h"

#define ADC_NUM_CHANNELS            (2U)
#define DMA_VOLTAGE_BUFFER_IDX      (0U)
#define DMA_CURRENT_BUFFER_IDX      (1U)

extern ADC_HandleTypeDef hadc1;

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

int16_t battery_monitor_get_voltage_raw();

int16_t battery_monitor_get_current_raw();

float battery_monitor_get_voltage();

uint8_t battery_monitor_get_soc();


#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** BATTERYMONITOR_H */