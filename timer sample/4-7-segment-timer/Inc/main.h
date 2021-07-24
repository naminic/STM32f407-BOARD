/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define E_7SEG_Pin GPIO_PIN_7
#define E_7SEG_GPIO_Port GPIOE
#define F_7SEG_Pin GPIO_PIN_8
#define F_7SEG_GPIO_Port GPIOE
#define G_7SEG_Pin GPIO_PIN_9
#define G_7SEG_GPIO_Port GPIOE
#define H_7SEG_Pin GPIO_PIN_10
#define H_7SEG_GPIO_Port GPIOE
#define K1_7SEG_Pin GPIO_PIN_11
#define K1_7SEG_GPIO_Port GPIOE
#define K3_7SEG_Pin GPIO_PIN_12
#define K3_7SEG_GPIO_Port GPIOE
#define K2_7SEG_Pin GPIO_PIN_13
#define K2_7SEG_GPIO_Port GPIOE
#define K4_7SEG_Pin GPIO_PIN_14
#define K4_7SEG_GPIO_Port GPIOE
#define A_7SEG_Pin GPIO_PIN_14
#define A_7SEG_GPIO_Port GPIOD
#define B_7SEG_Pin GPIO_PIN_15
#define B_7SEG_GPIO_Port GPIOD
#define C_7SEG_Pin GPIO_PIN_0
#define C_7SEG_GPIO_Port GPIOD
#define D_7SEG_Pin GPIO_PIN_1
#define D_7SEG_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
