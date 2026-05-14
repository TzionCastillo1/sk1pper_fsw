#ifndef SERVO_CFG_H
#define SERVO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "servo.h"
#include "ppm_cfg.h"

extern servo_t servo_forward;

#define SERVO_DEFAULT_MIN_MICROSECONDS 1000U
#define SERVO_DEFAULT_MAX_MICROSECONDS 4000U
#define SERVO_DEFAULT_MICROSECONDS 2500U
#define SERVO_DEFAULT_MAX_ANGLE 180U
#define SERVO_DEFAULT_LIM_MAX_ANGLE SERVO_DEFAULT_MAX_ANGLE
#define SERVO_DEFAULT_LIM_MIN_ANGLE 0U
#define SERVO_DEFAULT_TRIM_ANGLE 0U

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** SERVO_CFG_H */