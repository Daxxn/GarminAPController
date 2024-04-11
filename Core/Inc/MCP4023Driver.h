/*
 * MCP4023Driver.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_MCP4023DRIVER_H_
#define INC_MCP4023DRIVER_H_

#include "main.h"
#include "Utils.h"

typedef enum
{
	MCP4023_2K1,
	MCP4023_5K,
	MCP4023_10K,
	MCP4023_50K
} MCP4023_Resistance;

namespace MCP4023_Consts {
	const uint8_t StepCount = 63;
	const uint8_t StepCountSubOne = 62;
	const uint8_t DefaultStep = 0x1F;
	const float ResistanceValues[] = {
			2.1, 5, 10, 50
	};
}  // namespace MCP4023_Consts

/*
 *
 */
class MCP4023Driver
{
public:
	MCP4023Driver() { };
	MCP4023Driver(Pin udPin, Pin csPin, MCP4023_Resistance res);
	MCP4023Driver(Pin udPin, Pin csPin, MCP4023_Resistance res, uint8_t defaultStep);
	virtual ~MCP4023Driver();

	HAL_StatusTypeDef Init();

	void SetWiper(uint8_t wiper);

	void Increase();
	void Decrease();

	void Reset();

	void SetDefaultStep(uint8_t wiper);
	uint8_t GetDefaultStep() { return this->defaultStep; };

	double GetResistance();
	void SetResistance(float resKOhms);
private:
	double rs = 0;
	uint8_t step = MCP4023_Consts::DefaultStep;
	float kOhms = MCP4023_Consts::ResistanceValues[2];
	uint8_t defaultStep = MCP4023_Consts::DefaultStep;
	Pin udPin;
	Pin csPin;

	void UpdateStep(uint8_t step);

	void StepUp();
	void StepDown();
};

#endif /* INC_MCP4023DRIVER_H_ */
