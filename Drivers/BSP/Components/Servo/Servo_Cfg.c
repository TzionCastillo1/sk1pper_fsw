#include "Servo_Cfg.h"
#include "Servo.h"
#include "PPM_Cfg.h"

SERVO_t SERVO_0 =
{
    .PPMx = PPM_Channel_0,
    .MinPulse = 0.65,
    .MaxPulse = 0.3,
    .rangeDegrees = 180,
    .offsetDegrees = 0
};

SERVO_t SERVO_1 =
{
    .PPMx = PPM_Channel_1,
    .MinPulse = 0.65,
    .MaxPulse = 0.3,
    .rangeDegrees = 180,
    .offsetDegrees = 0
};

SERVO_t SERVO_2 =
{
    .PPMx = PPM_Channel_2,
    .MinPulse = 0.65,
    .MaxPulse = 0.3,
    .rangeDegrees = 180,
    .offsetDegrees = 0
};

SERVO_t SERVO_3 =
{
    .PPMx = PPM_Channel_3,
    .MinPulse = 0.65,
    .MaxPulse = 0.3,
    .rangeDegrees = 180,
    .offsetDegrees = 0
};