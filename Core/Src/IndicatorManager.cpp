/*
 * IndicatorManager.cpp
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#include <IndicatorManager.h>

IndicatorManager::IndicatorManager(STPLEDDriver *driver, PWMPin *backlight)
{
	this->driver    = driver;
	this->backlightPWM = backlight;
}

IndicatorManager::~IndicatorManager()
{
	this->driver       = NULL;
	this->backlightPWM = NULL;
}

void IndicatorManager::ParseIndicators(uint8_t *data)
{
	this->temp.bytes[0] = data[0];
	this->temp.bytes[1] = data[1];
	this->driver->SetAllIndicators(this->temp.integer);
}

void IndicatorManager::SetIndicator(IndicatorName ind, uint8_t state)
{
	this->driver->SetIndicator(ind, state);
}

void IndicatorManager::SetBacklight(uint16_t brightness)
{
	this->backlightPWM->Set(brightness);
}

void IndicatorManager::SetIndBrightness(uint8_t brightness)
{
	this->driver->SetBrightness(brightness);
}

void IndicatorManager::SetMaxIndBrightness(uint8_t brightness)
{
//	this->maxBrightness = (uint32_t)((float)(brightness / UINT8_MAX) * UINT16_MAX);
	this->driver->SetMaxBrightness(brightness);
}
