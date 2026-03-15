/*------------------------
File for running hardware tests outside of Unity/Ceedling unit testing



*/



#include "main.h"
#include <mavlink.h>
#include "Servo.h"
#include "printf/printf.h"

ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
//UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_uart5_rx;
DMA_HandleTypeDef hdma_uart5_tx;

uint8_t rxbuff[2*MAVLINK_MAX_PACKET_LEN];

void test_debug_uart()
{
    /**Init system and peripherals */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_GPIO_Init();

    /** Spit out data */
    while(1)
    {
        /** Delay for 1s between prints */
        HAL_Delay(1000);
        printf_("Hello world!\n");
    }
}

void test_adc()
{
    
}

void test_comms()
{

}

void test_sdcard()
{

}

void test_baro()
{

}

void test_imu()
{

}

void test_servo()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    while(1)
    {
        HAL_Delay(100);
        servo_test_all();
    }
}

void test_led()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    BSP_LED_Init(LED2);
    while(1)
    {
        BSP_LED_Toggle(LED2);
        HAL_Delay(500);
    }
}

int main()
{
    TEST();
}