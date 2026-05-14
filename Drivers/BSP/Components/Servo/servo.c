#include "servo.h"
#include "servo_cfg.h"

static float servo_angle_to_microseconds(servo_t *servo, float angle);

int servo_init(servo_t *servo)
{
    return ppm_init(servo->ppm_channel);
}

int servo_enable(servo_t *servo)
{
    return ppm_enable(servo->ppm_channel);
}

int servo_enable_all()
{
    /*for (int servo = SERVO_CHANNEL_1; servo < SERVO_MAX_CHANNELS; servo++)
    {
        servo_enable(servo);
    }
    return 0;
    */
}

int servo_disable(servo_t *servo)
{
    return ppm_disable(servo->ppm_channel);

}

int servo_disable_all()
{
    /*
    for (int servo = SERVO_CHANNEL_1; servo < SERVO_MAX_CHANNELS; servo++)
    {
        servo_disable(servo);
    }
        */
    return 0;
}

int servo_set_angle(servo_t *servo, float angle)
{
    float microseconds = servo_angle_to_microseconds(servo, angle);
    return ppm_set_microseconds(servo->ppm_channel, microseconds);
}

int servo_set_microseconds(servo_t *servo, float microseconds)
{
    return ppm_set_microseconds(servo->ppm_channel, microseconds);
}

int servo_update(servo_t *servo)
{
    return ppm_update(servo->ppm_channel);
}

int servo_update_all()
{
    return 0;
}

int servo_test(servo_t *servo)
{
    servo_init(servo);
    servo_enable(servo);
    servo_set_microseconds(servo, SERVO_DEFAULT_MIN_MICROSECONDS);
    servo_update(servo);
    HAL_Delay(500);
    servo_set_microseconds(servo, SERVO_DEFAULT_MAX_MICROSECONDS);
    servo_update(servo);
    HAL_Delay(500);
    servo_set_microseconds(servo, SERVO_DEFAULT_MICROSECONDS);
    servo_update(servo);
    HAL_Delay(500);
    servo_disable(servo);
}


static float servo_angle_to_microseconds(servo_t *servo, float angle)
{
   /** trying to map from degrees to microseconds.
    * 0 degrees corresponds with min microseconds,
    * max degrees corresponds with max microseconds.
    * y = mx + b, microseconds = degrees * microseconds/degree + min microseconds 
    * microseconds per degree = 1000/max degrees
    * */
    float microseconds = (angle * (servo->servo_cal.max_microseconds - servo->servo_cal.min_microseconds)
                         / servo->servo_cal.abs_max_angle) + servo->servo_cal.min_microseconds;
}