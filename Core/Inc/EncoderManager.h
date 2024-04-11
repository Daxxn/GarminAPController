/*
 * EncoderManager.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_ENCODERMANAGER_H_
#define INC_ENCODERMANAGER_H_

#include "main.h"
#include "RotaryEncoder.h"

#define ENCODER_COUNT 5

typedef enum {
	HDG_ENC,
	ALT_ENC,
	WHEEL_ENC,
	CRS1_ENC,
	CRS2_ENC,
} PanelEncoder;

/*
 *
 */
class EncoderManager
{
public:
	EncoderManager() { };
	EncoderManager(RotaryEncoder *hdgEnc, RotaryEncoder *altEnc, RotaryEncoder *whlEnc, RotaryEncoder *crs1Enc, RotaryEncoder *crs2Enc);
	virtual ~EncoderManager();

	void GetPositions(uint8_t *buffer);
	void GetDirections(uint8_t *buffer);
	bool GetStateChanged();
private:
	RotaryEncoder *hdgEnc;
	RotaryEncoder *altEnc;
	RotaryEncoder *whlEnc;
	RotaryEncoder *crs1Enc;
	RotaryEncoder *crs2Enc;
	uint8_t i = 0;
	bool stateChanged = false;
};

#endif /* INC_ENCODERMANAGER_H_ */
