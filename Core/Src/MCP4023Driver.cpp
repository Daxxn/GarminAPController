/*
 * MCP4023Driver.cpp
 *
 *  Created on: Feb 4, 2024
 *      Author: Daxxn
 */

#include <MCP4023Driver.h>

using namespace MCP4023_Consts;

MCP4023Driver::MCP4023Driver(Pin udPin, Pin csPin, MCP4023_Resistance res)
{
	this->udPin = udPin;
	this->csPin = csPin;
	this->kOhms = MCP4023_Consts::ResistanceValues[res];
}

MCP4023Driver::MCP4023Driver(Pin udPin, Pin csPin, MCP4023_Resistance res, uint8_t defaultStep)
{
	this->udPin = udPin;
	this->csPin = csPin;
	this->kOhms = MCP4023_Consts::ResistanceValues[res];
	this->defaultStep = defaultStep;
}

MCP4023Driver::~MCP4023Driver()
{
}

HAL_StatusTypeDef MCP4023Driver::Init()
{
	if (this->defaultStep != DefaultStep)
	{
		this->UpdateStep(defaultStep);
	}
	return HAL_OK;
}

void MCP4023Driver::SetWiper(uint8_t wiper)
{
	assert_param(wiper >= 0 && wiper < StepCount);
	this->UpdateStep(wiper);
}

void MCP4023Driver::Increase()
{
	if (this->step < StepCountSubOne)
	{
		this->UpdateStep(step + 1);
	}
}

void MCP4023Driver::Decrease()
{
	if (step > 0)
	{
		this->UpdateStep(step - 1);
	}
}

void MCP4023Driver::Reset()
{
	this->UpdateStep(defaultStep);
}

void MCP4023Driver::SetDefaultStep(uint8_t step)
{
	assert_param(step <= StepCount);

	this->defaultStep = step;
	this->UpdateStep(this->defaultStep);
}

double MCP4023Driver::GetResistance()
{
	return (this->step / StepCount) * this->kOhms;
}

void MCP4023Driver::SetResistance(float resKOhms)
{
	if (resKOhms < 0)
	{
		UpdateStep(0);
	}
	else if (resKOhms > this->kOhms)
	{
		UpdateStep(StepCountSubOne);
	}
	else
	{
		UpdateStep(((resKOhms / this->kOhms) * 1000) * StepCount);
	}
}

void MCP4023Driver::UpdateStep(uint8_t step)
{
	if (step < this->step)
	{
		this->udPin.Write(false);
		HAL_Delay(1);
		this->csPin.Write(true);
		while (this->step > step)
		{
			this->StepDown();
			this->step--;
		}
	}
	else if (step > this->step)
	{
		this->udPin.Write(true);
		HAL_Delay(1);
		this->csPin.Write(true);
		while (this->step < step)
		{
			this->StepUp();
			this->step++;
		}
	}
	else
	{
		return;
	}
	this->csPin.Write(false);
}

void MCP4023Driver::StepUp()
{
	this->udPin.Write(true);
	HAL_Delay(1);
	this->udPin.Write(false);
	HAL_Delay(1);
}

void MCP4023Driver::StepDown()
{
	this->udPin.Write(false);
	HAL_Delay(1);
	this->udPin.Write(true);
	HAL_Delay(1);
}
