/*------------------------
File for running hardware tests outside of Unity/Ceedling unit testing



*/



#include "main.h"
#include <mavlink.h>
#include "Servo.h"
#include "icm42688p.h"
#include "spl06.h"
#include "printf/printf.h"

#define USE_FULL_ASSERT

ADC_HandleTypeDef hadc1;


//SPI_HandleTypeDef hspi1;

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
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();

    spl06_Handle_t hspl06 = 
    {
        .hi2c = &hi2c1,
        .addr = BARO_I2C_ADDRESS << 1
    };
    
    printf_("Running Baro Test!\n");

    spl06_init(&hspl06);

    uint8_t id;
    spl06_read_id(&hspl06, &id);
    printf_("ID: %x\n", id);

    printf_("Calibration Parameters: c0: %d,c1: %d,c00: %d,c10: %d,C01: %d,C11: %d,C20: %d,C21: %d,C30: %d", hspl06.c0, hspl06.c1, hspl06.c00, hspl06.c10,
                    hspl06.c01, hspl06.c11, hspl06.c20, hspl06.c21, hspl06.c30);

    spl06_start(&hspl06);

    printf_("Sensor readings:\n");
    for (int i = 0; i < 5; i++)
    {
        int32_t raw_pres;
        int32_t raw_temp;
        float sc_pres;
        float sc_temp;
        float comp_pres;
        float comp_temp;

        spl06_read_raw_temp(&hspl06, &raw_temp);
        spl06_read_raw_pres(&hspl06, &raw_pres);
        spl06_read_scaled_pres(&hspl06, &sc_pres);
        spl06_read_scaled_temp(&hspl06, &sc_temp);
        spl06_read_comp_pres(&hspl06, &comp_pres);
        spl06_read_comp_temp(&hspl06, &comp_temp);
        printf_("raw pres: %ld, raw_temp: %ld \n", raw_pres, raw_temp);
        printf_("scaled pres: %f, scaled_temp: %f \n", sc_pres, sc_temp);
        printf_("comp pres: %f, comp_temp: %f \n", comp_pres, comp_temp);
        HAL_Delay(100);
    }

}

void test_assert()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_GPIO_Init();

    HAL_Delay(500);

    printf_("Running Assert Test");

    assert_param(1 == 0);
}

void test_imu()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    MX_USART1_UART_Init();
    printf_("Running imu test\n");
    icm42688p_Handle_t hicm42688p =
    {
        .CS_PIN = GPIO_PIN_4,
        .CS_PORT = GPIOA,
        .hspi = &hspi1, 
        .accel_range = ICM42688P_ACC_RANGE_2,
        .accel_rate = ICM42688P_ACC_2KHZ,
        .gyro_range = ICM42688P_GY_RANGE_1000,
        .gyro_rate = ICM42688P_GY_2KHZ
    };
    icm42688p_init(&hicm42688p);

    uint8_t id = 0;
    icm42688p_read_who_am_i(&hicm42688p, &id);

    printf_("Who am I: %x\n", id);

    printf_("Starting ICM42688P\n");
    icm42688P_Status_t status = icm42688p_start(&hicm42688p);
    printf_("result: %d\n", status);

    HAL_Delay(45);

    int16_t raw_gyro[3];
    

    for(int i = 0;  i < 3; i++)
    {
        icm42688p_read_raw_gyro(&hicm42688p, raw_gyro);
        printf_("raw gyro: %d, %d, %d\n", raw_gyro[0], raw_gyro[1], raw_gyro[2]);
        HAL_Delay(2000);
    }

    float scaled_gyro[3];

    for(int i = 0;  i < 3; i++)
    {
        icm42688p_read_scaled_gyro(&hicm42688p, scaled_gyro);
        printf_("scaled gyro: %f, %f, %f\n", scaled_gyro[0], scaled_gyro[1], scaled_gyro[2]);
        HAL_Delay(2000);
    }

    int16_t raw_acc[3];
    

    for(int i = 0;  i < 3; i++)
    {
        icm42688p_read_raw_acc(&hicm42688p, raw_acc);
        printf_("raw acc: %d, %d, %d\n", raw_acc[0], raw_acc[1], raw_acc[2]);
        HAL_Delay(2000);
    }

    float scaled_acc[3];

    for(int i = 0;  i < 3; i++)
    {
        icm42688p_read_scaled_acc(&hicm42688p, scaled_acc);
        printf_("scaled acc: %f, %f, %f\n", scaled_acc[0], scaled_acc[1], scaled_acc[2]);
        HAL_Delay(2000);
    }

    int16_t raw_temp;
    icm42688p_read_raw_temp(&hicm42688p, &raw_temp);

    float scaled_temp;
    icm42688p_read_scaled_temp(&hicm42688p, &scaled_temp);

    printf_("Raw Temp: %d, Scaled Temp: %f\n", raw_temp, scaled_temp);

    printf_("read_sensors function:\n");

    imu_data_t imu_data;

    icm42688p_read_sensors(&hicm42688p, &imu_data);

    printf_("scaled gyro: %f, %f, %f\n", imu_data.gyro[0], imu_data.gyro[1], imu_data.gyro[2]);
    printf_("scaled acc: %f, %f, %f\n", imu_data.accel[0], imu_data.accel[1], imu_data.accel[2]);
    printf_("Scaled Temp: %f\n", imu_data.temp);

    printf_("Stopping ICM42688P\n");
    status = icm42688p_stop(&hicm42688p);
    printf_("result: %d\n", status);
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

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    printf_("Wrong parameters value: file %s on line %ld\r\n", file, line);
  /* USER CODE END 6 */
}

int main()
{
    TEST();
}