#include "batterymonitor.h"
#include "stm32f405_SpeedyBee.h"


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

int16_t battery_monitor_get_voltage_raw()
{
    return adc_dma_buffer[DMA_VOLTAGE_BUFFER_IDX];
}

int16_t battery_monitor_get_current_raw()
{
    return adc_dma_buffer[DMA_CURRENT_BUFFER_IDX];
}

float battery_monitor_get_voltage()
{

}

float battery_monitor_get_current()
{

}

uint8_t battery_monitor_get_soc()
{

}

float battery_monitor_cnvrt_voltage()
{

}

float battery_monitor_cnvrt_current()
{
    
}