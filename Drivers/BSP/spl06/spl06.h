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


/* =============== Public Types =============*/
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

typedef enum spl06_Status_t
{
    SPL06_OK,
    SPL06_UNINIT,
    SPL06_ERR
}spl06_Status_t;

 typedef struct spl06_Handle_t
 {

 }spl06_Handle_t;

/* =============== Public Functions ============*/

spl06_Status_t spl06_init(spl06_Handle_t *hspl06);

spl06_Status_t spl06_start(spl06_Handle_t *hspl06);

spl06_Status_t spl06_stop(spl06_Handle_t *hspl06);

spl06_Status_t spl06_reset(spl06_Handle_t *hspl06);

spl06_Status_t spl06_read_raw_pres(spl06_Handle_t *hspl06, int32_t *raw_pres);

spl06_Status_t spl06_read_raw_temp(spl06_Handle_t *hspl06, int32_t *raw_temp);

spl06_Status_t spl06_read_scaled_pres(spl06_Handle_t *hspl06, int32_t *scaled_pres);

spl06_Status_t spl06_read_scaled_temp(spl06_Handle_t *hspl06, int32_t *scaled_temp);

spl06_Status_t spl06_read_comp_pres(spl06_Handle_t *hspl06, int32_t *comp_pres);

spl06_Status_t spl06_read_comp_temp(spl06_Handle_t *hspl06, int32_t *comp_temp);

spl06_Status_t spl06_read_cal(spl06_Handle_t *hspl06);

#endif /*SPL06_H*/