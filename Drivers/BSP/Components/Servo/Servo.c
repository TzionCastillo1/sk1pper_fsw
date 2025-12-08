#include "Servo.h"
#include "Servo_Cfg.h"

uint32_t servo_microseconds_to_ticks(int32_t microseconds);
float servo_angle_to_microseconds(servo_channels_t servo, float angle);

int servo_init(servo_channels_t servo_channel)
{
    servo_channels[servo_channel].servo_state.is_initialized = true;
    return 0;
}

int servo_enable(servo_channels_t servo_channel)
{
    servo_channels[servo_channel].servo_state.is_enabled = true;
    HAL_TIM_Base_Start(servo_channels[servo_channel].servo_hw_config.htimx);
    HAL_TIM_PWM_Start(servo_channels[servo_channel].servo_hw_config.htimx, servo_channels[servo_channel].servo_hw_config.tim_channel);
}

int servo_enable_all()
{
    for (int servo_channel = SERVO_CHANNEL_1; servo_channel < SERVO_MAX_CHANNELS; servo_channel++)
    {
        servo_enable(servo_channel);
    }
    return 0;
}

int servo_disable(servo_channels_t servo_channel)
{
    HAL_TIM_PWM_Stop(servo_channels[servo_channel].servo_hw_config.htimx, servo_channels[servo_channel].servo_hw_config.tim_channel);
    servo_channels[servo_channel].servo_state.is_enabled = false;
    return 0;
}

int servo_disable_all()
{
    for (int servo_channel = SERVO_CHANNEL_1; servo_channel < SERVO_MAX_CHANNELS; servo_channel++)
    {
        servo_disable(servo_channel);
    }
    return 0;
}

int servo_set_angle(servo_channels_t servo_channel, float angle)
{
    float microseconds = servo_angle_to_microseconds(servo_channel, angle);
    servo_channels[servo_channel].servo_state.next_microseconds = microseconds;
    return 0;
}

int servo_set_microseconds(servo_channels_t servo_channel, float microseconds)
{
    servo_channels[servo_channel].servo_state.next_microseconds = microseconds;
    return 0;
}

int servo_update(servo_channels_t servo_channel)
{
    if(servo_channels[servo_channel].servo_state.is_initialized && servo_channels[servo_channel].servo_state.is_enabled)
    {
        uint32_t compare_ticks = servo_microseconds_to_ticks(servo_channels[servo_channel].servo_state.next_microseconds);
        TIM_HandleTypeDef *htimex = servo_channels[servo_channel].servo_hw_config.htimx;
        __HAL_TIM_SET_COMPARE(servo_channels[servo_channel].servo_hw_config.htimx, 
                            servo_channels[servo_channel].servo_hw_config.tim_channel, 
                            compare_ticks);
        servo_channels[servo_channel].servo_state.current_microseconds = servo_channels[servo_channel].servo_state.next_microseconds;
    }

    return 0;
}

int servo_update_all()
{
    return 0;
}

int servo_test(servo_channels_t servo_channel)
{
    servo_init(servo_channel);
    servo_enable(servo_channel);
    servo_set_microseconds(servo_channel, SERVO_DEFAULT_MIN_MICROSECONDS);
    servo_update(servo_channel);
    HAL_Delay(500);
    servo_set_microseconds(servo_channel, SERVO_DEFAULT_MAX_MICROSECONDS);
    servo_update(servo_channel);
    HAL_Delay(500);
    servo_set_microseconds(servo_channel, SERVO_DEFAULT_MICROSECONDS);
    servo_update(servo_channel);
    HAL_Delay(500);
    servo_disable(servo_channel);
}

int servo_test_all()
{
    for (int servo_channel = SERVO_CHANNEL_1; servo_channel < SERVO_MAX_CHANNELS; servo_channel++)
    {
        servo_test(servo_channel);
    }
}

uint32_t servo_microseconds_to_ticks(int32_t microseconds)
{
    return (uint32_t) microseconds * SERVO_TICKS_PER_US;
}

float servo_angle_to_microseconds(servo_channels_t servo_channel, float angle)
{
   /** trying to map from degrees to microseconds.
    * 0 degrees corresponds with min microseconds,
    * max degrees corresponds with max microseconds.
    * y = mx + b, microseconds = degrees * microseconds/degree + min microseconds 
    * microseconds per degree = 1000/max degrees
    * */
    float microseconds = (angle * (servo_channels[servo_channel].servo_cal.max_microseconds - servo_channels[servo_channel].servo_cal.min_microseconds)
                         / servo_channels[servo_channel].servo_cal.abs_max_angle) + servo_channels[servo_channel].servo_cal.min_microseconds;
}