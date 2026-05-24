#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "errors.h"
#include "events.h"
#include "stdint.h"
#include "stdbool.h"

#define ADC_NUM_CHANNELS            (2U)
#define DMA_VOLTAGE_BUFFER_IDX      (0U)
#define DMA_CURRENT_BUFFER_IDX      (1U)
#define ADC_VREF                    (3.3f)
#define ADC_RES                     (4096U)
#define ADC_VOLTS_PER_LSB           (0.000805)//(3.3/4096.0) //(ADC_VREF / (float) ADC_RES)
#define BATT_MON_V_SCALE            (11.05f)
#define BATT_MON_I_SCALE            (0.333f)


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

uint16_t battery_monitor_get_voltage_raw();

uint16_t battery_monitor_get_current_raw();

float battery_monitor_get_voltage();

float battery_monitor_get_current();

uint8_t battery_monitor_get_soc();

float battery_monitor_cnvrt_voltage(uint16_t raw_voltage);

float battery_monitor_cnvrt_current(uint16_t raw_current);

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** BATTERYMONITOR_H */