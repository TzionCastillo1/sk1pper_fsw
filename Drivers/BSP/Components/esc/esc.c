#include "esc.h"
#include "esc_cfg.h"
#include "ppm.h"

static uint16_t throttle_to_microseconds(esc_t *esc, float throttle);

int esc_init(esc_t *esc)
{
    return ppm_init(esc->ppm_channel);
}

int esc_enable(esc_t *esc)
{
    int16_t res = ppm_enable(esc->ppm_channel);
    esc_set_throttle(esc, 0);
    esc_update(esc);
    return res;
}

int esc_disable(esc_t *esc)
{
    return ppm_disable(esc->ppm_channel);
}

int esc_cal(esc_t *esc)
{
    /** TODO: */
    return 0;
}

int esc_set_throttle(esc_t *esc, float throttle)
{
    int result = -1;
    int16_t microseconds = throttle_to_microseconds(esc, throttle);

    if(microseconds != -1)
    {
        esc_set_microseconds(esc, (uint16_t) microseconds);
        result = 0;
    }

    return result;

}

int esc_set_microseconds(esc_t *esc, uint16_t microseconds)
{
    ppm_set_microseconds(esc->ppm_channel, microseconds);
}

int esc_update(esc_t *esc)
{
    return ppm_update(esc->ppm_channel);
}

static uint16_t throttle_to_microseconds(esc_t *esc, float throttle)
{
    int16_t microseconds = -1;

    //going from min-max range to 0 to 100%. 
    //I should be able to take the delta from min-max,
    //and multiply that delta by the desired throttle.
    //then I add back the minimum microseconds


    //Valid throttle values are [0, 1]
    if (throttle >= 0 && throttle <= 1)
    {
        microseconds = (int16_t)( (float)(esc->max_microseconds - esc->min_microseconds) * throttle) + (int16_t)esc->min_microseconds;
    }

    return microseconds;

}