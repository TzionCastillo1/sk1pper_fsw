#ifndef SENSOR_MGR_H
#define SENSOR_MGR_H

#include "stdint.h"
#include "errors.h"
#include "stdbool.h"

/**
 * @brief Intialize the sensor manager module 
 * 
 * @return error_t 
 */
error_t sensormgr_init(void); 

/**
 * @brief Calibrate the gyroscope 
 * 
 * @return error_t 
 */
error_t sensormgr_cal_gryo(void);

/**
 * @brief Calibrate the accelerometer 
 * 
 * @return error_t 
 */
error_t sensormgr_cal_acc(void);

/**
 * @brief Calibrate the barometer 
 * 
 * @return error_t 
 */
error_t sensormgr_cal_baro(void);

/**
 * @brief Reads the current gyro values from the sensor. 
 * 
 * @param gyro_val gyroscope values in rad/s, in the order
 * [x,y,z] 
 * @return error_t 
 */
error_t sensormgr_read_gyro(float gyro_val[3]);

/**
 * @brief Reads the current accelerometer values from the sensor. 
 * 
 * @param acc_val accelerometer values in m/s/s, in the order
 * [x, y, z] 
 * @return error_t 
 */
error_t sensormgr_read_acc(float acc_val[3]);

/**
 * @brief Reads the current barometer pressue value from the sensor. 
 * 
 * @param baro_alt barometer altitude value in Pa
 * @return error_t 
 */
error_t sensormgr_read_baro_pres(float *baro_alt);


/**
 * @brief Reads the current barometer altitude value from the sensor. 
 * 
 * @param baro_alt barometer altitude value in meters Above Sea Level (ASL)
 * @return error_t 
 */
error_t sensormgr_read_baro_alt(float *baro_alt);
#endif //SENSOR_MGR_H