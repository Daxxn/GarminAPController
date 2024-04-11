/*
 * buttonManager.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_BUTTONMANAGER_H_
#define INC_BUTTONMANAGER_H_

#include "main.h"
#include "Utils.h"

#define BUTTON_COUNT 18

typedef enum {
	HDG_BTN,
	APR_BTN,
	BC_BTN,
	NAV_BTN,
	FD_BTN,
	BANK_BTN,
	AP_BTN,
	XFR_BTN,
	YD_BTN,
	ALT_BTN,
	VS_BTN,
	VNV_BTN,
	FLC_BTN,
	SPD_BTN,
	CRS1_ENC_BTN,
	CRS2_ENC_BTN,
	HDG_ENC_BTN,
	ALT_ENC_BTN
} PanelButton;


typedef struct {
	Pin hdg;
	Pin apr;
	Pin bc;
	Pin nav;
	Pin fd;
	Pin bank;
	Pin ap;
	Pin xfr;
	Pin yd;
	Pin alt;
	Pin vs;
	Pin vnv;
	Pin flc;
	Pin spd;
	Pin crs1_enc;
	Pin crs2_enc;
	Pin hdg_enc;
	Pin alt_enc;
} ButtonPins;

union ButtonUnion {
	bool data[BUTTON_COUNT];
	uint32_t raw;
};

/*
 *
 */
class ButtonManager
{
public:
	ButtonManager() { };
	ButtonManager(ButtonPins pins);
	virtual ~ButtonManager();

	void GetButtons(uint8_t *data);
	void Update();

	bool GetStateChanged();
private:
	ButtonPins pins;
//	bool states[32];
//	ButtonUnion states;
	uint32_t states;
	uint8_t i;
	uint32_t previousState = (uint32_t)0;
//	bool stateChanged = false;
	UInt32Union temp;

	void SetButton(PanelButton btn, bool value);
};

#endif /* BUTTONMANAGER_H_ */
