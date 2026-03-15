#ifndef HW_CONFIG_H
#define HW_CONFIG_H

/* ============== IMU Config ============== */
// IMU - ICM24688P on SPI1
// Rotation: ROLL_180 and YAW_270 Relative to flight axes
// INT1 pin routing unconfirmed - schematic not available.

#define IMU_SPI_Handle  hspi1
#define IMU_CS_PORT     GPIOA
#define IMU_CS_PIN      GPIO_PIN_4
#define IMU_CLOCK_HZ    8000000UL

/* ============== LED Config ============= */
// LED2 - Green LED on A13
#define LED2_GPIO_PORT  GPIOA
#define LED2_PIN GPIO_PIN_13
#define LED2_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()

/* ============== Baro Config ============= */


/* ============== SD Card Config ===========*/

/* ============= Battery Monitor Config ==== */

/* ============= Telemetry Config ========== */

/* ============= Debug Port Config ========= */


#endif /* HW_CONFIG_H */