#include "spl06.h"
#include "stm32_assert.h"

#include "printf/printf.h"

static inline int16_t bytes_to_int16(uint8_t byte_lo, uint8_t byte_up);
static inline int32_t bytes_to_int24(uint8_t byte_lo, uint8_t byte_mid, uint8_t byte_hi);
static inline int16_t int12_int16_sign_extend(int16_t unextended);
static inline int32_t int20_int32_sign_extend(int32_t unextended);
static inline int32_t int24_int32_sign_extend(int32_t unextended);

spl06_Status_t spl06_init(spl06_Handle_t *hspl06)
{
    uint8_t id;
    spl06_reset(hspl06);
    HAL_Delay(SPL06_RESET_DELAY);
    spl06_read_id(hspl06, &id);
    assert_param(id == SPL06_EXPECTED_ID_VAL);

    spl06_get_cal(hspl06);

    /** Default config, based on datasheet's 'Sports' use case */
    hspl06->pres_oversample = SPL06_PRES_OVERSAMPLE_64;
    spl06_set_pres_cfg(hspl06, hspl06->pres_oversample, SPL06_PRES_RATE_4HZ);
    hspl06->kP = SPL06_SCALE_FACTOR_64;
    hspl06->temp_oversample = SPL06_TEMP_OVERSAMPLE_1;
    spl06_set_temp_cfg(hspl06, hspl06->temp_oversample, SPL06_TEMP_RATE_4HZ);
    hspl06->kT = SPL06_SCALE_FACTOR_1;
}


spl06_Status_t spl06_start(spl06_Handle_t *hspl06)
{
    uint8_t rxData;
    uint8_t txData;

    /** Read MEAS_CFG register */
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_MEAS_CFG, I2C_MEMADD_SIZE_8BIT, &rxData, 1, SPL06_DEFAULT_TIMEOUT_MS);

    /** Set lowest 3 bits to desired measurement state */
    txData = rxData;
    txData = (txData & 0b11111000) | SPL06_PRES_TEMP_CONT;

    /**Write MEAS_CFG register */
    HAL_I2C_Mem_Write(hspl06->hi2c, hspl06->addr, SPL06_MEAS_CFG, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);

}

spl06_Status_t spl06_stop(spl06_Handle_t *hspl06)
{
    uint8_t rxData;
    uint8_t txData;

    /** Read MEAS_CFG register */
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_MEAS_CFG, I2C_MEMADD_SIZE_8BIT, &rxData, 1, SPL06_DEFAULT_TIMEOUT_MS);

    /** Set lowest 3 bits to desired measurement state */
    txData = rxData;
    txData = (txData & 0b000) | SPL06_MEAS_IDLE;

    /**Write MEAS_CFG register */
    HAL_I2C_Mem_Write(hspl06->hi2c, hspl06->addr, SPL06_MEAS_CFG, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);
}

spl06_Status_t spl06_reset(spl06_Handle_t *hspl06)
{
    uint8_t txData = SPL06_SOFT_RST_VAL;
    HAL_I2C_Mem_Write(hspl06->hi2c, hspl06->addr, SPL06_RESET, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);
}

spl06_Status_t spl06_get_cal(spl06_Handle_t *hspl06)
{
    uint8_t rxDataTemp[3];
    uint8_t rxDataPres[15];
    /** Read from the 3 sequential temperature calibration registers */
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_COEF_C0_UPPER, I2C_MEMADD_SIZE_8BIT, rxDataTemp, 3, SPL06_DEFAULT_TIMEOUT_MS);
    /** Read from the 15 sequential temperature calibration registers */
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_COEF_C00_UPPER, I2C_MEMADD_SIZE_8BIT, rxDataPres, 15, SPL06_DEFAULT_TIMEOUT_MS);

    /** Temp Calibration Coefficients Processing */
    hspl06->c0 = int12_int16_sign_extend(((int16_t) rxDataTemp[0] << 4) | ( ((int16_t) rxDataTemp[1] & 0xF0) >> 4));
    hspl06->c1 = int12_int16_sign_extend(((int16_t) (rxDataTemp[1] & 0x0F) << 8) | (int16_t) rxDataTemp[2]);

    hspl06->c00 = int20_int32_sign_extend(((int32_t) rxDataPres[0] << 12) | ((int32_t) rxDataPres[1] << 4) | ((int32_t) (rxDataPres[2] & 0xF0) >> 4));
    hspl06->c10 = int20_int32_sign_extend(((int32_t) (rxDataPres[2] & 0x0F) << 16) | ((int32_t) rxDataPres[3] << 8) | (int32_t) rxDataPres[4]);

    hspl06->c01 = bytes_to_int16(rxDataPres[6],rxDataPres[5]);
    hspl06->c11 = bytes_to_int16(rxDataPres[8],rxDataPres[7]);
    hspl06->c20 = bytes_to_int16(rxDataPres[10],rxDataPres[9]);
    hspl06->c21 = bytes_to_int16(rxDataPres[12],rxDataPres[11]);
    hspl06->c30 = bytes_to_int16(rxDataPres[14],rxDataPres[13]);

}

