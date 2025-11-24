#include "Servo.h"
#include "Servo_Cfg.h"


void SERVO_Init(SERVO_t * const me)
{
    /**
     * TODO: incorporate & track timers somehow
     * 
     */
    PPM_Init(me);
}

void SERVO_DeInit(SERVO_t * const me)
{
    PPM_DeInit(me);
}

void SERVO_Start(SERVO_t *const me)
{
    PPM_Start(me);
}

void SERVO_Stop(SERVO_t * const me)
{
    PPM_Stop(me);
}

/**
 * @brief Set the Servo to its minimum angle 
 * 
 * @param me: Servo to be set
 * 
 * @retval None 
 */
void SERVO_ToMin(SERVO_t * const me)
{
    PPM_SetMilliseconds(me, me->MinPulse);
}

void SERVO_ToMax(SERVO_t * const me)
{
    PPM_SetMilliseconds(me, me->MaxPulse);
}

void SERVO_ToCenter(SERVO_t * const me)
{
    PPM_SetMilliseconds(me, (me->MaxPulse - me->MinPulse) / 2);
}

void SERVO_ToAngle(SERVO_t * const me)
{
}

void SERVO_Set_Max(SERVO_t * const me)
{
}

void SERVO_Set_Min(SERVO_t * const me)
{   
}

float SERVO_DegToMilliseconds(float Degrees)
{
    /**
     * NOTE: Just a test value, needs to be updated. 
     * 
     */
    return 0.925;
}

