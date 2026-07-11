/**
 * @file param_mgr.h
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

#ifndef PARAM_MGR_H
#define PARAM_MGR_H

#include "stdint.h"
#include "errors.h"
#include "gnc_params.h"

/**
 * @brief initialize the parameter table. Pulls from flash where available.
 * Uses defaults when flash does not contain a parameter.
 * 
 * @return error_t 
 */
error_t param_mgr_init(void);

error_t param_mgr_get(char *key, float *value);

error_t param_mgr_get_gnc(gnc_params_t *gnc_params);

error_t param_mgr_set(char *key, float value);

error_t param_mgr_save(void);

error_t param_mgr_load(void);

error_t param_mgr_find(char *key, int *idx);


#endif //PARAMMANAGER_H