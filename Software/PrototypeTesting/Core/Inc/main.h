/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stddef.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define RAD2DEG              57.2957795f

/* Main-loop task periods (ms). Nothing in the loop blocks, so these are real periods. */
#define BNO_PRINT_PERIOD_MS  50U     /* orientation print, ~20 Hz            */
#define TOF_POLL_PERIOD_MS   20U     /* check "data ready" on the ToF sensors */
#define ENC_PRINT_PERIOD_MS  500U    /* AS5600 angle print, 2 Hz             */

/* Motor commands  */
#define MOTOR1_CMD           1000
#define MOTOR2_CMD           (-1000)
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* Peripheral handles defined in main.c, so drivers (bno085_hal.c, tof7.c, ...)
   can use them by including main.h */
extern I2C_HandleTypeDef  hi2c1;
extern I2C_HandleTypeDef  hi2c2;
extern I2C_HandleTypeDef  hi2c3;
extern TIM_HandleTypeDef  htim3;
extern UART_HandleTypeDef huart2;

/* Debug print over USART2 (blocking, 100 ms timeout) */
void uart_print(const char *s);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
