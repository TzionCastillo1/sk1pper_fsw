#include "icm42688p.h"
#include "stm32_assert.h"

static inline uint8_t read_reg(uint8_t reg_addr);

static inline uint8_t write_reg(uint8_t reg_addr);

static inline int16_t bytes_to_int16(uint8_t byte_lo, uint8_t byte_up);

static icm42688P_Status_t icm42688p_read_reg(icm42688p_Handle_t *hicm42688p, uint8_t reg, uint8_t *rxData, uint16_t size, uint16_t timeout);

static icm42688P_Status_t icm42688p_write_reg(icm42688p_Handle_t *hicm42688p, uint8_t reg, uint8_t *rxData, uint16_t size, uint16_t timeout);


icm42688P_Status_t icm42688p_init(icm42688p_Handle_t *hicm42688p)
{
    /** 
    * TODO:
    * config filter 
    */

    /** Select Accelerometer scaling factor */
    switch(hicm42688p->accel_range)
    {
        case(ICM42688P_ACC_RANGE_16):
            hicm42688p->accel_scaling_factor = ICM42688P_ACC_SSF_16;
            break;

        case(ICM42688P_ACC_RANGE_8):
            hicm42688p->accel_scaling_factor = ICM42688P_ACC_SSF_8;
            break;

        case(ICM42688P_ACC_RANGE_4):
            hicm42688p->accel_scaling_factor = ICM42688P_ACC_SSF_4;
            break;

        case(ICM42688P_ACC_RANGE_2):
            hicm42688p->accel_scaling_factor = ICM42688P_ACC_SSF_2;
            break;
    }

    /** Select Gyro scaling factor */
    switch(hicm42688p->gyro_range)
    {
        case(ICM42688P_GY_RANGE_2000):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_2000;
            break;

        case(ICM42688P_GY_RANGE_1000):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_1000;
            break;

        case(ICM42688P_GY_RANGE_500):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_500;
            break;

        case(ICM42688P_GY_RANGE_250):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_250;
            break;

        case(ICM42688P_GY_RANGE_125):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_125;
            break;

        case(ICM42688P_GY_RANGE_62_5):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_62_5;
            break;

        case(ICM42688P_GY_RANGE_31_25):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_31_25;
            break;

        case(ICM42688P_GY_RANGE_15_625):
            hicm42688p->gyro_scaling_factor= ICM42688P_GYRO_SSF_15_625;
            break;

    }
    uint8_t id;
    uint8_t txData[8];
    uint8_t rxData[8];
    
    // Set default CS state (HIGH)
    HAL_GPIO_WritePin(hicm42688p->CS_PORT,hicm42688p->CS_PIN, GPIO_PIN_SET);

    // Reset IMU
    icm42688p_reset(hicm42688p);

    //Delay for 1ms before reading any registers
    HAL_Delay(1);

    // Assert IMU ID is as expected
    icm42688p_read_who_am_i(hicm42688p, &id);
    assert_param(id == ICM42688P_WHO_AM_I_ID);

    // Select Register Bank 0
    icm42688p_read_reg(hicm42688p, ICM42688P_REG_BANK_SEL, rxData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    // Mask reserved bits
    txData[0] = rxData[0] & 0b11111000;
    icm42688p_write_reg(hicm42688p, ICM42688P_REG_BANK_SEL, txData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);

    //Configure accelerometer
    txData[0] = (hicm42688p->accel_range << 5) | hicm42688p->accel_rate;
    icm42688p_write_reg(hicm42688p, ICM42688P_ACCEL_CONFIG0, txData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);

    //Configure gyroscope
    txData[0] = (hicm42688p->gyro_range << 5) | hicm42688p->gyro_rate;
    icm42688p_write_reg(hicm42688p, ICM42688P_GYRO_CONFIG0, txData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    
    //Configure LPFs
}

icm42688P_Status_t icm42688p_start(icm42688p_Handle_t *hicm42688p)
{

    icm42688P_Status_t status = ICM42688P_OK;

    //Configure Power Management Register
    uint8_t txData;
    uint8_t rxData;
    txData = ICM42688P_TEMP_ON_VAL | ICM42688P_ACCEL_ON_LN_VAL | ICM42688P_GYRO_ON_LN_VAL;
    icm42688p_write_reg(hicm42688p, ICM42688P_PWR_MGMT0, &txData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);

    //Part requires 200us delay before accessing registers after reset
    HAL_Delay(1);

    icm42688p_read_reg(hicm42688p, ICM42688P_PWR_MGMT0, &rxData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);

    //Mask for only the bits for acc, gyro power
    if( (rxData & 0x0F) != (txData & 0x0F))
    {
        status = ICM42688P_ERR;
    }
    
    return status;
}

icm42688P_Status_t icm42688p_stop(icm42688p_Handle_t *hicm42688p)
{

    icm42688P_Status_t status = ICM42688P_OK;

    //Configure Power Management Register
    uint8_t txData;
    uint8_t rxData;
    txData = ICM42688P_ACCEL_OFF_LN_VAL | ICM42688P_GYRO_OFF_LN_VAL;
    icm42688p_write_reg(hicm42688p, ICM42688P_PWR_MGMT0, &txData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);

    icm42688p_read_reg(hicm42688p, ICM42688P_PWR_MGMT0, &rxData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);

    //Mask for only the bits for acc, gyro power
    if( (rxData & 0x0F) != (txData & 0x0F))
    {
        icm42688P_Status_t status = ICM42688P_OK;
    }
    
    return status;

}

icm42688P_Status_t icm42688p_reset(icm42688p_Handle_t *hicm42688p)
{
    /**
     * TODO:
     * Read DEVICE_CONFIG Register
     * set LSB to 0
     */
    uint8_t device_config_data;
    icm42688p_read_reg(hicm42688p, ICM42688P_DEVICE_CONFIG, &device_config_data, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    //Apply bitmask to set LSB to 0 
    device_config_data = device_config_data | 0b00000001;
    icm42688p_write_reg(hicm42688p, ICM42688P_DEVICE_CONFIG, &device_config_data, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
}

icm42688P_Status_t icm42688p_read_raw_gyro(icm42688p_Handle_t *hicm42688p, int16_t gyro_vals[3])
{
    uint8_t rxData[6];
    icm42688p_read_reg(hicm42688p, ICM42688P_UPPER_X_GYRO_DATA, rxData, 6, ICM42688P_DEFAULT_TIMEOUT_MS);

    gyro_vals[0] = bytes_to_int16(rxData[1], rxData[0]);
    gyro_vals[1] = bytes_to_int16(rxData[3], rxData[2]);
    gyro_vals[2] = bytes_to_int16(rxData[5], rxData[4]);
}

icm42688P_Status_t icm42688p_read_raw_acc(icm42688p_Handle_t *hicm42688p, int16_t acc_vals[3])
{
    uint8_t rxData[6];
    icm42688p_read_reg(hicm42688p, ICM42688P_UPPER_X_ACCEL_DATA, rxData, 6, ICM42688P_DEFAULT_TIMEOUT_MS);

    acc_vals[0] = bytes_to_int16(rxData[1], rxData[0]);
    acc_vals[1] = bytes_to_int16(rxData[3], rxData[2]);
    acc_vals[2] = bytes_to_int16(rxData[5], rxData[4]);

}

icm42688P_Status_t icm42688p_read_raw_temp(icm42688p_Handle_t *hicm42688p, int16_t *temp)
{
    uint8_t rxData[2];
    icm42688p_read_reg(hicm42688p, ICM42688P_UPPER_TEMP_DATA, rxData, 2, ICM42688P_DEFAULT_TIMEOUT_MS);

    *temp = bytes_to_int16(rxData[1], rxData[0]);

}

icm42688P_Status_t icm42688p_read_scaled_gyro(icm42688p_Handle_t *hicm42688p, float gyro_vals[3])
{
    int16_t temp_gyro[3];
    icm42688p_read_raw_gyro(hicm42688p, temp_gyro);

    for(int i = 0; i < 3; i++)
    {
        // scaling factor should be dps/bit
        gyro_vals[i] = (float) temp_gyro[i] * hicm42688p->gyro_scaling_factor;
    }

}

icm42688P_Status_t icm42688p_read_scaled_acc(icm42688p_Handle_t *hicm42688p, float acc_vals[3])
{
    int16_t temp_acc[3];
    icm42688p_read_raw_acc(hicm42688p, temp_acc);

    for(int i = 0; i < 3; i++)
    {
        // scaling factor should be g's/bit
        acc_vals[i] = (float) temp_acc[i] * hicm42688p->accel_scaling_factor;
    }

}

icm42688P_Status_t icm42688p_read_scaled_temp(icm42688p_Handle_t *hicm42688p, float *temp)
{
    int16_t temp_temp;
    icm42688p_read_raw_temp(hicm42688p, &temp_temp);

    *temp = ((float) temp_temp * ICM42688P_TEMP_SSF) + ICM42688P_TEMP_OFFSET;
}

icm42688P_Status_t icm42688p_read_sensors(icm42688p_Handle_t *hicm42688p, imu_data_t *imu_data)
{
    icm42688p_read_scaled_acc(hicm42688p, imu_data->accel);
    icm42688p_read_scaled_gyro(hicm42688p, imu_data->gyro);
    icm42688p_read_scaled_temp(hicm42688p, &(imu_data->temp));
}

icm42688P_Status_t icm42688p_read_who_am_i(icm42688p_Handle_t *hicm42688p, uint8_t *id)
{
    /**
    HAL_GPIO_WritePin(hicm42688p->CS_PORT,hicm42688p->CS_PIN, GPIO_PIN_RESET);
    uint8_t txData = read_reg(ICM42688P_WHO_AM_I);
    HAL_SPI_Transmit(hicm42688p->hspi, &txData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    HAL_SPI_Receive(hicm42688p->hspi, &rxData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    HAL_GPIO_WritePin(hicm42688p->CS_PORT,hicm42688p->CS_PIN, GPIO_PIN_SET);
    */
    uint8_t rxData = 0;
    icm42688p_read_reg(hicm42688p, ICM42688P_WHO_AM_I, &rxData, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    *id = rxData;
}

icm42688P_Status_t icm42688p_read_reg(icm42688p_Handle_t *hicm42688p, uint8_t reg, uint8_t *rxData, uint16_t size, uint16_t timeout)
{
    uint8_t txReg = read_reg(reg);
    HAL_GPIO_WritePin(hicm42688p->CS_PORT, hicm42688p->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hicm42688p->hspi, &txReg, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    HAL_SPI_Receive(hicm42688p->hspi, rxData, size, timeout);
    HAL_GPIO_WritePin(hicm42688p->CS_PORT, hicm42688p->CS_PIN, GPIO_PIN_SET);
}

icm42688P_Status_t icm42688p_write_reg(icm42688p_Handle_t *hicm42688p, uint8_t reg, uint8_t *txData, uint16_t size, uint16_t timeout)
{
    uint8_t txReg = write_reg(reg);
    HAL_GPIO_WritePin(hicm42688p->CS_PORT,hicm42688p->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hicm42688p->hspi, &txReg, 1, ICM42688P_DEFAULT_TIMEOUT_MS);
    HAL_SPI_Transmit(hicm42688p->hspi, txData, size, timeout);
    HAL_GPIO_WritePin(hicm42688p->CS_PORT,hicm42688p->CS_PIN, GPIO_PIN_SET);
}

/**
 * @brief Set the MSB to the read bit (1)
 * 
 * @param reg_addr 
 * @return uint8_t 
 */
inline uint8_t read_reg(uint8_t reg_addr)
{
    return (reg_addr | (1 << 7));
}

/**
 * @brief Set the MSB to the read bit (0)
 * 
 * @param reg_addr 
 * @return uint8_t 
 */
inline uint8_t write_reg(uint8_t reg_addr)
{
    return (reg_addr & 0b01111111);
}

inline int16_t bytes_to_int16(uint8_t byte_lo, uint8_t byte_up)
{
    //Shift upper byte to the left 8 bits and apply a bitmask.
    return (int16_t) ((int16_t)byte_up << 8) | (int16_t) byte_lo;
}