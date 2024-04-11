/*
 * buttonManager.cpp
 *
 *  Created on: Apr 4, 2024
 *      Author: Daxxn
 */

#include "ButtonManager.h"

ButtonManager::ButtonManager(ButtonPins pins)
{
	this->pins = pins;
	this->states = (uint32_t)0;
//	this->states = new bool[BUTTON_COUNT]();
	this->temp.integer = (uint32_t)0;
}

ButtonManager::~ButtonManager()
{
//	delete[] this->states;
}

void ButtonManager::GetButtons(uint8_t *data)
{
//	this->temp.integer = 0;
//	for (i = 0; i < BUTTON_COUNT; ++i) {
//		this->temp.integer |= this->states[i] << i;
//	}
	this->temp.integer = this->states;
	data[0] = this->temp.bytes[0];
	data[1] = this->temp.bytes[1];
	data[2] = this->temp.bytes[2];
//	data[0] = this->states.bytes[0];
//	data[1] = this->states.bytes[1];
//	data[2] = this->states.bytes[2];

	this->previousState = this->temp.integer;
//	uint8_t b = 0;
//	uint8_t sb = 0;
//	for (i = 0; i < BUTTON_COUNT; ++i) {
//		data[b] |= this->states[i] << sb;
//		if (sb < 8) {
//			b++;
//		} else {
//			b = 0;
//			sb++;
//		}
//	}

//	for (i = 0; i < 3; ++i) {
//		for (uint8_t j = 0; j < 8; ++j) {
//			data[i] = this->states[8 * i + j];
//			if (!((8 * i + j) < BUTTON_COUNT)) {
//				return;
//			}
//		}
//	}
}

bool ButtonManager::GetStateChanged()
{
//	this->temp.integer = 0;
//	for (i = 0; i < BUTTON_COUNT; ++i) {
//		this->temp.integer |= this->states[i] << i;
//	}
//	return this->temp.integer != this->previousState;
	return this->states != this->previousState;
}

void ButtonManager::Update()
{
	// The boring way then...
	this->SetButton(HDG_BTN,      this->pins.hdg.Read(0));
	this->SetButton(APR_BTN,      this->pins.apr.Read(0));
	this->SetButton(BC_BTN,       this->pins.bc.Read(0));
	this->SetButton(NAV_BTN,      this->pins.nav.Read(0));
	this->SetButton(FD_BTN,       this->pins.fd.Read(0));
	this->SetButton(BANK_BTN,     this->pins.bank.Read(0));
	this->SetButton(AP_BTN,       this->pins.ap.Read(0));
	this->SetButton(XFR_BTN,      this->pins.xfr.Read(0));
	this->SetButton(YD_BTN,       this->pins.yd.Read(0));
	this->SetButton(ALT_BTN,      this->pins.alt.Read(0));
	this->SetButton(VS_BTN,       this->pins.vs.Read(0));
	this->SetButton(VNV_BTN,      this->pins.vnv.Read(0));
	this->SetButton(FLC_BTN,      this->pins.flc.Read(0));
	this->SetButton(SPD_BTN,      this->pins.spd.Read(0));
	this->SetButton(CRS1_ENC_BTN, this->pins.crs1_enc.Read(0));
	this->SetButton(CRS2_ENC_BTN, this->pins.crs2_enc.Read(0));
	this->SetButton(HDG_ENC_BTN,  this->pins.hdg_enc.Read(0));
	this->SetButton(ALT_ENC_BTN,  this->pins.alt_enc.Read(0));
}

void ButtonManager::SetButton(PanelButton btn, bool value)
{
	if (value) {
		this->states |= (1 << (uint8_t)btn);
	}
	else {
		this->states &= ~(1 << (uint8_t)btn);
	}
}
