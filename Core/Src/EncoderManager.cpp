/*
 * EncoderManager.cpp
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#include <EncoderManager.h>

EncoderManager::EncoderManager(RotaryEncoder *hdgEnc, RotaryEncoder *altEnc, RotaryEncoder *whlEnc, RotaryEncoder *crs1Enc, RotaryEncoder *crs2Enc)
{
	this->hdgEnc = hdgEnc;
	this->altEnc = altEnc;
	this->whlEnc = whlEnc;
	this->crs1Enc = crs1Enc;
	this->crs2Enc = crs2Enc;
}

EncoderManager::~EncoderManager()
{
	this->hdgEnc = NULL;
	this->altEnc = NULL;
	this->whlEnc = NULL;
	this->crs1Enc = NULL;
	this->crs2Enc = NULL;
}

bool EncoderManager::GetStateChanged()
{
	if (this->hdgEnc->GetStateChanged()) {
		this->stateChanged = true;
		return true;
	}
	if (this->altEnc->GetStateChanged()) {
		this->stateChanged = true;
		return true;
	}
	if (this->whlEnc->GetStateChanged()) {
		this->stateChanged = true;
		return true;
	}
	if (this->crs1Enc->GetStateChanged()) {
		this->stateChanged = true;
		return true;
	}
	if (this->crs2Enc->GetStateChanged()) {
		this->stateChanged = true;
		return true;
	}
	return false;
}

void EncoderManager::GetPositions(uint8_t *buffer)
{
	buffer[0] = this->hdgEnc->GetPosition();
	buffer[1] = this->altEnc->GetPosition();
	buffer[2] = this->whlEnc->GetPosition();
	buffer[3] = this->crs1Enc->GetPosition();
	buffer[4] = this->crs2Enc->GetPosition();
}

void EncoderManager::GetDirections(uint8_t *buffer)
{
//	EncoderDirection hdgDir = this->hdgEnc->GetDirection();
//	EncoderDirection altDir = this->altEnc->GetDirection();
//	EncoderDirection whlDir = this->whlEnc->GetDirection();
//	EncoderDirection crs1Dir = this->crs1Enc->GetDirection();
//	EncoderDirection crs2Dir = this->crs2Enc->GetDirection();

	buffer[0]  = (uint8_t)this->hdgEnc->GetDirection();
	buffer[0] |= (uint8_t)this->altEnc->GetDirection() << 2;
	buffer[0] |= (uint8_t)this->whlEnc->GetDirection() << 4;
	buffer[0] |= (uint8_t)this->crs1Enc->GetDirection() << 6;
	buffer[1]  = (uint8_t)this->crs2Enc->GetDirection();

	this->hdgEnc->ResetDir();
	this->altEnc->ResetDir();
	this->whlEnc->ResetDir();
	this->crs1Enc->ResetDir();
	this->crs2Enc->ResetDir();
}
