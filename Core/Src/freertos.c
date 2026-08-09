/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cli.h"
#include "param_mgr.h"
#include "sensor_mgr.h"
#include <mavlink.h>
#include "printf/printf.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define CLI_CMD_LINE_BUFF 256
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for cli */
osThreadId_t cliHandle;
uint32_t cliBuffer[ 1024 ];
osStaticThreadDef_t cliControlBlock;
const osThreadAttr_t cli_attributes = {
  .name = "cli",
  .cb_mem = &cliControlBlock,
  .cb_size = sizeof(cliControlBlock),
  .stack_mem = &cliBuffer[0],
  .stack_size = sizeof(cliBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal1,
};
/* Definitions for housekeeper */
osThreadId_t housekeeperHandle;
uint32_t housekeeperBuffer[ 1024 ];
osStaticThreadDef_t housekeeperControlBlock;
const osThreadAttr_t housekeeper_attributes = {
  .name = "housekeeper",
  .cb_mem = &housekeeperControlBlock,
  .cb_size = sizeof(housekeeperControlBlock),
  .stack_mem = &housekeeperBuffer[0],
  .stack_size = sizeof(housekeeperBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal2,
};
/* Definitions for flight_mgr */
osThreadId_t flight_mgrHandle;
uint32_t flight_mgrBuffer[ 1024 ];
osStaticThreadDef_t flight_mgrControlBlock;
const osThreadAttr_t flight_mgr_attributes = {
  .name = "flight_mgr",
  .cb_mem = &flight_mgrControlBlock,
  .cb_size = sizeof(flight_mgrControlBlock),
  .stack_mem = &flight_mgrBuffer[0],
  .stack_size = sizeof(flight_mgrBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for link_mgr */
osThreadId_t link_mgrHandle;
uint32_t link_mgrBuffer[ 1024 ];
osStaticThreadDef_t link_mgrControlBlock;
const osThreadAttr_t link_mgr_attributes = {
  .name = "link_mgr",
  .cb_mem = &link_mgrControlBlock,
  .cb_size = sizeof(link_mgrControlBlock),
  .stack_mem = &link_mgrBuffer[0],
  .stack_size = sizeof(link_mgrBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for test_mutex */
osMutexId_t test_mutexHandle;
osStaticMutexDef_t test_mutexControlBlock;
const osMutexAttr_t test_mutex_attributes = {
  .name = "test_mutex",
  .cb_mem = &test_mutexControlBlock,
  .cb_size = sizeof(test_mutexControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void start_cli(void *argument);
void start_hk(void *argument);
void start_fm(void *argument);
void start_lm(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of test_mutex */
  test_mutexHandle = osMutexNew(&test_mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of cli */
  cliHandle = osThreadNew(start_cli, NULL, &cli_attributes);

  /* creation of housekeeper */
  housekeeperHandle = osThreadNew(start_hk, NULL, &housekeeper_attributes);

  /* creation of flight_mgr */
  flight_mgrHandle = osThreadNew(start_fm, NULL, &flight_mgr_attributes);

  /* creation of link_mgr */
  link_mgrHandle = osThreadNew(start_lm, NULL, &link_mgr_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_start_cli */
/**
* @brief Function implementing the cli thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_cli */
void start_cli(void *argument)
{
  /* USER CODE BEGIN start_cli */
  //Start CLI UART
  HAL_UART_Receive_IT(&huart1, uart1_buff, 1);
  cli_init();

  char cmd_line[CLI_CMD_LINE_BUFF];
  char *argv[CLI_MAX_LINE_LEN];
  /* Infinite loop */
  for(;;)
  {
    int cli_ret = cli_ringbuff_to_str(cmd_line);
    if(cli_ret)
    {
      int argc = cli_tokenizer(cmd_line, argv);
      cli_invoker(argc, argv);
    }
    osDelay(100);
  }
  /* USER CODE END start_cli */
}

/* USER CODE BEGIN Header_start_hk */
/**
* @brief Function implementing the housekeeper thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_hk */
void start_hk(void *argument)
{
  /* USER CODE BEGIN start_hk */
  param_mgr_init();
  osDelay(10);
  param_mgr_load();

  /* Infinite loop */;
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END start_hk */
}

/* USER CODE BEGIN Header_start_fm */
/**
* @brief Function implementing the flight_mgr thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_fm */
void start_fm(void *argument)
{
  /* USER CODE BEGIN start_fm */
  //Base rate of 200Hz
  uint32_t base_period_ticks = 5;
  uint32_t base_tick;

  error_t status = sensormgr_init();

  if (status != ERROR_OK)
  {
      printf_("Error: %d\r\n", status);
  }

  float gyro[3];

  /* Infinite loop */
  for(;;)
  {
    base_tick = osKernelGetTickCount();
    sensormgr_update_gyro();
    sensormgr_update_acc();
    sensormgr_update_baro();
    osDelayUntil(base_tick + base_period_ticks);
  }
  /* USER CODE END start_fm */
}

/* USER CODE BEGIN Header_start_lm */
/**
* @brief Function implementing the link_mgr thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_lm */
void start_lm(void *argument)
{
  /* USER CODE BEGIN start_lm */
  //Base rate of 10Hz
  const uint32_t base_period_ticks = 100;
  const uint32_t period_ticks_5Hz = 200;
  const uint32_t period_ticks_1Hz = 1000;
  uint32_t slow_tick = osKernelGetTickCount();
  uint32_t base_tick;
  const float Gs_to_mGs = 1000;
  const float dps_to_mrads = 1000*3.1415/180.0;

  //Need some way to wait until the sensors are initialized
  float alt_at_boot;
  sensormgr_get_baro_alt(&alt_at_boot);


  /* Infinite loop */
  for(;;)
  {
    base_tick = osKernelGetTickCount();

    /******** Insert Base-frequency code ***************/
    BSP_LED_Toggle(LED_GREEN);   

    /******** Insert 5Hz code ***************/
    if((base_tick - slow_tick) % period_ticks_5Hz == 0)
    {
      /************** Scaled IMU Message ********************/
      uint8_t txbuff[MAVLINK_MAX_PACKET_LEN];
      uint8_t system_id = 42;
      uint8_t base_mode = 0;
      uint8_t custom_mode = 0;
      mavlink_message_t message;
      sensor_data_t data;
      sensormgr_get_all(&data);
      float gyro[3];
      float acc[3];
      sensormgr_get_acc(acc);
      sensormgr_get_gyro(gyro);
      mavlink_msg_scaled_imu_pack_chan(
        system_id,
        MAV_COMP_ID_PERIPHERAL,
        MAVLINK_COMM_0,
        &message,
        0,//TODO: Create system time,
        (int16_t)(data.acc[0] * Gs_to_mGs),
        (int16_t)(data.acc[1] * Gs_to_mGs),
        (int16_t)(data.acc[2] * Gs_to_mGs),
        (int16_t)(data.gyro[0] * dps_to_mrads),
        (int16_t)(data.gyro[1] * dps_to_mrads),
        (int16_t)(data.gyro[2] * dps_to_mrads),
        0,
        0,
        0,
        69.69420//TODO: IMU temperature
      );

      int len = mavlink_msg_to_send_buffer(txbuff, &message);
      //synchronous tx should prevent us from overwritting buffer mid transmission
      int status = HAL_UART_Transmit(&huart4, txbuff, len, 100);

      /************** Altitude Message ********************/
      float alt;
      sensormgr_get_baro_alt(&alt);
      mavlink_msg_altitude_pack_chan(
        system_id,
        MAV_COMP_ID_PERIPHERAL,
        MAVLINK_COMM_0,
        &message,
        0,//TODO: Create system time,
        alt_at_boot,
        0,
        alt,
        -9999, /** TODO: Make an 'unknown' constant */
        -9999,
        -9999
      );      
      len = mavlink_msg_to_send_buffer(txbuff, &message);
      //synchronous tx should prevent us from overwritting buffer mid transmission
      status = HAL_UART_Transmit(&huart4, txbuff, len, 100);
    }
    
    /******** Insert 1Hz code ***************/
    if((base_tick - slow_tick) % period_ticks_1Hz == 0)
    {
      //Write heartbeat message
      uint8_t txbuff[MAVLINK_MAX_PACKET_LEN];
      uint8_t system_id = 42;
      uint8_t base_mode = 0;
      uint8_t custom_mode = 0;
      mavlink_message_t message;
      mavlink_msg_heartbeat_pack_chan(
        system_id,
        MAV_COMP_ID_PERIPHERAL,
        MAVLINK_COMM_0,
        &message,
        MAV_TYPE_GENERIC,
        MAV_AUTOPILOT_GENERIC,
        base_mode,
        custom_mode,
        MAV_STATE_STANDBY
      );
      const int len = mavlink_msg_to_send_buffer(txbuff, &message);
      int status = HAL_UART_Transmit(&huart4, txbuff, len, 100);

      BSP_LED_Toggle(LED_BLUE);
    }

    osDelayUntil(base_tick + base_period_ticks); 
  }
  /* USER CODE END start_lm */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

