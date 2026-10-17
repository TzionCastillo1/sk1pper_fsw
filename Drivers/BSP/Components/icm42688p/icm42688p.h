#ifndef ICM42688P_H
#define ICM42688P_H

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"

//REGISTER DEFINITIONS 

//The only register settings that user can modify during sensor operation are for ODR selection, FSR selection, and sensor mode
//changes (register parameters GYRO_ODR, ACCEL_ODR, GYRO_FS_SEL, ACCEL_FS_SEL, GYRO_MODE, ACCEL_MODE). User must not
//modify any other register values during sensor operation.

// Bank 0 registers
/*CONFIGURATIONS*/
#define ICM42688P_DEVICE_CONFIG 0x11 // BIT 4 FOR SPI MODE SELECTION, BIT 0 FOR SOFT_RESET_CONFIG
#define ICM42688P_DRIVE_CONFIG 0x13  //BITS 2:0 DEFINE SPI SLEW RATE
#define ICM42688P_INT_CONFIG 0x14 // INT2 MODE:CIRCUITS:POLARITY >> BITS 5:4:3 //INT1 MODE:CIRCUITS:POLARITY >> BITS 2:1:0
#define ICM42688P_FIFO_CONFIG 0x16  //DEFAULT IS BYPASS MODE 00, SET BITS 7:6 TO 01 FOR STREAM TO FIFO MODE

#define ICM42688P_UPPER_TEMP_DATA 0x1D  // TEMP DATA [15:8] (Bits 9 -16)
#define ICM42688P_LOWER_TEMP_DATA 0x1E // TEMP DATA [7:0] (Bits 1- 8)
/*REMEMBER THAT TEMPERATURE BITS MUST BE CONVERTED*/

/*ACCELERATION RAW DATA REGISTERS*/
#define ICM42688P_UPPER_X_ACCEL_DATA 0x1F //X ACCL [15:8] (Bits 9-16)
#define ICM42688P_LOWER_X_ACCEL_DATA 0x20 //X ACCL [7:0] (Bits 1-8)
#define ICM42688P_UPPER_Y_ACCEL_DATA 0x21 //Y ACCL [15:8] (Bits 9-16)
#define ICM42688P_LOWER_Y_ACCEL_DATA 0x22 //Y ACCL [7:0] (Bits 1-8)
#define ICM42688P_UPPER_Z_ACCEL_DATA 0x23 //Z ACCL [15:8] (Bits 9-16)
#define ICM42688P_LOWER_Z_ACCEL_DATA 0x24 //Z ACCL [7:0] (Bits 1-8)

/*GYROSCOPE RAW DATA REGISTERS*/
#define ICM42688P_UPPER_X_GYRO_DATA 0x25 //X GYRO [15:8] (Bits 9-16)
#define ICM42688P_LOWER_X_GYRO_DATA 0x26 //X GYRO [7:0] (Bits 1-8)
#define ICM42688P_UPPER_Y_GYRO_DATA 0x27 //Y GYRO [15:8] (Bits 9-16)
#define ICM42688P_LOWER_Y_GYRO_DATA 0x28 //Y GYRO [7:0] (Bits 1-8)
#define ICM42688P_UPPER_Z_GYRO_DATA 0x29 //Z GYRO [15:8] (Bits 9-16)
#define ICM42688P_LOWER_Z_GYRO_DATA 0x2A //Z GYRO [7:0] (Bits 1-8)

/*FIFO AND DATA STREAM REGISTERS*/
#define ICM42688P_HIGH_TMST_FSYNCH 0x2B //TIME DELTA FROM LATEST OUTPUT DATA RATE OF SENSOR [15:89] Bits (9-16)
#define ICM42688P_LOW_TMST_FSYNCH 0x2C //SEE ABOVE (Bits 1-8)

#define ICM42688P_INT_STATUS_STREAM 0x2D //SEE DATA SHEET INTERACTS WITH FSYNC AND FIFO TO INDICATE STATUS OF READ. EACH BIT RESPONDS TO STATUS OF INDIVIDUAL READ TASK.

#define ICM42688P_HIGH_FIFO_COUNT 0x2E //FIFO BYTE AVAILABILITY [15:8] (Bits 9-16)
#define ICM42688P_LOW_FIFO_COUNT 0x2F //FIFO BYTE AVAILABILITY [7:0] (Bits 1-8)
#define ICM42688P_FIFO_DATA 0x30 //FIFO DATA PORT

#define ICM42688P_INT_STATUS_WAKE 0x37 //BIT 3 DETECTS SIGNIFICANT MOTION, BITS 2:1:0 ALL DETECT MOTION ON Z:Y:X AXES RESPECTIVELY

