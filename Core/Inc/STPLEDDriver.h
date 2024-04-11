/*
 * STPLEDDriver.h
 *
 *  Created on: Mar 31, 2024
 *      Author: Daxxn
 */

#ifndef INC_STPLEDDRIVER_H_
#define INC_STPLEDDRIVER_H_

#include "main.h"
#include "MCP4023Driver.h"

typedef enum : uint8_t {
	FLC_IND   = 0,
	SPD_IND   = 1,
	BC_IND    = 2,
	NAV_IND   = 3,
	APR_IND   = 4,
	HDG_IND   = 5,
	VS_IND    = 6,
	ALT_IND   = 7,
	VNV_IND   = 8,
	XFRR_IND  = 9,
	FD_IND    = 10,
	XFRL_IND  = 11,
	YD_IND    = 12,
	AP_IND    = 13,
	BANK_IND  = 14,
	ERROR_IND = 15,
} IndicatorName;

typedef union {
	uint8_t arr[2];
	uint16_t num;
} STP_U16_Union;

typedef struct {
	TIM_HandleTypeDef *htim;
	uint32_t ch;
} STP_PWM_Pin;

typedef struct {
	Pin lePin;
	STP_PWM_Pin oePin;
} STP_Pins;

/*
 *
 */
class STPLEDDriver
{
public:
	STPLEDDriver() { };
	STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins);
	STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins, uint16_t defaultValue);
	STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins, MCP4023Driver *blDriver);
	STPLEDDriver(SPI_HandleTypeDef *spi, STP_Pins pins, MCP4023Driver *blDriver, uint16_t defaultValue);
	virtual ~STPLEDDriver();

	HAL_StatusTypeDef Init();

	void SetIndicator(IndicatorName name, bool state);
	void SetIndicator(IndicatorName name, uint8_t state);
	void SetIndicator(uint8_t index, bool state);
	void SetIndicator(uint8_t index, uint8_t state);
	void ToggleIndicator(IndicatorName name);
	void ToggleIndicator(uint8_t index);
	void SetAllIndicators(uint16_t states);

	void AllOFF();

	void SetMaxBrightness(uint8_t bright);
	void SetBrightness(uint16_t bright);
private:
	SPI_HandleTypeDef *h_spi;
	MCP4023Driver *h_bl;
	uint16_t brightness = UINT16_MAX / 2;
	UInt16Union rxUnion;
	STP_Pins pins;

	HAL_StatusTypeDef SendState();
	void SetBright();
	void ClearBright();
};

#endif /* INC_STPLEDDRIVER_H_ */
