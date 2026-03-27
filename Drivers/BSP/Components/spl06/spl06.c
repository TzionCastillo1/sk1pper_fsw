#include "spl06.h"
#include "stm32_assert.h"

static inline int16_t bytes_to_int16(uint8_t byte_lo, uint8_t byte_up);

spl06_Status_t spl06_init(spl06_Handle_t *hspl06)
{
    /**
     * TODO:
     * reset*
     * verify ID*
     * get calibration coefficients
     * setup temp cfg
     * setup pres cfg 
     * Get temp cal
     * Get pres cal
     */

    uint8_t id;
    spl06_reset(hspl06);
    HAL_Delay(SPL06_RESET_DELAY);
    spl06_read_id(hspl06, &id);
    assert_param(id == SPL06_EXPECTED_ID_VAL);

    spl06_get_cal(hspl06);
}


spl06_Status_t spl06_start(spl06_Handle_t *hspl06)
{
    /**
     * TODO:
     * Put device into background mode
     * 
     */
}

spl06_Status_t spl06_stop(spl06_Handle_t *hspl06)
{
    /**
     * TODO:
     * Put device into standby mode 
     * 
     */
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
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_COEF_C0_UPPER, I2C_MEMADD_SIZE_8BIT, rxDataPres, 15, SPL06_DEFAULT_TIMEOUT_MS);

    /** Temp Calibration Coefficients Processing */
    hspl06->c0 = ((int16_t) rxDataTemp[0] << 4) | ( ((int16_t) rxDataTemp[1] & 0xF0) >> 4);
    hspl06->c1 = ((int16_t) (rxDataTemp[1] & 0xF0) << 4) | (int16_t) rxDataTemp[1];

    hspl06->c00 = ((int32_t) rxDataPres[0] << 12) | ((int32_t) rxDataPres[1] << 4) | ((int32_t) (rxDataPres[2] & 0xF0) >> 4);
    hspl06->c10 = ((int32_t) (rxDataPres[2] & 0x0F) << 16) | ((int32_t) rxDataPres[3] << 8) | (int32_t) rxDataPres[4];

    hspl06->c01 = bytes_to_int16(rxDataPres[6],rxDataPres[5]);
    hspl06->c11 = bytes_to_int16(rxDataPres[8],rxDataPres[7]);
    hspl06->c20 = bytes_to_int16(rxDataPres[10],rxDataPres[9]);
    hspl06->c21 = bytes_to_int16(rxDataPres[12],rxDataPres[11]);
    hspl06->c30 = bytes_to_int16(rxDataPres[14],rxDataPres[13]);

}

spl06_Status_t spl06_read_id(spl06_Handle_t *hspl06, uint8_t *id)
{
    HAL_I2C_Mem_Read(hspl06->hi2c, hspl06->addr, SPL06_ID, I2C_MEMADD_SIZE_8BIT, id, 1, SPL06_DEFAULT_TIMEOUT_MS);
}

/** Private functions */
inline int16_t bytes_to_int16(uint8_t byte_lo, uint8_t byte_up)
{
    //Shift upper byte to the left 8 bits and apply a bitmask.
    return (int16_t) ((int16_t)byte_up << 8) | (int16_t) byte_lo;
}