#include "unity.h"

//File Under test
#include "batterymonitor.h"

//Mocks
//#include "mock_stm32f4xx_hal.h"
//#include "mock_stm32f4xx_hal_adc.h"

void setUp()
{

}

void tearDown()
{

}

void test_adc_raw_conversion(void)
{
    uint16_t raw_value = 1672;
    float sc_value = battery_monitor_cnvrt_voltage(raw_value);

    TEST_ASSERT_FLOAT_WITHIN(0.1, 14.87, sc_value);

}
