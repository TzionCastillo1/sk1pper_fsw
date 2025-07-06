/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"
#include "status.h"
#include "leddriver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticEventGroup_t osStaticEventGroupDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern osEventFlagsId_t ErrorHandle;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for logTask */
osThreadId_t logTaskHandle;
uint32_t logTaskBuffer[ 256 ];
osStaticThreadDef_t logTaskControlBlock;
const osThreadAttr_t logTask_attributes = {
  .name = "logTask",
  .cb_mem = &logTaskControlBlock,
  .cb_size = sizeof(logTaskControlBlock),
  .stack_mem = &logTaskBuffer[0],
  .stack_size = sizeof(logTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for status_timer */
osTimerId_t status_timerHandle;
osStaticTimerDef_t StatusTimerControlBlock;
const osTimerAttr_t status_timer_attributes = {
  .name = "status_timer",
  .cb_mem = &StatusTimerControlBlock,
  .cb_size = sizeof(StatusTimerControlBlock),
};
/* Definitions for Error */
osEventFlagsId_t ErrorHandle;
osStaticEventGroupDef_t ErrorControlBlock;
const osEventFlagsAttr_t Error_attributes = {
  .name = "Error",
  .cb_mem = &ErrorControlBlock,
  .cb_size = sizeof(ErrorControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void startLogTask(void *argument);
extern void status_timer_callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of status_timer */
  status_timerHandle = osTimerNew(status_timer_callback, osTimerPeriodic, NULL, &status_timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of logTask */
  logTaskHandle = osThreadNew(startLogTask, NULL, &logTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of Error */
  ErrorHandle = osEventFlagsNew(&Error_attributes);

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
  status_set_error();
  /* Infinite loop */
  for(;;)
  {
    osDelay(4000);
    status_set_armed();
    //osEventFlagsSet(ErrorHandle, EVENT_FLAG_DEBUG);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_14);

  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

