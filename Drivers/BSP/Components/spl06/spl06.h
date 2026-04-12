#ifndef SPL06_H
#define SPL06_H

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"

//REGISTER DEFINITIONS

/*PRESSURE RAW DATA REGISTERS*/
#define SPL06_PRS_B2    0x00
#define SPL06_PRS_B1    0x01
#define SPL06_PRS_B0    0x02

#define SPL06_TMP_B2    0x03
#define SPL06_TMP_B1    0x04
#define SPL06_TMP_B0    0x05

/*TEMPERATURE RAW DATA REGISTERS*/

/*CONFIGURATION REGISTERS*/
#define SPL06_PRS_CFG   0x06
#define SPL06_TEMP_CFG  0x07
#define SPL06_MEAS_CFG  0x08
#define SPL06_CFG_REG   0x09
#define SPL06_INT_STS   0x0A
#define SPL06_FIFO_STS  0x0B
#define SPL06_RESET     0x0C
#define SPL06_ID        0x0D

/*CALIBRATION COEFFICIENT REGISTERS*/
#define SPL06_COEF_C0_UPPER             0x10
#define SPL06_COEF_C0_LOWER_C1_UPPER    0x11
#define SPL06_COEF_C1_LOWER             0x12
#define SPL06_COEF_C00_UPPER            0x13
#define SPL06_COEF_C00_MID              0x14
#define SPL06_COEF_C00_LOWER_C10_UPPER  0x15
#define SPL06_COEF_C10_MID              0x16
#define SPL06_COEF_C10_LOWER            0x17
#define SPL06_COEF_C01_UPPER            0x18
#define SPL06_COEF_C01_LOWER            0x19
#define SPL06_COEF_C11_UPPER            0x1A
#define SPL06_COEF_C11_LOWER            0x1B
#define SPL06_COEF_C20_UPPER            0x1C
#define SPL06_COEF_C20_LOWER            0x1D
#define SPL06_COEF_C21_UPPER            0x1E
#define SPL06_COEF_C21_LOWER            0x1F
#define SPL06_COEF_C30_UPPER            0x20
#define SPL06_COEF_C30_LOWER            0x21

/*USEFUL CONSTANTS */
#define SPL06_EXPECTED_ID_VAL 0x10

#define SPL06_DEFAULT_TIMEOUT_MS 20

#define SPL06_SOFT_RST_VAL 0b1001

#define SPL06_RESET_DELAY 40U

#define SPL06_P_SHIFT_OFFSET 2U

#define SPL06_T_SHIFT_OFFSET 3U

#define SPL06_TMP_EXT   0b1 << 7

#define SPL06_TMP_INT   0U

#define SPL06_PRES_RATE_OFFSET 4U

#define SPL06_TEMP_RATE_OFFSET 4U

#define SPL06_DATA_SIZE 3U

#define PRES_AT_SEA_LEVEL 1013.25

/* =============== Public Types =============*/

typedef enum spl06_Pres_Rate_t
{
    SPL06_PRES_RATE_1HZ = 0,
    SPL06_PRES_RATE_2HZ,
    SPL06_PRES_RATE_4HZ,
    SPL06_PRES_RATE_8HZ,
    SPL06_PRES_RATE_16HZ,
    SPL06_PRES_RATE_32HZ,
    SPL06_PRES_RATE_64HZ,
    SPL06_PRES_RATE_128HZ
}spl06_Pres_Rate_t;

typedef enum spl06_Pres_Over_Sample_t
{
    SPL06_PRES_OVERSAMPLE_1 = 0,
    SPL06_PRES_OVERSAMPLE_2,
    SPL06_PRES_OVERSAMPLE_4,
    SPL06_PRES_OVERSAMPLE_8,
    SPL06_PRES_OVERSAMPLE_16,
    SPL06_PRES_OVERSAMPLE_32,
    SPL06_PRES_OVERSAMPLE_64,
    SPL06_PRES_OVERSAMPLE_128
}spl06_Pres_Over_Sample_t;

typedef enum spl06_Temp_Over_Sample_t
{
    SPL06_TEMP_OVERSAMPLE_1 = 0,
    SPL06_TEMP_OVERSAMPLE_2,
    SPL06_TEMP_OVERSAMPLE_4,
    SPL06_TEMP_OVERSAMPLE_8,
    SPL06_TEMP_OVERSAMPLE_16,
    SPL06_TEMP_OVERSAMPLE_32,
    SPL06_TEMP_OVERSAMPLE_64,
    SPL06_TEMP_OVERSAMPLE_128
}spl06_Temp_Over_Sample_t;

typedef enum spl06_Temp_Rate_t
{
    SPL06_TEMP_RATE_1HZ = 0,
    SPL06_TEMP_RATE_2HZ,
    SPL06_TEMP_RATE_4HZ,
    SPL06_TEMP_RATE_8HZ,
    SPL06_TEMP_RATE_16HZ,
    SPL06_TEMP_RATE_32HZ,
    SPL06_TEMP_RATE_64HZ,
    SPL06_TEMP_RATE_128HZ
}spl06_Temp_Rate_t;

