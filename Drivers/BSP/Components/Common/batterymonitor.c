#include "batterymonitor.h"
#include "stm32f4xx_hal.h" 


extern ADC_HandleTypeDef hadc1;

static uint16_t adc_dma_buffer[ADC_NUM_CHANNELS];

error_t battery_monitor_init()
{
    //battery_voltage = -1;
}

error_t battery_monitor_enable()
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_NUM_CHANNELS);
}

error_t battery_monitor_disable()
{
    HAL_ADC_Stop_DMA(&hadc1);
}

uint16_t battery_monitor_get_voltage_raw()
{
    return adc_dma_buffer[DMA_VOLTAGE_BUFFER_IDX];
}

uint16_t battery_monitor_get_current_raw()
{
    return adc_dma_buffer[DMA_CURRENT_BUFFER_IDX];
}

float battery_monitor_get_voltage()
{
    uint16_t raw_voltage = battery_monitor_get_voltage_raw();
    return battery_monitor_cnvrt_voltage(raw_voltage);
}

float battery_monitor_get_current()
{
    uint16_t raw_current = battery_monitor_get_current_raw();
    return battery_monitor_cnvrt_current(raw_current);

}

uint8_t battery_monitor_get_soc()
{

}

float battery_monitor_cnvrt_voltage(uint16_t raw_voltage)
{
    return (BATT_MON_V_SCALE * raw_voltage * ADC_VOLTS_PER_LSB);
}

float battery_monitor_cnvrt_current(uint16_t raw_current)
{
    return BATT_MON_I_SCALE * raw_current * ADC_VOLTS_PER_LSB;
}