spl06_Status_t spl06_set_pres_cfg(spl06_Handle_t *hslp06, spl06_Pres_Over_Sample_t pres_over_sample, spl06_Pres_Rate_t pres_rate)
{
    uint8_t txData = (pres_rate << SPL06_PRES_RATE_OFFSET) | (pres_over_sample);
    HAL_I2C_Mem_Write(hslp06->hi2c, hslp06->addr, SPL06_PRS_CFG, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);
    
    /** Set bit shift in interrupt and fifo config reg if needed */
    if(pres_over_sample > SPL06_PRES_OVERSAMPLE_8)
    {
        uint8_t rxData;
        HAL_I2C_Mem_Read(hslp06->hi2c, hslp06->addr, SPL06_CFG_REG, I2C_MEMADD_SIZE_8BIT, &rxData, 1, SPL06_DEFAULT_TIMEOUT_MS);
        txData = rxData | (1 << SPL06_P_SHIFT_OFFSET);
        HAL_I2C_Mem_Write(hslp06->hi2c, hslp06->addr, SPL06_CFG_REG, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);
    }
    
}

spl06_Status_t spl06_set_temp_cfg(spl06_Handle_t *hslp06, spl06_Temp_Over_Sample_t temp_over_sample, spl06_Temp_Rate_t temp_rate)
{
    uint8_t rxData = HAL_I2C_Mem_Read(hslp06->hi2c, hslp06->addr, SPL06_TEMP_CFG, I2C_MEMADD_SIZE_8BIT, &rxData, 1, SPL06_DEFAULT_TIMEOUT_MS);
    //Maintain the reserved data at bit 3
    uint8_t txData = SPL06_TMP_EXT | (temp_rate << SPL06_TEMP_RATE_OFFSET) | (rxData & 0b00001000) | (temp_over_sample);
    HAL_I2C_Mem_Write(hslp06->hi2c, hslp06->addr, SPL06_TEMP_CFG, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);
    
    /** Set bit shift in interrupt and fifo config reg if needed */
    if(temp_over_sample > SPL06_TEMP_OVERSAMPLE_8)
    {
        uint8_t rxData;
        HAL_I2C_Mem_Read(hslp06->hi2c, hslp06->addr, SPL06_CFG_REG, I2C_MEMADD_SIZE_8BIT, &rxData, 1, SPL06_DEFAULT_TIMEOUT_MS);
        txData = rxData | (1 << SPL06_T_SHIFT_OFFSET);
        HAL_I2C_Mem_Write(hslp06->hi2c, hslp06->addr, SPL06_CFG_REG, I2C_MEMADD_SIZE_8BIT, &txData, 1, SPL06_DEFAULT_TIMEOUT_MS);
    }
    
}

spl06_Status_t spl06_read_raw_pres(spl06_Handle_t *hspl06, int32_t *raw_pres)
{
    uint8_t rxData[3];
    uint8_t data_bit_shift = 0;

    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_PRS_B2, I2C_MEMADD_SIZE_8BIT, rxData, SPL06_DATA_SIZE, SPL06_DEFAULT_TIMEOUT_MS);
    *raw_pres = int24_int32_sign_extend(bytes_to_int24(rxData[2], rxData[1], rxData[0]));
}