typedef enum spl06_Scale_Factor_t
{
    SPL06_SCALE_FACTOR_1 = 524288,
    SPL06_SCALE_FACTOR_2 = 1572864,
    SPL06_SCALE_FACTOR_4 = 3670016,
    SPL06_SCALE_FACTOR_8 = 7864320,
    SPL06_SCALE_FACTOR_16 = 253952,
    SPL06_SCALE_FACTOR_32 = 516096,
    SPL06_SCALE_FACTOR_64 = 1040384,
    SPL06_SCALE_FACTOR_128 = 2088960
}spl06_Scale_Factor_t;

typedef enum spl06_Meas_Cntrl_t
{
    SPL06_MEAS_IDLE = 0,
    SPL06_PRES_CMD,
    SPL06_TEMP_CMD,
    SPL06_PRES_CONT = 5,
    SPL06_TEMP_CONT,
    SPL06_PRES_TEMP_CONT
}spl06_Meas_Cntrl_t;

typedef enum spl06_Status_t
{
    SPL06_OK,
    SPL06_UNINIT,
    SPL06_ERR
}spl06_Status_t;

typedef struct spl06_Handle_t
{
    I2C_HandleTypeDef *hi2c;
    uint8_t addr;
    int32_t pres_oversample;
    int32_t temp_oversample;
    int32_t kT;
    int32_t kP;
    int32_t c00;
    int32_t c10;
    int16_t c20;
    int16_t c30;
    int16_t c01;
    int16_t c11;
    int16_t c21;
    int16_t c0;
    int16_t c1;
}spl06_Handle_t;


/* =============== Public Functions ============*/

/**
 * @brief Handles the initialization of the SPL06 device and checks connection via the ID register.
 * May take up to 40ms to run.
 * 
 * @param hspl06 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_init(spl06_Handle_t *hspl06);

/**
 * @brief 
 * 
 * @param hspl06 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_start(spl06_Handle_t *hspl06);

spl06_Status_t spl06_stop(spl06_Handle_t *hspl06);

/**
 * @brief Performs a soft reset on the device.
 * Wait for 40 ms after reset before reading from registers
 * 
 * @param hspl06 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_reset(spl06_Handle_t *hspl06);

/**
 * @brief Retrieve calibration data and update local parameters.
 * 
 * @param hspl06 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_get_cal(spl06_Handle_t *hspl06);

/**
 * @brief Set the oversampling and measurement rate for the pressure transducer
 * 
 * @param hslp06 
 * @param pres_over_sample 
 * @param pres_rate 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_set_pres_cfg(spl06_Handle_t *hslp06, spl06_Pres_Over_Sample_t pres_over_sample, spl06_Pres_Rate_t pres_rate);

/**
 * @brief Set the oversampling and measurement rate for the temperature sensor
 * 
 * @param hslp06 
 * @param temp_over_sample 
 * @param temp_rate 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_set_temp_cfg(spl06_Handle_t *hslp06, spl06_Temp_Over_Sample_t temp_over_sample, spl06_Temp_Rate_t temp_rate);

/**
 * @brief reads latest raw pressure register values
 * 
 * @param hspl06 
 * @param raw_pres 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_raw_pres(spl06_Handle_t *hspl06, int32_t *raw_pres);

/**
 * @brief reads latest raw temperature register values 
 * 
 * @param hspl06 
 * @param raw_temp 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_raw_temp(spl06_Handle_t *hspl06, int32_t *raw_temp);

/**
 * @brief returns the pressure scaled to a dimensionless value between 1 and -1
 * 
 * @param hspl06 
 * @param scaled_pres 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_scaled_pres(spl06_Handle_t *hspl06, float *scaled_pres);

/**
 * @brief returns the temperature scaled to a dimensionless value between 1 and -1 
 * 
 * @param hspl06 
 * @param scaled_temp 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_scaled_temp(spl06_Handle_t *hspl06, float *scaled_temp);

/**
 * @brief returns the pressure in Pascals (Pa)
 * 
 * @param hspl06 
 * @param comp_pres 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_comp_pres(spl06_Handle_t *hspl06, float *comp_pres);

/**
 * @brief returns the temperature in Celsius 
 * 
 * @param hspl06 
 * @param comp_temp 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_comp_temp(spl06_Handle_t *hspl06, float *comp_temp);

/**
 * @brief Reads teh factory-provided calibration coefficients used for calculating compensated pressure
 * and temperature 
 * 
 * @param hspl06 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_cal(spl06_Handle_t *hspl06);

/**
 * @brief reads the device ID 
 * 
 * @param hspl06 
 * @param id 
 * @return spl06_Status_t 
 */
spl06_Status_t spl06_read_id(spl06_Handle_t *hspl06, uint8_t *id);

#endif /*SPL06_H*/