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
#include "stm32f1xx_hal.h"

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

#define TEST_TFT_AT_STARTUP		0

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOA
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOA
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define COL0_Pin GPIO_PIN_0
#define COL0_GPIO_Port GPIOB
#define COL1_Pin GPIO_PIN_1
#define COL1_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_10
#define COL2_GPIO_Port GPIOB
#define COL3_Pin GPIO_PIN_11
#define COL3_GPIO_Port GPIOB
#define ROW0_Pin GPIO_PIN_10
#define ROW0_GPIO_Port GPIOA
#define ROW1_Pin GPIO_PIN_11
#define ROW1_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_12
#define ROW2_GPIO_Port GPIOA
#define ROW3_Pin GPIO_PIN_15
#define ROW3_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_4
#define RD_GPIO_Port GPIOB
#define WR_Pin GPIO_PIN_5
#define WR_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_6
#define RS_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_7
#define CS_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_8
#define RST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
