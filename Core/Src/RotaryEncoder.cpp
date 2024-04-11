/*
 * RotaryEncoder.cpp
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#include <RotaryEncoder.h>

RotaryEncoder::RotaryEncoder(Pin *a, Pin *b)
{
	this->a = a;
	this->b = b;
}

RotaryEncoder::~RotaryEncoder()
{
	this->a = NULL;
	this->b = NULL;
}

void RotaryEncoder::OnInterrupt()
{
	this->b->Read();
	if (this->b->GetState(0)) {
		this->dir = ENC_CW;
		this->count += 1;
	}
	else {
		this->dir = ENC_CCW;
		this->count -= 1;
	}
	this->stateChanged = true;
}

void RotaryEncoder::Update()
{
	bool ea = this->a->Read(0);
	this->b->Read();
	if (ea && !this->previousState) {
		if (this->b->GetState(0)) {
			this->dir = ENC_CW;
			this->count += 1;
		} else {
			this->dir = ENC_CCW;
			this->count -= 1;
		}
	}
	this->stateChanged = true;
}

EncoderDirection RotaryEncoder::GetDirection()
{
	this->stateChanged = false;
	return this->dir;
}

int8_t RotaryEncoder::GetPosition()
{
	int8_t pos = this->count;
	this->stateChanged = false;
	this->count = 0;
	return pos;
}