#define ICM42688P_SIGNAL_PATH_RESET 0x4B //

#define ICM42688P_WHO_AM_I 0x75 //THE CONTENTS OF WHOAMI, WHICH DEFAULTS TO 0x47

#define ICM42688P_REG_BANK_SEL 0x76 //SELECTS CURRENT REGISTER BANK

/*POWER MANAGEMENT REGISTERS*/
#define ICM42688P_PWR_MGMT0 0x4E //Enable/Disable onboard devices

/*ACCELEROMETER AND GYRO CONFIGURATION REGISTERS*/
#define ICM42688P_GYRO_CONFIG0 0x4F //SETS GYRO SCALING AND OUTPUT RATE

#define ICM42688P_ACCEL_CONFIG0 0x50 //SETS ACCELEROMETER SCALING AND OUTPUT RATE

#define ICM42688P_GYRO_CONFIG1 0x51 //SETS BW OF TEMP LPF, ORDER OF GYRO UI FILTER, ORDER OF GYRO DEC2_M2 FILTER  

#define ICM42688P_GYRO_ACCEL_CONFIG0 0x52 //SETS ACCEL LPF BW, GYRO LPF BW

#define ICM42688P_ACEL_CONFIG1 0x53 //SETS ORDER OF ACCEL UI FILTER, ORDER OF ACCEL DEC2_M2 FILTER




// USEFUL CONSTANTS
#define ICM42688P_WHO_AM_I_ID 0x47

#define ICM42688P_DEFAULT_TIMEOUT_MS 10U

#define ICM42688P_GYRO_OFF_LN_VAL (0b00 << 2)

#define ICM42688P_GYRO_ON_LN_VAL (0b11 << 2)

#define ICM42688P_ACCEL_OFF_LN_VAL (0b00 << 0)

#define ICM42688P_ACCEL_ON_LN_VAL (0b11 << 0)

#define ICM42688P_TEMP_ON_VAL   (0b1 << 4)

//GYRO SCALING FACTORS
#define ICM42688P_GYRO_SSF_2000 (1.0/16.4)

#define ICM42688P_GYRO_SSF_1000 (1.0/32.8)

#define ICM42688P_GYRO_SSF_500 (1.0/65.5)

#define ICM42688P_GYRO_SSF_250 (1.0/131.0)

#define ICM42688P_GYRO_SSF_125 (1.0/262.0)

#define ICM42688P_GYRO_SSF_62_5 (1.0/524.3)

#define ICM42688P_GYRO_SSF_31_25 (1.0/1048.6)

#define ICM42688P_GYRO_SSF_15_625 (1.0/2097.2)

//ACCELEROMETER SCALING FACTORS
#define ICM42688P_ACC_SSF_16 (1.0/2048.0)

#define ICM42688P_ACC_SSF_8 (1.0/4096.0)

#define ICM42688P_ACC_SSF_4 (1.0/8192.0)

#define ICM42688P_ACC_SSF_2 (1.0/16384.0) 

//TEMP SCALING FACTOR
#define ICM42688P_TEMP_SSF (1.0/132.48)

//TEMP OFFSET
#define ICM42688P_TEMP_OFFSET (25.0)

/* =============== Public Types =============*/
typedef enum icm42688P_Gyro_Range_t
{
    ICM42688P_GY_RANGE_2000 = 0,
    ICM42688P_GY_RANGE_1000,
    ICM42688P_GY_RANGE_500,
    ICM42688P_GY_RANGE_250,
    ICM42688P_GY_RANGE_125,
    ICM42688P_GY_RANGE_62_5,
    ICM42688P_GY_RANGE_31_25,
    ICM42688P_GY_RANGE_15_625,
} icm42688P_Gyro_Range_t;

typedef enum icm42688p_Gyro_Rate_t
{
    ICM42688P_GY_32KHZ = 0x01,
    ICM42688P_GY_16KHZ,
    ICM42688P_GY_8KHZ,
    ICM42688P_GY_4KHZ,
    ICM42688P_GY_2KHZ,
    ICM42688P_GY_1KHZ,
    ICM42688P_GY_200HZ,
    ICM42688P_GY_100HZ,
    ICM42688P_GY_50HZ,
    ICM42688P_GY_25HZ,
    ICM42688P_GY_12_5HZ,
    ICM42688p_GY_500HZ = 0xFF
}icm42688p_Gyro_Rate_t;

typedef enum icm42688P_Accel_Range_t
{
    ICM42688P_ACC_RANGE_16 = 0,
    ICM42688P_ACC_RANGE_8,
    ICM42688P_ACC_RANGE_4,
    ICM42688P_ACC_RANGE_2,
} icm42688P_Accel_Range_t;

