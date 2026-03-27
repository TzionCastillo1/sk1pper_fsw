#ifndef SPL06_H
#define SPL06_H

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"

//REGISTER DEFINITIONS

/*PRESSURE RAW DATA REGISTERS*/

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

/* =============== Public Types =============*/
/*
typedef enum spl06_Pres_Rate_t
{

}spl06_Pres_Rate_t;

typedef enum spl06_Pres_Over_Sample_t
{

}spl06_Pres_Over_Sample_t;

typedef enum spl06_Temp_Rate_t
{

}spl06_Temp_Rate_t;

typedef enum spl06_Temp_Over_Sample_t
{

}spl06_Temp_Over_Sample_t;
*/
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

spl06_Status_t spl06_read_raw_pres(spl06_Handle_t *hspl06, int32_t *raw_pres);

spl06_Status_t spl06_read_raw_temp(spl06_Handle_t *hspl06, int32_t *raw_temp);

spl06_Status_t spl06_read_scaled_pres(spl06_Handle_t *hspl06, int32_t *scaled_pres);

spl06_Status_t spl06_read_scaled_temp(spl06_Handle_t *hspl06, int32_t *scaled_temp);

spl06_Status_t spl06_read_comp_pres(spl06_Handle_t *hspl06, int32_t *comp_pres);

spl06_Status_t spl06_read_comp_temp(spl06_Handle_t *hspl06, int32_t *comp_temp);

spl06_Status_t spl06_read_cal(spl06_Handle_t *hspl06);

spl06_Status_t spl06_read_id(spl06_Handle_t *hspl06, uint8_t *id);

#endif /*SPL06_H*/