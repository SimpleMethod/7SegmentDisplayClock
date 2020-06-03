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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define HOUR_1_D_Pin GPIO_PIN_0
#define HOUR_1_D_GPIO_Port GPIOC
#define HOUR_1_C_Pin GPIO_PIN_1
#define HOUR_1_C_GPIO_Port GPIOC
#define HOUR_1_A_Pin GPIO_PIN_2
#define HOUR_1_A_GPIO_Port GPIOC
#define HOUR_1_B_Pin GPIO_PIN_3
#define HOUR_1_B_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SECOND_2_D_Pin GPIO_PIN_6
#define SECOND_2_D_GPIO_Port GPIOA
#define SECOND_1_D_Pin GPIO_PIN_7
#define SECOND_1_D_GPIO_Port GPIOA
#define MINUTE_1_A_Pin GPIO_PIN_4
#define MINUTE_1_A_GPIO_Port GPIOC
#define BUTTON_2_Pin GPIO_PIN_5
#define BUTTON_2_GPIO_Port GPIOC
#define BUTTON_2_EXTI_IRQn EXTI9_5_IRQn
#define MINUTE_2_D_Pin GPIO_PIN_1
#define MINUTE_2_D_GPIO_Port GPIOB
#define SECOND_2_A_Pin GPIO_PIN_2
#define SECOND_2_A_GPIO_Port GPIOB
#define MINUTE_2_C_Pin GPIO_PIN_10
#define MINUTE_2_C_GPIO_Port GPIOB
#define SECOND_2_B_Pin GPIO_PIN_12
#define SECOND_2_B_GPIO_Port GPIOB
#define MINUTE_1_B_Pin GPIO_PIN_13
#define MINUTE_1_B_GPIO_Port GPIOB
#define MINUTE_1_D_Pin GPIO_PIN_14
#define MINUTE_1_D_GPIO_Port GPIOB
#define MINUTE_2_B_Pin GPIO_PIN_15
#define MINUTE_2_B_GPIO_Port GPIOB
#define BUTTON_1_Pin GPIO_PIN_6
#define BUTTON_1_GPIO_Port GPIOC
#define BUTTON_1_EXTI_IRQn EXTI9_5_IRQn
#define SECOND_1_B_Pin GPIO_PIN_7
#define SECOND_1_B_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOC
#define SECOND_1_A_Pin GPIO_PIN_8
#define SECOND_1_A_GPIO_Port GPIOA
#define SECOND_2_C_Pin GPIO_PIN_11
#define SECOND_2_C_GPIO_Port GPIOA
#define BUTTON_3_Pin GPIO_PIN_12
#define BUTTON_3_GPIO_Port GPIOA
#define BUTTON_3_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define HOUR_2_A_Pin GPIO_PIN_15
#define HOUR_2_A_GPIO_Port GPIOA
#define HOUR_2_C_Pin GPIO_PIN_11
#define HOUR_2_C_GPIO_Port GPIOC
#define HOUR_2_B_Pin GPIO_PIN_12
#define HOUR_2_B_GPIO_Port GPIOC
#define HOUR_2_D_Pin GPIO_PIN_2
#define HOUR_2_D_GPIO_Port GPIOD
#define MINUTE_2_A_Pin GPIO_PIN_4
#define MINUTE_2_A_GPIO_Port GPIOB
#define MINUTE_1_C_Pin GPIO_PIN_5
#define MINUTE_1_C_GPIO_Port GPIOB
#define SECOND_1_C_Pin GPIO_PIN_6
#define SECOND_1_C_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
