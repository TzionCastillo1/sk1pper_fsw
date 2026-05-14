#include "esc_cfg.h"
#include "ppm.h"

esc_t esc_main = 
{
    .ppm_channel = PPM_CHANNEL_5,
    .max_microseconds = ESC_DEFAULT_MAX_MICROSECONDS,
    .min_microseconds = ESC_DEFAULT_MIN_MICROSECONDS
};