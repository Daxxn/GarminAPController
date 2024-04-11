/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MainWrapper.h"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO_OUT_Pin GPIO_PIN_13
#define GPIO_OUT_GPIO_Port GPIOC
#define BRGT_CS_Pin GPIO_PIN_14
#define BRGT_CS_GPIO_Port GPIOC
#define BRGT_UD_Pin GPIO_PIN_15
#define BRGT_UD_GPIO_Port GPIOC
#define STATUS_IND_Pin GPIO_PIN_0
#define STATUS_IND_GPIO_Port GPIOC
#define WHEEL_A_Pin GPIO_PIN_2
#define WHEEL_A_GPIO_Port GPIOC
#define WHEEL_A_EXTI_IRQn EXTI2_3_IRQn
#define WHEEL_B_Pin GPIO_PIN_3
#define WHEEL_B_GPIO_Port GPIOC
#define VBUS_Pin GPIO_PIN_0
#define VBUS_GPIO_Port GPIOA
#define BACKLIGHT_IN_Pin GPIO_PIN_1
#define BACKLIGHT_IN_GPIO_Port GPIOA
#define BRIGHT_Pin GPIO_PIN_2
#define BRIGHT_GPIO_Port GPIOA
#define ALT_BTN_Pin GPIO_PIN_3
#define ALT_BTN_GPIO_Port GPIOA
#define VS_BTN_Pin GPIO_PIN_4
#define VS_BTN_GPIO_Port GPIOA
#define IND_SCLK_Pin GPIO_PIN_5
#define IND_SCLK_GPIO_Port GPIOA
#define IND_LATCH_Pin GPIO_PIN_6
#define IND_LATCH_GPIO_Port GPIOA
#define IND_SD_Pin GPIO_PIN_7
#define IND_SD_GPIO_Port GPIOA
#define FLC_BTN_Pin GPIO_PIN_0
#define FLC_BTN_GPIO_Port GPIOB
#define SPD_BTN_Pin GPIO_PIN_1
#define SPD_BTN_GPIO_Port GPIOB
#define VNV_BTN_Pin GPIO_PIN_2
#define VNV_BTN_GPIO_Port GPIOB
#define CRS2_SW_Pin GPIO_PIN_10
#define CRS2_SW_GPIO_Port GPIOB
#define CRS2_A_Pin GPIO_PIN_11
#define CRS2_A_GPIO_Port GPIOB
#define GPIO_IN_Pin GPIO_PIN_12
#define GPIO_IN_GPIO_Port GPIOB
#define CRS2_B_Pin GPIO_PIN_13
#define CRS2_B_GPIO_Port GPIOB
#define ALT_A_Pin GPIO_PIN_14
#define ALT_A_GPIO_Port GPIOB
#define ALT_A_EXTI_IRQn EXTI4_15_IRQn
#define BACKLIGHT_Pin GPIO_PIN_15
#define BACKLIGHT_GPIO_Port GPIOB
#define ALT_B_Pin GPIO_PIN_6
#define ALT_B_GPIO_Port GPIOC
#define AP_BTN_Pin GPIO_PIN_7
#define AP_BTN_GPIO_Port GPIOC
#define ALT_SW_Pin GPIO_PIN_8
#define ALT_SW_GPIO_Port GPIOC
#define BANK_BTN_Pin GPIO_PIN_9
#define BANK_BTN_GPIO_Port GPIOC
#define FD_BTN_Pin GPIO_PIN_8
#define FD_BTN_GPIO_Port GPIOA
#define YD_BTN_Pin GPIO_PIN_9
#define YD_BTN_GPIO_Port GPIOA
#define XFR_BTN_Pin GPIO_PIN_10
#define XFR_BTN_GPIO_Port GPIOA
#define CRS1_A_Pin GPIO_PIN_15
#define CRS1_A_GPIO_Port GPIOA
#define CRS1_A_EXTI_IRQn EXTI4_15_IRQn
#define CRS1_B_Pin GPIO_PIN_10
#define CRS1_B_GPIO_Port GPIOC
#define CRS1_SW_Pin GPIO_PIN_11
#define CRS1_SW_GPIO_Port GPIOC
#define BC_BTN_Pin GPIO_PIN_12
#define BC_BTN_GPIO_Port GPIOC
#define HDG_SW_Pin GPIO_PIN_2
#define HDG_SW_GPIO_Port GPIOD
#define HDG_BTN_Pin GPIO_PIN_3
#define HDG_BTN_GPIO_Port GPIOB
#define APR_BTN_Pin GPIO_PIN_4
#define APR_BTN_GPIO_Port GPIOB
#define NAV_BTN_Pin GPIO_PIN_5
#define NAV_BTN_GPIO_Port GPIOB
#define HDG_A_Pin GPIO_PIN_6
#define HDG_A_GPIO_Port GPIOB
#define HDG_A_EXTI_IRQn EXTI4_15_IRQn
#define HDG_B_Pin GPIO_PIN_7
#define HDG_B_GPIO_Port GPIOB
#define USB_SER_SEL_Pin GPIO_PIN_8
#define USB_SER_SEL_GPIO_Port GPIOB
#define USART_INVALID_Pin GPIO_PIN_9
#define USART_INVALID_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
