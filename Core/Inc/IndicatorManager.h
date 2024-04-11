/*
 * IndicatorManager.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_INDICATORMANAGER_H_
#define INC_INDICATORMANAGER_H_

#include "main.h"
#include "STPLEDDriver.h"

#define INDICATOR_COUNT 16

//typedef enum {
//	HDG_IND,
//	APR_IND,
//	BC_IND,
//	NAV_IND,
//	FD_IND,
//	BANK_IND,
//	AP_IND,
//	XFR_R_IND,
//	XFR_L_IND,
//	YD_IND,
//	ALT_IND,
//	VS_IND,
//	VNV_IND,
//	FLC_IND,
//	SPD_IND,
//} PanelIndicator;

/*
 *
 */
class IndicatorManager
{
public:
	IndicatorManager() { };
	IndicatorManager(STPLEDDriver *driver, PWMPin *backlight);
	virtual ~IndicatorManager();

	void ParseIndicators(uint8_t *data);

	void SetIndicator(IndicatorName ind, uint8_t state);
	void SetBacklight(uint16_t brightness);
	void SetIndBrightness(uint8_t brightness);
	void SetMaxIndBrightness(uint8_t brightness);
private:
	STPLEDDriver *driver;
	PWMPin       *backlightPWM;
	uint8_t       i;
	UInt16Union   temp;

	uint16_t      backlight;
	uint16_t      maxBrightness = UINT16_MAX / 2;
};

#endif /* INC_INDICATORMANAGER_H_ */
