#ifndef SERVO_H
#define SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "PPM.h"


typedef struct 
{
    PPM_t PPMx;
    float MinPulse;
    float MaxPulse;
    float rangeDegrees;
    float offsetDegrees;
}SERVO_t;


void SERVO_Init(SERVO_t * const me);

void SERVO_DeInit(SERVO_t * const me);

void SERVO_Start(SERVO_t * const me);

void SERVO_Stop(SERVO_t * const me);

void SERVO_ToMin(SERVO_t * const me);

void SERVO_ToMax(SERVO_t * const me);

void SERVO_ToCenter(SERVO_t * const me);

void SERVO_ToAngle(SERVO_t * const me);

void SERVO_Set_Max(SERVO_t * const me);

void SERVO_Set_Min(SERVO_t * const me);

#ifdef __cplusplus
}
#endif

#endif /** SERVO_H */