typedef enum icm42688p_Accel_Rate_t
{
    ICM42688P_ACC_32KHZ = 0x01,
    ICM42688P_ACC_16KHZ,
    ICM42688P_ACC_8KHZ,
    ICM42688P_ACC_4KHZ,
    ICM42688P_ACC_2KHZ,
    ICM42688P_ACC_1KHZ,
    ICM42688P_ACC_200HZ,
    ICM42688P_ACC_100HZ,
    ICM42688P_ACC_50HZ,
    ICM42688P_ACC_25HZ,
    ICM42688P_ACC_12_5HZ,
    ICM42688P_ACC_6_25HZ,
    ICM42688P_ACC_3_125HZ,
    ICM42688P_ACC_1_5625HZ,
    ICM42688p_ACC_500HZ
}icm42688p_Accel_Rate_t;

typedef enum icm42688P_Status_t
{
    ICM42688P_OK,
    ICM42688P_UNINIT,
    ICM42688P_ERR
} icm42688P_Status_t;


typedef struct icm42688p_Config_t
{
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *CS_PORT;
    uint16_t CS_PIN;
    icm42688P_Accel_Range_t accel_range;
    icm42688P_Gyro_Range_t gyro_range;
    uint32_t spi_clk;
} icm42688p_Config_t;

typedef struct icm42688p_Handle_t
{
    bool is_init;
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *CS_PORT;
    uint16_t CS_PIN;
    uint32_t spi_clk;
    icm42688P_Accel_Range_t accel_range;
    icm42688p_Accel_Rate_t accel_rate;
    float accel_scaling_factor;
    icm42688P_Gyro_Range_t gyro_range;
    icm42688p_Gyro_Rate_t gyro_rate;
    float gyro_scaling_factor;
}icm42688p_Handle_t;

typedef struct imu_data_t
{
    float accel[3];
    float gyro[3];
    float temp;
} imu_data_t;

/* =============== Public Functions ============*/

/**
 * @brief Handles the intialization of the ICM42688P device and checks for connection via the whoami register and 
 * 
 * @param hicm42688p 
 * @param icm42688p_config 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_init(icm42688p_Handle_t *hicm42688p);

/**
 * @brief Enables the gyro and acc.
 * 
 * @param hicm42688p 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_start(icm42688p_Handle_t *hicm42688p);

/**
 * @brief Disables the gyro, acc.
 * 
 * @param hicm42688p 
 * @return icm42688P_Status_t 
 */
icm42688P_Status_t icm42688p_stop(icm42688p_Handle_t *hicm42688p);

/**
 * @brief Perform a soft reset on the IMU IC
 * 
 * @param hicm42688p 
 * @return icm42688P_Status_t 
 */
icm42688P_Status_t icm42688p_reset(icm42688p_Handle_t *hicm42688p);

/**
 * @brief read latest values from accelerometer values
 * 
 * @param hicm42688p 
 * @param gyro_vals
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_raw_gyro(icm42688p_Handle_t *hicm42688p, int16_t gyro_vals[3]);

/**
 * @brief read latest values from accelerometer values.
 * 
 * @param hicm42688p 
 * @param acc_vals 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_raw_acc(icm42688p_Handle_t *hicm42688p, int16_t acc_vals[3]);

/**
 * @brief Read latest value from temperature register.
 * 
 * @param hicm42688p 
 * @param temp 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_raw_temp(icm42688p_Handle_t *hicm42688p, int16_t *temp);

/**
 * @brief Read latest gyroscope values and perform scaling to return value in dps
 * 
 * @param hicm42688p 
 * @param gyro_vals 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_scaled_gyro(icm42688p_Handle_t *hicm42688p, float gyro_vals[3]);

/**
 * @brief Read latest accelerometer values and perform scaling to return value in g's
 * 
 * @param hicm42688p 
 * @param acc_vals 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_scaled_acc(icm42688p_Handle_t *hicm42688p, float acc_vals[3]);

/**
 * @brief Read latest temp and perform scaling to return value in *C.
 * 
 * @param hicm42688p 
 * @param temp 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_scaled_temp(icm42688p_Handle_t *hicm42688p, float *temp);

/**
 * @brief Reads latest register values for all sensors.
 * 
 * @param hicm42688p 
 * @param imu_data 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_sensors(icm42688p_Handle_t *hicm42688p, imu_data_t *imu_data);

/**
 * @brief Reads the WHOAMI register, and puts the value at id.
 * 
 * @param hicm42688p 
 * @param id 
 * 
 * @return if succesful returns ICM42688P_OK
 */
icm42688P_Status_t icm42688p_read_who_am_i(icm42688p_Handle_t *hicm42688p, uint8_t *id);

#endif /* ICM42688P_H */

