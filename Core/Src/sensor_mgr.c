#include "sensor_mgr.h"
#include "math.h"
#include "stm32f405_SpeedyBee.h"
#include "spl06.h"
#include "icm42688p.h"
#include "printf/printf.h"

#define ALT_COEFF       44330U
#define ALT_EXP         (1.0/5.255f)
#define PRES_SEA_LEVEL  1013.25f

static spl06_Handle_t hspl06;
static icm42688p_Handle_t hicm42688p;

static float _press_pa_to_alt(float pres);

error_t sensormgr_init(void) 
{
    error_t status = ERROR_OK;

    /*---------------Barometer Initialization--------------*/
    printf_("Initializing Barometer\r\n");


    hspl06.hi2c = &hi2c1;
    hspl06.addr = BARO_I2C_ADDRESS << 1;

    spl06_init(&hspl06);
    printf_("1\r\n");

    uint8_t id;
    spl06_read_id(&hspl06, &id);
    printf_("2\r\n");

    if (id != SPL06_EXPECTED_ID_VAL)
    {
        printf_("FAIL\r\n");
        return ERROR_SENSOR_INIT_FAIL;
    }


    spl06_start(&hspl06);

    printf_("Barometer Initialized!\r\n");

    /*------------------IMU Initialization----------------*/
    printf_("Initializing IMU\r\n");

    hicm42688p.CS_PIN = GPIO_PIN_4;
    hicm42688p.CS_PORT = GPIOA;
    hicm42688p.hspi = &hspi1;
    hicm42688p.accel_range = ICM42688P_ACC_RANGE_2;
    hicm42688p.accel_rate = ICM42688P_ACC_2KHZ;
    hicm42688p.gyro_range = ICM42688P_GY_RANGE_1000;
    hicm42688p.gyro_rate = ICM42688P_GY_2KHZ;
    icm42688p_init(&hicm42688p);

    icm42688p_read_who_am_i(&hicm42688p, &id);

    if (id != ICM42688P_WHO_AM_I_ID)
    {
        return ERROR_SENSOR_INIT_FAIL;
    }

    icm42688p_start(&hicm42688p);

    printf_("IMU Initialized!\r\n");

    return status;
}

error_t sensormgr_cal_gryo(void)
{
    /**
     * TODO: 
     * 
     */
}

error_t sensormgr_cal_acc(void)
{

}

error_t sensormgr_cal_baro(void)
{

}

error_t sensormgr_read_acc(float acc_val[3])
{
    icm42688p_read_scaled_acc(&hicm42688p, acc_val);
    return ERROR_OK;
}

error_t sensormgr_read_gyro(float gyro_val[3])
{
    icm42688p_read_scaled_gyro(&hicm42688p, gyro_val);
    return ERROR_OK;
}

error_t sensormgr_read_baro_pres(float *baro_alt)
{
    spl06_read_comp_pres(&hspl06, baro_alt);
    return ERROR_OK;
}

error_t sensormgr_read_baro_alt(float *baro_alt)
{
    spl06_read_comp_pres(&hspl06, baro_alt);
    //Convert into hPa from Pa
    *baro_alt = _press_pa_to_alt(*baro_alt);
    return ERROR_OK;
}

static float _press_pa_to_alt(float pres)
{
    //Convert from Pa to hPa for conversion 
    return ALT_COEFF * (1.0f - pow((pres/100.0f)/PRES_SEA_LEVEL, ALT_EXP));
}