/**
 * @file parammanager.h
 * @author Tzion Castillo (tzionmcastillo@gmail.com)
 * @brief Manages the modification and retreival of system parameters.
 * @version 0.1
 *   -Set/retrieve parameters
 *   -initialize
 *   -Save parameters to flash
 *   -Mavlink uses strings as parameter IDs
 *   -Parameters should all be floats
 * @date 2026-01-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H
#include "stdint.h"


typedef enum {
    PARAM_OK,
    PARAM_NOT_SUPPORTED
} Param_Status_t;

typedef enum
{
    PARAM_BOOL,
    PARAM_NUM,
} Param_Type_t;

typedef struct 
{
    char id[16];
    Param_Type_t type;
    float value;
} Parameter_t;


Param_Status_t ParamManager_init(void);

Param_Status_t ParamManager_get_param_name(char* id, Parameter_t Param);

Param_Status_t ParamManager_get_param_index(uint16_t index, Parameter_t Param);

Param_Status_t ParamManager_set_param(char* id, float value);

Param_Status_t ParamManager_save(char* id);

#endif //PARAMMANAGER_H