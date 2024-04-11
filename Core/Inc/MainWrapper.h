/*
 * MainWrapper.h
 *
 *  Created on: Mar 9, 2024
 *      Author: Daxxn
 */

#ifndef INC_MAINWRAPPER_H_
#define INC_MAINWRAPPER_H_

#include "main.h"

#define BACKLIGHT_PWM_CH TIM_CHANNEL_2

void EncInterruptCallback(uint16_t pinNumber);

void UsbReceiveCallback();

void TimerElapsedCallback(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef Init(ADC_HandleTypeDef *hadc, SPI_HandleTypeDef *hspi1, TIM_HandleTypeDef *htim15, UART_HandleTypeDef *huart3, TIM_HandleTypeDef *htim7);

void Main();

#endif /* INC_MAINWRAPPER_H_ */
