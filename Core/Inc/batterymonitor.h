#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "errors.h"
#include "event.h"

error_t batteryMonitorInit();

error_t batteryMonitorStart();

error_t batteryMonitorStop();

error_t batteryMonitorUpdate();

float batteryMonitorGetVoltage();

error_t batteryMonitorLogVoltage();


#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#endif /** BATTERYMONITOR_H */