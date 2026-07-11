/*------------------------
File for running hardware tests outside of Unity/Ceedling unit testing



*/



#include "main.h"

#include <mavlink.h>
#include "servo.h"
#include "esc.h"
#include "icm42688p.h"
#include "spl06.h"
#include "printf/printf.h"
#include "fatfs.h"
#include "batterymonitor.h"
#include "stm32f405_SpeedyBee.h"
#include "sensor_mgr.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions

#define USE_FULL_ASSERT

uint8_t rxbuff[2*MAVLINK_MAX_PACKET_LEN];
extern servo_t servo_forward;
extern esc_t esc_main;


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

void test_sd_card()
{
    /**Init system and peripherals */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_SPI3_Init();

    printf_("0\r\n");

    MX_FATFS_Init();
    printf_("00\r\n");

    //HAL_Delay(1000);
    printf_("\r\n SD Card Test, pulled from kiwih \r\n\r\n");

    FATFS FatFs;
    FIL fil;
    FRESULT fres;

    fres = f_mount(&FatFs, "", 1);
    if (fres != FR_OK)
    {
        printf_("f_mount error (%i)\r\n", fres);
        while(1);
    }

    printf_("1");
    //Let's get some statistics from the SD card
    DWORD free_clusters, free_sectors, total_sectors;

    FATFS* getFreeFs;

    fres = f_getfree("", &free_clusters, &getFreeFs);
    if (fres != FR_OK) {
        printf_("f_getfree error (%i)\r\n", fres);
        while(1);
    }

    printf_("2");
    //Formula comes from ChaN's documentation
    total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
    free_sectors = free_clusters * getFreeFs->csize;

    printf_("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

    //Now let's try to open file "test.txt"
    fres = f_open(&fil, "test.txt", FA_READ);
    if (fres != FR_OK) {
        printf_("f_open error (%i)\r\n");
        while(1);
    }
    printf_("I was able to open 'test.txt' for reading!\r\n");

    //Read 30 bytes from "test.txt" on the SD card
    BYTE readBuf[30];

    //We can either use f_read OR f_gets to get data out of files
    //f_gets is a wrapper on f_read that does some string formatting for us
    TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
    if(rres != 0) {
        printf_("Read string from 'test.txt' contents: %s\r\n", readBuf);
    } else {
        printf_("f_gets error (%i)\r\n", fres);
    }

    //Be a tidy kiwi - don't forget to close your file!
    f_close(&fil);

    //Now let's try and write a file "write.txt"
    fres = f_open(&fil, "write.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
    if(fres == FR_OK) {
        printf_("I was able to open 'write.txt' for writing\r\n");
    } else {
        printf_("f_open error (%i)\r\n", fres);
    }

    //Copy in a string
    strncpy((char*)readBuf, "a new file is made!", 19);
    UINT bytesWrote;
    fres = f_write(&fil, readBuf, 19, &bytesWrote);
    fres = f_printf(&fil, "f_printf proof\r\n");
    if(fres == FR_OK) {
        printf_("Wrote %i bytes to 'write.txt'!\r\n", bytesWrote);
    } else {
        printf_("f_write error (%i)\r\n");
    }

    //Be a tidy kiwi - don't forget to close your file!
    f_close(&fil);

    //We're done, so de-mount the drive
    f_mount(NULL, "", 0);
}

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

char rx_buffer[] = " ";
void test_echo()
{
    /**Init system and peripherals */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_GPIO_Init();

    /** Setup interrupt */
    HAL_UART_Receive_IT(&huart1, rx_buffer, 1);

    /** Spit out data */
    printf_("Echo Test\r\n");
    while(1)
    {
        /** Delay for 1s between prints */
        HAL_Delay(1000);
    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    //HAL_UART_Transmit(&huart1, rx_buffer, 1, 10);
    if (huart->Instance == USART1)
    {
        printf_(rx_buffer);
        HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
    }
}

void test_adc()
{
    
}

void test_comms()
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

void test_sensor_mgr()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();
    MX_SPI1_Init();

    printf_("Running sensor_mgr test\r\n");

    error_t status = sensormgr_init();

    if (status != ERROR_OK)
    {
        printf_("Error: %d\r\n", status);
    }

    float gyro[3];
    float acc[3];
    float pres;
    float alt;

    for (int i = 0; i < 10; i++)
    {
        sensormgr_read_acc(acc);
        sensormgr_read_gyro(gyro);
        sensormgr_read_baro_pres(&pres);
        sensormgr_read_baro_alt(&alt);

        printf_("Acc: %f, %f, %f\r\n", acc[0], acc[1], acc[2]);
        printf_("Gyro: %f, %f, %f\r\n", gyro[0], gyro[1], gyro[2]);
        printf_("Pres: %f, Alt: %f\r\n", pres, alt);
        HAL_Delay(1000);
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
        //servo_test(&servo_forward);
    }
}

void test_esc()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM8_Init();
    MX_USART1_UART_Init();

    int16_t res = 0;

    printf_("Running ESC test\r\n");
    printf_("CAUTION - MOTOR WILL SPIN IF CONNECTED\r\n");
    printf_("SPINNING IN:\r\n");

    int ticks = 5;
    for (int counter = ticks; counter >= 0; counter--)
    {
        HAL_Delay(1000);
        printf_("%d...\r\n", counter);
    }

    printf_("SPINNING");

    esc_init(&esc_main);
    esc_enable(&esc_main);
    HAL_Delay(5000);
    esc_set_throttle(&esc_main, 0.25);
    //esc_set_microseconds(&esc_main, 1000);
    esc_update(&esc_main);
    HAL_Delay(1000);
    //esc_disable(&esc_main);
    //HAL_Delay(250);
    //esc_enable(&esc_main);
    res = esc_set_throttle(&esc_main, 0.5);
    printf_("result: %d", res);
    esc_update(&esc_main);
    HAL_Delay(1000);
    res = esc_set_throttle(&esc_main, 0.75);
    printf_("result: %d", res);
    esc_update(&esc_main);
    HAL_Delay(1000);
    res = esc_set_throttle(&esc_main, 1.0);
    printf_("result: %d", res);
    esc_update(&esc_main);
    HAL_Delay(1000);
    esc_disable(&esc_main);
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

void test_battery_monitor()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();

    battery_monitor_enable();
    while(1)
    {
        uint16_t battery_voltage_raw = battery_monitor_get_voltage_raw();
        uint16_t battery_current_raw = battery_monitor_get_current_raw();
        float battery_voltage_sc1 = battery_voltage_raw * 11.05 * 0.000805;
        float battery_voltage_sc = battery_monitor_get_voltage();
        float battery_current_sc = battery_monitor_get_current();

        printf_("Battery Voltage Raw: %d\r\n", battery_voltage_raw);
        printf_("Battery Current Raw: %d\r\n", battery_current_raw);

        printf_("Scaled Battery Voltage: %f\r\n", battery_voltage_sc);
        printf_("Scaled Battery Current: %f\r\n", battery_current_sc);
        HAL_Delay(1000);
    }

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
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
