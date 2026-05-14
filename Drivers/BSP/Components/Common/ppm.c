#include "ppm.h"
#include "ppm_cfg.h"

uint32_t ppm_microseconds_to_ticks(int32_t microseconds);

int ppm_init(ppm_channels_t ppm_channel)
{
    ppm_channels[ppm_channel].ppm_state.is_initialized = true;
    return 0;
}

int ppm_enable(ppm_channels_t ppm_channel)
{
    ppm_channels[ppm_channel].ppm_state.is_enabled = true;
    HAL_TIM_Base_Start(ppm_channels[ppm_channel].ppm_hw_config.htimx);
    HAL_TIM_PWM_Start(ppm_channels[ppm_channel].ppm_hw_config.htimx, ppm_channels[ppm_channel].ppm_hw_config.tim_channel);
}

int ppm_enable_all()
{
    for (int ppm_channel = PPM_CHANNEL_1; ppm_channel < PPM_MAX_CHANNELS; ppm_channel++)
    {
        ppm_enable(ppm_channel);
    }
    return 0;
}

int ppm_disable(ppm_channels_t ppm_channel)
{
    HAL_TIM_PWM_Stop(ppm_channels[ppm_channel].ppm_hw_config.htimx, ppm_channels[ppm_channel].ppm_hw_config.tim_channel);
    ppm_channels[ppm_channel].ppm_state.is_enabled = false;
    return 0;
}

int ppm_disable_all()
{
    for (int ppm_channel = PPM_CHANNEL_1; ppm_channel < PPM_MAX_CHANNELS; ppm_channel++)
    {
        ppm_disable(ppm_channel);
    }
    return 0;
}


int ppm_set_microseconds(ppm_channels_t ppm_channel, float microseconds)
{
    ppm_channels[ppm_channel].ppm_state.next_microseconds = microseconds;
    return 0;
}

int ppm_update(ppm_channels_t ppm_channel)
{
    if(ppm_channels[ppm_channel].ppm_state.is_initialized && ppm_channels[ppm_channel].ppm_state.is_enabled)
    {
        uint32_t compare_ticks = ppm_microseconds_to_ticks(ppm_channels[ppm_channel].ppm_state.next_microseconds);
        TIM_HandleTypeDef *htimex = ppm_channels[ppm_channel].ppm_hw_config.htimx;
        __HAL_TIM_SET_COMPARE(ppm_channels[ppm_channel].ppm_hw_config.htimx, 
                            ppm_channels[ppm_channel].ppm_hw_config.tim_channel, 
                            compare_ticks);
        ppm_channels[ppm_channel].ppm_state.current_microseconds = ppm_channels[ppm_channel].ppm_state.next_microseconds;
    }

    return 0;
}

uint32_t ppm_microseconds_to_ticks(int32_t microseconds)
{
    return (uint32_t) microseconds * PPM_TICKS_PER_US;
}
