/*
 * RotaryEncoder.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#ifndef INC_ROTARYENCODER_H_
#define INC_ROTARYENCODER_H_

#include "main.h"
#include "Utils.h"

typedef enum : int8_t {
	ENC_CW    = 2,
	ENC_CCW   = 0,
	ENC_STILL = 1,
} EncoderDirection;

/*
 *
 */
class RotaryEncoder
{
public:
	RotaryEncoder() { };
	RotaryEncoder(Pin *a, Pin *b);
	virtual ~RotaryEncoder();

	void OnInterrupt();

	EncoderDirection GetDirection();
	int8_t GetPosition();
	bool GetStateChanged() { return this->stateChanged; };

	void ResetDir() { this->dir = ENC_STILL; }

	void Update();
private:
	Pin             *a;
	Pin             *b;
	GPIO_PinState    previousState;
	EncoderDirection dir = ENC_STILL;
	int8_t           count = 0;
	int8_t           prevCount = 0;

	bool stateChanged = false;
};

#endif /* INC_ROTARYENCODER_H_ */