spl06_Status_t spl06_read_raw_temp(spl06_Handle_t *hspl06, int32_t *raw_temp)
{
    uint8_t rxData[3];
    uint8_t data_bit_shift = 0;

    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_TMP_B2, I2C_MEMADD_SIZE_8BIT, rxData, SPL06_DATA_SIZE, SPL06_DEFAULT_TIMEOUT_MS);

    *raw_temp = int24_int32_sign_extend(bytes_to_int24(rxData[2], rxData[1], rxData[0]));
}

spl06_Status_t spl06_read_scaled_pres(spl06_Handle_t *hspl06, float *scaled_pres)
{
    int32_t temporary_raw_pres;
    spl06_read_raw_pres(hspl06, &temporary_raw_pres);
    *scaled_pres = (float)temporary_raw_pres/hspl06->kP;
}

spl06_Status_t spl06_read_scaled_temp(spl06_Handle_t *hspl06, float *scaled_temp)
{
    int32_t temporary_raw_temp;
    spl06_read_raw_temp(hspl06, &temporary_raw_temp);
    *scaled_temp = (float)temporary_raw_temp/hspl06->kT;

}

spl06_Status_t spl06_read_comp_pres(spl06_Handle_t *hspl06, float *comp_pres)
{
    float Praw_sc;
    float Traw_sc;
    spl06_read_scaled_pres(hspl06, &Praw_sc);
    spl06_read_scaled_temp(hspl06, &Traw_sc);

    *comp_pres = ( hspl06->c00 + Praw_sc * (hspl06->c10 + Praw_sc * (hspl06->c20 + Praw_sc * hspl06->c30)) 
                    + Traw_sc * hspl06->c01 
                    + Traw_sc * Praw_sc * (hspl06->c11 + Praw_sc * hspl06->c21) );

    printf_("term2 c10*Praw_sc: %f\n", Praw_sc * hspl06->c10);
    printf_("term3 c20*Praw_sc^2: %f\n", Praw_sc * Praw_sc * hspl06->c20);
    printf_("term4 c30*Praw_sc^3: %f\n", Praw_sc * Praw_sc * Praw_sc * hspl06->c30);
    printf_("term5 Traw_sc*c01: %f\n", Traw_sc * hspl06->c01);
    printf_("term6 Traw_sc*Praw_sc*c11: %f\n", Traw_sc * Praw_sc * hspl06->c11);
    printf_("term7 Traw_sc*Praw_sc^2*c21: %f\n", Traw_sc * Praw_sc * Praw_sc * hspl06->c21);
}

spl06_Status_t spl06_read_comp_temp(spl06_Handle_t *hspl06, float *comp_temp)
{
    float Traw_sc;
    spl06_read_scaled_temp(hspl06, &Traw_sc);
    *comp_temp = hspl06->c0*0.5 + hspl06->c1*Traw_sc;
}

spl06_Status_t spl06_read_id(spl06_Handle_t *hspl06, uint8_t *id)
{
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_ID, I2C_MEMADD_SIZE_8BIT, id, 1, SPL06_DEFAULT_TIMEOUT_MS);
}

/** Private functions */
inline int16_t bytes_to_int16(uint8_t byte_lo, uint8_t byte_hi)
{
    //Shift upper byte to the left 8 bits and apply a bitmask.
    return (int16_t) ((int16_t)byte_hi << 8) | (int16_t) byte_lo;
}

inline int32_t bytes_to_int24(uint8_t byte_lo, uint8_t byte_mid, uint8_t byte_hi)
{
    return (int32_t) ((int32_t)byte_hi << 16) | ((int32_t)byte_mid <<  8) | ((int32_t) byte_lo);
}

inline int16_t int12_int16_sign_extend(int16_t unextended)
{
    int16_t extended = unextended;
    if(unextended & 0b100000000000)
    {
        extended |= 0b1111100000000000;
    }
    return extended;
}

inline int32_t int20_int32_sign_extend(int32_t unextended)
{
    int32_t extended = unextended;
    if (unextended & 0b10000000000000000000)
    {
        extended |= 0b11111111111110000000000000000000;
    }
    return extended;
}

inline int32_t int24_int32_sign_extend(int32_t unextended)
{
    int32_t extended = unextended;
    if (unextended & 0b100000000000000000000000)
    {
        extended |= 0b11111111000000000000000000000000;
    }
    return extended;
}