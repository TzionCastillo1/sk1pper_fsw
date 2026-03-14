/**
 * @file housekeeper.h
 * @author Tzion Castillo (tzionmcastillo@gmail.com)
 * @brief Manages all of the non-flight critical data gathering.
 *      - Queue Heartbeat
 *      - Check battery voltage
 *      - Control indicator LEDs
 *      - Retrieve/set parameters
 * @version 0.1
 * @date 2026-02-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef HOUSEKEEPER_H
#define HOUSEKEEPER_H

#include "cmsis_os2.h"

QueueHandle_t hk_queue;




#endif //HOUSEKEEPER_H