#ifndef SENSOR_MGR_H
#define SENSOR_MGR_H

#include "stdint.h"
#include "errors.h"
#include "stdbool.h"

/**************** Some Helpful Conversion Constants *********************/
/**
 * @brief Constant to convert from G's to milli-G's
 */
#define GS_TO_MGS (1000.0f)
/**
 * @brief Constant to convert from Degrees to Radians
 */
#define DEG_TO_RAD (3.1415/180.0)
/**
 * @brief Constant to convert from Degrees per Second to milli-Radians per Second
 */
#define DPS_TO_MRADS (1000.0*DEG_TO_RAD)
/**********************************************************************/

typedef struct sensor_data_t
{
    float gyro[3];
    float acc[3];
    float alt;
    float pres;
}sensor_data_t;

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

/**************** Functions to return last updated sensor data **************/

/**
 * @brief Provides the latest read values from all sensors. 
 * 
 * @param data structure to contain all data
 * 
 * @return error_t 
 */
error_t sensormgr_get_all(sensor_data_t *data);

/**
 * @brief Provides the latest read values from the gyroscope. 
 * 
 * @param gyro_val gyroscope values in rad/s, in the order
 * [x,y,z] 
 * @return error_t 
 */
error_t sensormgr_get_gyro(float gyro_val[3]);

/**
 * @brief Provides the latest read values from the accelerometer. 
 * 
 * @param acc_val accelerometer values in m/s/s, in the order
 * [x, y, z] 
 * @return error_t 
 */
error_t sensormgr_get_acc(float acc_val[3]);

/**
 * @brief Provides the latest pressure value from the barometer. 
 * 
 * @param baro_alt barometer altitude value in Pa
 * @return error_t 
 */
error_t sensormgr_get_baro_pres(float *baro_alt);


/**
 * @brief Provides the latest read altitude value from the barometer. 
 * 
 * @param baro_alt barometer altitude value in meters Above Sea Level (ASL)
 * @return error_t 
 */
error_t sensormgr_get_baro_alt(float *baro_alt);

/**************** Functions to pull new data from sensors **************/

/**
 * @brief Pulls the latest readings from all of the sensors
 * 
 * @param data 
 * @return error_t 
 */
error_t sensormgr_update_all();

/**
 * @brief Reads the current gyro values from the sensor. 
 * 
 * @param gyro_val gyroscope values in rad/s, in the order
 * [x,y,z] 
 * @return error_t 
 */
error_t sensormgr_update_gyro();

/**
 * @brief Reads the current accelerometer values from the sensor. 
 * 
 * @param acc_val accelerometer values in G's, in the order
 * [x, y, z] 
 * @return error_t 
 */
error_t sensormgr_update_acc();

/**
 * @brief Reads the current barometer altitude and pressue values from the sensor. 
 * 
 * @param baro_alt barometer altitude value in meters Above Sea Level (ASL)
 * @return error_t 
 */
error_t sensormgr_update_baro();

#endif //SENSOR_MGR_H