/*
 * STPLEDDriver.cpp
 *
 *  Created on: Mar 31, 2024
 *      Author: Daxxn
 */

#include <STPLEDDriver.h>

STPLEDDriver::STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins)
{
	this->h_spi           = spi;
	this->pins            = pins;
	this->rxUnion.integer = 0;
}

STPLEDDriver::STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins, uint16_t defaultValue)
{
	this->h_spi           = spi;
	this->pins            = pins;
	this->rxUnion.integer = defaultValue;
}

STPLEDDriver::STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins, MCP4023Driver *blDriver)
{
	this->h_spi           = spi;
	this->pins            = pins;
	this->h_bl            = blDriver;
	this->rxUnion.integer = 0;
}

STPLEDDriver::STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins, MCP4023Driver *blDriver, uint16_t defaultValue)
{
	this->h_spi           = spi;
	this->pins            = pins;
	this->h_bl            = blDriver;
	this->rxUnion.integer = defaultValue;
}

STPLEDDriver::~STPLEDDriver()
{
	this->h_spi           = NULL;
	this->h_bl            = NULL;
	this->pins            = { };
	this->rxUnion.integer = 0;
}

HAL_StatusTypeDef STPLEDDriver::Init()
{
	if (this->h_bl->Init() != HAL_OK) {
		return HAL_ERROR;
	}

	HAL_TIM_PWM_Start(this->pins.oePin.htim, this->pins.oePin.ch);
	if (this->SendState() != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}

void STPLEDDriver::SetIndicator(IndicatorName name, bool state)
{
	this->SetIndicator(name, (uint8_t)state);
}

void STPLEDDriver::SetIndicator(IndicatorName name, uint8_t state)
{
	if (state != 0) {
		this->rxUnion.integer &= ~(1 << name);
	} else {
		this->rxUnion.integer |= (1 << name);
	}
	this->SendState();
}

void STPLEDDriver::SetIndicator(uint8_t index, bool state)
{
	assert_param(index < STP_CHANNEL_COUNT);
	this->SetIndicator(index, (uint8_t)state);
}

void STPLEDDriver::SetIndicator(uint8_t index, uint8_t state)
{
	assert_param(index < STP_CHANNEL_COUNT);
	if (state != 0) {
		this->rxUnion.integer &= ~(1 << index);
	} else {
		this->rxUnion.integer |= (1 << index);
	}
	this->SendState();
}

void STPLEDDriver::ToggleIndicator(IndicatorName name)
{
	this->ToggleIndicator((uint8_t)name);
}

void STPLEDDriver::ToggleIndicator(uint8_t index)
{
	assert_param(index < STP_CHANNEL_COUNT);
	this->rxUnion.integer ^= (1 << index);
	this->SendState();
}

void STPLEDDriver::SetAllIndicators(uint16_t states)
{
	this->rxUnion.integer = states;
	this->SendState();
}

void STPLEDDriver::AllOFF()
{
	this->rxUnion.integer = 0;
	this->SendState();
}

void STPLEDDriver::SetMaxBrightness(uint8_t bright)
{
	this->h_bl->SetWiper(bright);
}

void STPLEDDriver::SetBrightness(uint16_t bright)
{
	this->brightness = bright;
	this->SetBright();
}

void STPLEDDriver::SetBright()
{
	__HAL_TIM_SET_COMPARE(this->pins.oePin.htim, this->pins.oePin.ch, this->brightness);
}

void STPLEDDriver::ClearBright()
{
	__HAL_TIM_SET_COMPARE(this->pins.oePin.htim, this->pins.oePin.ch, 0);
}

HAL_StatusTypeDef STPLEDDriver::SendState()
{
	this->ClearBright();
	this->pins.lePin.Write(true);
	if (HAL_SPI_Transmit(this->h_spi, this->rxUnion.bytes, 2, 100) != HAL_OK) {
		return HAL_ERROR;
	}
	this->pins.lePin.Write(false);
	this->SetBright();
	return HAL_OK;
}
