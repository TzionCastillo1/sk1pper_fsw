#ifndef ESC_CFG_H
#define ESC_CFG_H

#include "esc.h"

#define ESC_FREQUENCY               50U
#define ESC_PERIOD_US               (1000000 / ESC_FREQUENCY)
//Timer tick period (us) = prescaler * 1000000/clock frequency 
#define ESC_TICKS_PER_US            (7000.0F / 20000.0F)

#define ESC_DEFAULT_MIN_MICROSECONDS    1000U
#define ESC_DEFAULT_MAX_MICROSECONDS    2000U   
#define ESC_DEFAULT_TRIM_MICROSECONDS   1000U

extern esc_t esc_main;

#endif //ESC_CFG_H